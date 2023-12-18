CREATE DATABASE assignment5;
GO;
USE assignment5;

-- Tables as in the requirements.

CREATE TABLE Ta(
    aid INT PRIMARY KEY,    -- Clustered
    a2 INT UNIQUE,          -- Non-clustered
    a3 INT                  -- Non-clustered
);
DROP TABLE Ta;

CREATE TABLE Tb (
	bid INT PRIMARY KEY,    -- Clustered
	b2 INT                  -- Non-clustered
);
DROP TABLE Tb;

CREATE TABLE Tc (
	cid INT PRIMARY KEY,                        -- Clustered
	aid INT FOREIGN KEY REFERENCES Ta(aid),     -- Non-clustered I think
	bid INT FOREIGN KEY REFERENCES Tb(bid)      -- Non-clustered I think
);
DROP TABLE Tc;

-- Random bullshit generators
GO
CREATE OR ALTER PROCEDURE randomTa(@rows INT) AS
BEGIN
	DECLARE @max INT
	SET @max = @rows*2 + 100
	WHILE @rows > 0
	BEGIN
		INSERT INTO Ta VALUES (@rows, @max, @max%210)
		SET @rows = @rows - 1
		SET @max = @max - 2
	END
END

GO
CREATE OR ALTER PROCEDURE randomTb(@rows INT) AS
BEGIN
	WHILE @rows > 0
	BEGIN
		INSERT INTO Tb VALUES(@rows, @rows%542)
		SET @rows = @rows - 1
	END
END

GO
CREATE OR ALTER PROCEDURE randomTc(@rows INT) AS
BEGIN
	DECLARE @aid INT
	DECLARE @bid INT
	WHILE @rows > 0
	BEGIN
		SET @aid = (SELECT TOP 1 aid FROM Ta ORDER BY NEWID())
		SET @bid = (SELECT TOP 1 bid FROM Tb ORDER BY NEWID())
		INSERT INTO Tc VALUES(@rows, @aid, @bid)
		SET @rows = @rows - 1
	END
END

-- Random bullshit go
EXEC randomTa 10000;
EXEC randomTb 12500;
EXEC randomTc 9000;

-- Preview bullshit
SELECT *
FROM Ta;

SELECT *
FROM Tb;

SELECT *
FROM Tc;


-- a. Write queries on Ta such that their execution plans contain the following operators:...
-- clustered index scan
-- estimated cost: 0.0328005 for 10k rows
SELECT *
FROM Ta;

-- clustered index seek
-- estimated cost: 0.0035119 for 209 rows
SELECT *
FROM Ta
WHERE aid < 210;

-- non-clustered index
-- estimated cost: 0.0268746 for 10k rows
SELECT a2
FROM Ta
ORDER BY a2;

-- non-clustered seek
-- estimated cost: 0.00333754 for 50 rows
SELECT a2
FROM Ta
WHERE a2 BETWEEN 100 AND 200;

-- key lookup using non-clustered seek
-- estimated cost: 0.00657038 for 1 row
SELECT a2, a3
FROM Ta
WHERE a2 = 530;

-- b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. Create a nonclustered index that can speed up the query. Examine the execution plan again.
SELECT *
FROM Tb
WHERE b2 = 154;

-- clustered scan with estimated cost: 0.0362913

-- creating new index:
DROP INDEX Tb_b2_index ON Tb;
CREATE NONCLUSTERED INDEX Tb_b2_index ON Tb(b2);

-- non-clustered seek with estimated cost: 0.0033073

-- c. Create a view that joins at least 2 tables. Check whether existing indexes are helpful; if not, reassess existing indexes / examine the cardinality of the tables.
GO;
CREATE OR ALTER VIEW manitis11PMandIamSleepySendHelpView AS
	SELECT A.aid, B.bid, C.cid
	FROM Tc C
	INNER JOIN Ta A ON A.aid = C.aid
	INNER JOIN Tb B ON B.bid = C.bid
	WHERE B.b2 > 500 AND A.a3 < 150;

GO;
SELECT *
FROM manitis11PMandIamSleepySendHelpView;

-- ok so, estimated costs:
-- default indexes: 0.292161
-- default indexes + non-clustered b2 from before: 0.25493
-- adding non-clustered to a3 from before: 0.237364
-- without non-clustered b2, with non-clustered a3: 0.274595
-- non-clustered b2 + non-clustered a3 + non-clustered (aid, bid) from Tc: 0.235142

DROP INDEX Ta_a3_index ON Ta;
CREATE NONCLUSTERED INDEX Ta_a3_index ON Ta(a3);

DROP INDEX Tc_index ON Tc;
CREATE NONCLUSTERED INDEX Tc_index ON Tc(aid, bid);