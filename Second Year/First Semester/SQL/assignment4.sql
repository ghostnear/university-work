USE assignment4;

-- BIG PROCEDURE CHUNK YES.

GO
CREATE OR ALTER PROCEDURE measureViewSelect(@viewName VARCHAR(MAX), @testRunId INT)
AS
    DECLARE @startTime DATETIME = sysdatetime()

    -- Build statement and execute it.
    DECLARE @statement VARCHAR(MAX) = concat('SELECT * FROM ' , @viewName)
    EXEC (@statement)

    DECLARE @endTime DATETIME = sysdatetime()

    -- Get the view ID and insert it into the test run views.
    DECLARE @viewId INT = (SELECT ViewID FROM Views WHERE Views.Name = @viewName)
    INSERT INTO TestRunViews VALUES (@testRunId, @viewId, @startTime, @endTime)
GO

CREATE OR ALTER PROCEDURE measureViewInsert(@testRunId INT, @tableId INT)
AS
    DECLARE @tableName VARCHAR = (SELECT Name FROM Tables WHERE @tableId = Tables.TableID)
    DECLARE @noRows INT = (SELECT NoOfRows FROM TestTables WHERE @testRunId = TestID AND TableID = @tableId)

    DECLARE @startTime DATETIME = sysdatetime()

    -- Execute all the inserts.
    DECLARE @iteration INT = @noRows
    WHILE @iteration > 0 BEGIN
        DECLARE @command VARCHAR(MAX) = concat('insertInto', @tableName)
        EXEC @command @iteration
        SET @iteration = @iteration-1
    END

    DECLARE @endTime DATETIME = sysdatetime()

    -- Insert into the test run views.
    INSERT INTO TestRunTables VALUES (@testRunId, @tableId, @startTime, @endTime)
GO

CREATE OR ALTER PROCEDURE runTest(@testId INT)
AS
    DECLARE tablesCursor CURSOR SCROLL
        FOR SELECT TableID,Position FROM TestTables WHERE TestID = @testId ORDER BY Position
    OPEN tablesCursor

    DECLARE viewCursor CURSOR SCROLL
        FOR SELECT ViewID FROM TestViews WHERE TestID = @testId
    OPEN viewCursor

    DECLARE @startTime DATETIME = sysdatetime()

    INSERT INTO TestRuns (Description, StartAt, EndAt) VALUES (@testId, @startTime, null)
    DECLARE @testRunId INT = (SELECT TestRunID FROM TestRuns WHERE @startTime = StartAt)
    DECLARE @tableID INT
    DECLARE @position INT
    FETCH FIRST FROM tablesCursor INTO @tableID, @position

    -- Erase so that we can insert later.
    WHILE @@fetch_status = 0 BEGIN
        DECLARE @myTableName VARCHAR(MAX) = (SELECT name FROM Tables WHERE @tableID = TableID)
        DECLARE @deleteCmd VARCHAR(MAX) = concat('DELETE FROM ', @myTableName)
        EXECUTE (@deleteCmd)
        FETCH NEXT FROM tablesCursor INTO @tableID, @position
    END

    -- Measure the insert times.
    FETCH LAST FROM tablesCursor INTO @tableID, @position
    WHILE @@fetch_status = 0 BEGIN
        EXEC measureViewInsert @testRunId, @tableID
        FETCH PRIOR FROM tablesCursor INTO @tableID, @position
    END

    -- Measure the view times.
    DECLARE @viewId INT;
    FETCH FIRST FROM viewCursor INTO @viewId BEGIN
       DECLARE @viewName VARCHAR(MAX) = (SELECT Name FROM Views WHERE @viewId = ViewID)
       EXEC measureViewSelect @viewName, @testRunId
    END

    DECLARE @endTime DATETIME = sysdatetime()

    -- Clean up the memory.
    CLOSE viewCursor
    DEALLOCATE viewCursor
    CLOSE tablesCursor
    DEALLOCATE tablesCursor

    -- Update the times in the database.
    UPDATE TestRuns SET EndAt = @endTime WHERE TestRunID = @testRunId
GO

-- MAIN ENTRY POINT CHUNK.

CREATE OR ALTER VIEW mangaView AS
    SELECT * FROM Manga;

SELECT * FROM Author;

CREATE OR ALTER VIEW mangaAuthorView AS
    SELECT M.Title, A.Naming
    FROM Manga as M, Author as A
        INNER JOIN MangasToAuthors ON
            M.ID = MangasToAuthors.MangaID AND A.Naming = MangasToAuthors.AuthorID;

CREATE OR ALTER VIEW mangaReaderView AS
    SELECT M.Title, R.UserName
    FROM Manga as M, Reader as R
        INNER JOIN ReaderToManga ON
            M.ID = ReaderToManga.MangaID AND R.ID = ReaderToManga.ReaderID
    GROUP BY M.Title, R.UserName;

CREATE OR ALTER PROCEDURE insertIntoManga(@index int) AS
    INSERT INTO Manga (Title, TotalChapters, MangaType, PhysicallyOwned) VALUES ('Dummy Manga', @index, 'test', 1);

CREATE OR ALTER PROCEDURE insertIntoReader(@index int) AS
    INSERT INTO Reader (UserName, PfPPath) VALUES (@index, null);

create table MulticolumnKey(
    id1 int,
    id2 int,
    primary key (id1, id2)
);

CREATE OR ALTER PROCEDURE insertIntoMulticolumnKey(@index int) AS
    INSERT INTO MulticolumnKey VALUES(@index, @index);

INSERT INTO Tests VALUES ('MulticolumnKeyTest');
INSERT INTO Tests VALUES ('ReaderTest');
INSERT INTO Tests VALUES ('MangaTest');

INSERT INTO Tables VALUES ('MulticolumnKey');
INSERT INTO Tables VALUES ('Reader');
INSERT INTO Tables VALUES ('Manga');

INSERT INTO TestTables VALUES (1,1,15,0);
INSERT INTO TestTables VALUES (2,2,15,1);
INSERT INTO TestTables VALUES (3,3,15,2);

INSERT INTO Views VALUES('mangaView');
INSERT INTO TestViews VALUES(3, 1);
INSERT INTO TestViews VALUES(1, 1);

DELETE FROM TestTables;
DELETE FROM Tables;

EXEC runTest 1;
