-- Write SQL scripts that:
-- a. modify the type of a column;
CREATE OR ALTER PROCEDURE make_manga_physicallyowned_int as
    ALTER TABLE Manga ALTER COLUMN PhysicallyOwned int;

CREATE OR ALTER PROCEDURE make_manga_physicallyowned_bit as
    ALTER TABLE Manga ALTER COLUMN PhysicallyOwned bit;

-- b. add / remove a column;
CREATE OR ALTER PROCEDURE add_manga_description as
    ALTER TABLE Manga ADD MangaDescription varchar(255);

CREATE OR ALTER PROCEDURE remove_manga_description as
    ALTER TABLE Manga DROP COLUMN MangaDescription;

-- c. add / remove a DEFAULT constraint;
CREATE OR ALTER PROCEDURE add_manga_physicallyowned_default as
    ALTER TABLE Manga ADD CONSTRAINT DEFAULTPO1 DEFAULT(1) FOR PhysicallyOwned;

CREATE OR ALTER PROCEDURE remove_manga_physicallyowned_default as
    ALTER TABLE Manga DROP CONSTRAINT DEFAULTPO1;

-- g. create / drop a table.
CREATE OR ALTER PROCEDURE create_manga_review as 
    CREATE TABLE MangaReview(
        ID int PRIMARY KEY IDENTITY,
        MangaID int FOREIGN KEY REFERENCES Manga(ID),
        ReaderID int FOREIGN KEY REFERENCES Reader(ID),
        Review varchar(255),
        Rating int
    );

CREATE OR ALTER PROCEDURE drop_manga_review as
    DROP TABLE MangaReview;

-- d. add / remove a primary key;
CREATE OR ALTER PROCEDURE add_manga_review_pk as
    ALTER TABLE MangaReview ADD CONSTRAINT MangaReviewPK PRIMARY KEY(ID);

CREATE OR ALTER PROCEDURE remove_manga_review_pk as
    ALTER TABLE MangaReview DROP CONSTRAINT MangaReviewPK;

-- e. add / remove a candidate key;
CREATE OR ALTER PROCEDURE add_manga_review_ck as
    ALTER TABLE MangaReview ADD CONSTRAINT MangaReviewCK UNIQUE(Review);

CREATE OR ALTER PROCEDURE remove_manga_review_ck as
    ALTER TABLE MangaReview DROP CONSTRAINT MangaReviewCK;

-- f. add / remove a foreign key;
CREATE OR ALTER PROCEDURE add_manga_review_fk as
    ALTER TABLE MangaReview ADD CONSTRAINT MangaReviewFK FOREIGN KEY(MangaID) REFERENCES Manga(ID);

CREATE OR ALTER PROCEDURE remove_manga_review_fk as
    ALTER TABLE MangaReview DROP CONSTRAINT MangaReviewFK;

-- Create a new table that holds the current version of the database schema.
-- Simplifying assumption: the version is an integer number.
CREATE TABLE SchemaVersion(
    Version int PRIMARY KEY
);
INSERT INTO SchemaVersion VALUES(0);
DROP TABLE SchemaVersion;

-- Write a stored procedure that receives as a parameter a version number and brings the database to that version.
CREATE TABLE SchemaProcedures(
    targetVersion int,
    sourceVersion int,
	PRIMARY KEY (sourceVersion, targetVersion),
    procedureName varchar(255)
);
DROP TABLE SchemaProcedures;

INSERT INTO SchemaProcedures VALUES
    (1, 0, 'make_manga_physicallyowned_int'),
    (0, 1, 'make_manga_physicallyowned_bit'),
    (2, 1, 'add_manga_description'),
    (1, 2, 'remove_manga_description'),
    (3, 2, 'add_manga_physicallyowned_default'),
    (2, 3, 'remove_manga_physicallyowned_default'),
    (4, 3, 'create_manga_review'),
    (3, 4, 'drop_manga_review'),
    (5, 4, 'add_manga_review_pk'),
    (4, 5, 'remove_manga_review_pk'),
    (6, 5, 'add_manga_review_ck'),
    (5, 6, 'remove_manga_review_ck'),
    (7, 6, 'add_manga_review_fk'),
    (6, 7, 'remove_manga_review_fk');

CREATE OR ALTER PROCEDURE update_schema_version @version int as
    DECLARE @currentVersion int
    DECLARE @procedure varchar(255)
    SELECT @currentVersion = Version FROM SchemaVersion

    IF @version > (SELECT MAX(targetVersion) FROM SchemaProcedures)
        RAISERROR('Inexistent version', 10, 1)

    WHILE @currentVersion > @version BEGIN
        SELECT @procedure = procedureName FROM SchemaProcedures WHERE targetVersion = @currentVersion - 1 AND sourceVersion = @currentVersion
        EXEC (@procedure)
        SET @currentVersion = @currentVersion - 1
    END

    WHILE @currentVersion < @version BEGIN
        SELECT @procedure = procedureName FROM SchemaProcedures WHERE targetVersion = @currentVersion + 1 AND sourceVersion = @currentVersion
        EXEC (@procedure)
        SET @currentVersion = @currentVersion + 1
    END

    UPDATE SchemaVersion SET Version = @version;

EXECUTE update_schema_version 1;