CREATE DATABASE SportDB;
GO
USE SportDB
GO

CREATE TABLE SportsTypes(
	ID int PRIMARY KEY IDENTITY,
	Nume varchar(255),
	Descriere varchar(255)
);

CREATE TABLE Sports(
	ID int PRIMARY KEY IDENTITY,
	Nume varchar(255),
	Descriere varchar(255),
	Locatie varchar(255),
	Tip int FOREIGN KEY REFERENCES SportsTypes(ID)
);

CREATE TABLE Players(
	ID int PRIMARY KEY IDENTITY,
	Nume varchar(255),
	Prenume varchar(255),
	DataNastere date,
	Gen varchar(255),
	Sport int FOREIGN KEY REFERENCES Sports(ID)
);

CREATE TABLE Clubs(
	ID int PRIMARY KEY IDENTITY,
	Nume varchar(255),
	AnDeschidere int,
	Stele int
);

CREATE TABLE ClubPlayers(
	ClubID int FOREIGN KEY REFERENCES Clubs(ID),
	PlayerID int FOREIGN KEY REFERENCES Players(ID),
	Taxa int,
	DataInscriere date
);

INSERT INTO Sports (Nume, Descriere, Locatie) VALUES
	('Fotbal', 'Jocul cu mingea rotunda.', 'Bistrita'),
	('Rugby', 'Cel cu mingea ovala.', 'Cluj Napoca');

INSERT INTO Players (Nume, Prenume, Gen, Sport) VALUES
	('Gigel', 'Ilenii', 'Barbat', 1),
	('Gigela', 'Aioanei', 'Femeie', 1),
	('Costel', 'Aioanei', 'Barbat', 2),
	('Costela', 'Ilenii', 'Femeie', 2);

SELECT * FROM Players;
SELECT * FROM Sports;

-- Phantom reads.
-- T1
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
DECLARE @playerID int;
SET @playerID = CAST((SELECT TOP 1 ID FROM Players ORDER BY ID DESC) AS INT) + 1; -- Get biggest ID and add 1.
BEGIN TRANSACTION
WAITFOR DELAY '00:00:03'
INSERT INTO Players (ID, Nume, Prenume) VALUES (@playerID, 'Participant', 'Nou');
COMMIT TRANSACTION

-- Why does this occur?
-- This occurs because more rows have been added to the table that fit the criteria of the select.
-- The first select from T2 reads a set of rows, T1 then inserts some new rows, after which T2 reads a different set of rows now.
-- How to fix?
-- Increasing the isolation level to serializable will fix this issue from appearing as they will be scheduled to be runned
--	one after another and as such the insert will occur before the first select.