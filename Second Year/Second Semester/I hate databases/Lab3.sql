USE EventDatabaseValidateParticipantUser
GO

-- Stuff for 3.
CREATE OR ALTER FUNCTION ValidateEvent (@name VARCHAR(20), @description VARCHAR(50), @date DATE, @location VARCHAR(20))
RETURNS INT AS
BEGIN
	DECLARE @returnValue INT
	SET @returnValue = 1
	IF (@name NOT IN ('Gaming tournament', 'Thing', 'Other thing'))
	SET @returnValue = 0
	IF (@date < '2000-1-1' OR @date > '2045-1-31')
	SET @returnValue = 0
	IF (@location NOT IN ('Bistrita', 'Suceava', 'Iasi'))
	SET @returnValue = 0
	RETURN @returnValue
END
GO

CREATE OR ALTER FUNCTION ValidateParticipantUser (@name VARCHAR(20), @age SMALLINT, @facultyID CHAR(10), @groupID CHAR(10))
RETURNS INT AS
BEGIN
	DECLARE @returnValue INT
	SET @returnValue = 1
	-- Minors not allowed.
	IF (@age < 18)
	SET @returnValue = 0
	IF (@facultyID NOT IN (SELECT oid FROM Organizers))
	SET @returnValue = 0
	IF (@groupID NOT IN (SELECT did FROM Departments))
	SET @returnValue = 0
	RETURN @returnValue
END
GO

CREATE OR ALTER PROCEDURE AddParticipantForSpecial @participantName VARCHAR(20), @participantAge SMALLINT, @participantoid CHAR(10), @participantDID CHAR(10), @specialeventName VARCHAR(20), @specialeventDescription VARCHAR(50), @specialeventDate DATE, @specialeventLocation VARCHAR(20)
AS
BEGIN
	BEGIN TRANSACTION
	BEGIN TRY
		IF (dbo.ValidateParticipantUser(@participantName, @participantAge, @participantoid, @participantDID) <> 1)
		BEGIN
			RAISERROR('Invalid participant', 14, 1)
		END
		DECLARE @participantID CHAR(10)
		SET @participantID = CAST((CAST((SELECT TOP 1 vid FROM Participants ORDER BY vid DESC) AS INT) + 1) AS CHAR(10))
		INSERT INTO Participants VALUES (@participantID, @participantName, @participantAge, @participantoid, @participantDID)

		IF (dbo.ValidateEvent(@specialeventName, @specialeventDescription, @specialeventDate, @specialeventLocation) <> 1)
		BEGIN
			RAISERROR('Invalid Special event', 14, 1)
		END
		DECLARE @specialeventID CHAR(10)
		SET @specialeventID = CAST((CAST((SELECT TOP 1 specialid FROM SpecialEvents ORDER BY specialid DESC) AS INT) + 1) AS CHAR(10))
		INSERT INTO SpecialEvents VALUES (@specialeventID, @specialeventName, @specialeventDescription, @specialeventDate, @specialeventLocation)
		INSERT INTO ParticipantsForSpecial VALUES (@participantID, @specialeventID)
		COMMIT TRANSACTION
		SELECT 'Transaction committed'
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION
		SELECT 'Transaction rollbacked'
	END CATCH
END
GO

EXEC AddParticipantForSpecial 'New participant', 19, '11', '1', 'Gaming tournament', 'insert description here', '2005-11-29', 'Bistrita'
GO
EXEC AddParticipantForSpecial 'New participant', 11, '11', '1', 'Gaming tournament', 'insert description here', '2020-5-17', 'Bistrita'
GO

SELECT * FROM Participants
SELECT * FROM SpecialEvents
SELECT * FROM ParticipantsForSpecial
GO

-- Stuff for 5.
CREATE OR ALTER PROCEDURE AddParticipantForSpecial_Individually @participantName VARCHAR(20), @participantAge SMALLINT, @participantoid CHAR(10), @participantDID CHAR(10), @specialeventName VARCHAR(20), @specialeventDescription VARCHAR(50), @specialeventDate DATE, @specialeventLocation VARCHAR(20)
AS
BEGIN
	DECLARE @AddParticipantSuccess SMALLINT
	SET @AddParticipantSuccess = 0
	DECLARE @AddSpecialEventSuccess SMALLINT
	SET @AddSpecialEventSuccess = 0
	DECLARE @participantID CHAR(10)
	DECLARE @specialeventID CHAR(10)
	BEGIN TRANSACTION
	BEGIN TRY
		IF (dbo.ValidateParticipantUser(@participantName, @participantAge, @participantoid, @participantDID) <> 1)
		BEGIN
			RAISERROR('Invalid participant', 14, 1)
		END
		SET @participantID = CAST((CAST((SELECT TOP 1 vid FROM Participants ORDER BY vid DESC) AS INT) + 1) AS CHAR(10))
		INSERT INTO Participants VALUES (@participantID, @participantName, @participantAge, @participantoid, @participantDID)
		SET @AddParticipantSuccess = 1
		COMMIT TRANSACTION
		SELECT 'Transaction for adding participant committed'
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION
		SELECT 'Transaction for adding participant rollbacked'
	END CATCH
	BEGIN TRANSACTION
	BEGIN TRY
		IF (dbo.ValidateEvent(@specialeventName, @specialeventDescription, @specialeventDate, @specialeventLocation) <> 1)
		BEGIN
			RAISERROR('Invalid Special event', 14, 1)
		END
		SET @specialeventID = CAST((CAST((SELECT TOP 1 specialid FROM SpecialEvents ORDER BY specialid DESC) AS INT) + 1) AS CHAR(10))
		INSERT INTO SpecialEvents VALUES (@specialeventID, @specialeventName, @specialeventDescription, @specialeventDate, @specialeventLocation)
		SET @AddSpecialEventSuccess = 1
		COMMIT TRANSACTION
		SELECT 'Transaction for adding Special Event committed'
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION
		SELECT 'Transaction adding Special Event rollbacked'
	END CATCH
	IF (@AddParticipantSuccess = 1 AND @AddSpecialEventSuccess = 1)
	BEGIN
		INSERT INTO ParticipantsForSpecial VALUES (@participantID, @specialeventID)
	END
END
GO

EXEC AddParticipantForSpecial_Individually 'AddParticipantForSpecial_Individually', 20, '11', '1', 'Thing', 'insert description here', '2015-10-27', 'Bistrita'
GO
EXEC AddParticipantForSpecial_Individually 'New participant2', 11, '11', '1', 'Thing', 'insert description here', '2023-10-27', 'Suceava'
GO
EXEC AddParticipantForSpecial_Individually 'New participant3', 23, '11', '1', 'invalid event', 'insert description here', '2023-10-27', 'Iasi'
GO

SELECT * FROM Participants
SELECT * FROM SpecialEvents
SELECT * FROM ParticipantsForSpecial
GO

SELECT * FROM Participants
GO

-- Stuff for 9.

-- dirty reads
-- first transaction
BEGIN TRANSACTION
UPDATE Participants 
SET name = 'ParticipantNameidk'
WHERE pid LIKE '6'
SELECT * FROM Participants
WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION

-- non-repeatable reads
-- first transaction
DECLARE @participantID CHAR(10)
SET @participantID = CAST((CAST((SELECT TOP 1 pid FROM Participants ORDER BY pid DESC) AS INT) + 1) AS CHAR(10))
INSERT INTO Participants Values (@participantID, 'New Participant')
BEGIN TRANSACTION
WAITFOR DELAY '00:00:05'
UPDATE Participants
SET name = 'Update Participants'
WHERE pid = @participantID
COMMIT TRANSACTION

SELECT * FROM Participants
DELETE FROM Participants WHERE pid LIKE '7'

-- phantom reads
-- first transaction
DECLARE @participantID CHAR(10)
SET @participantID = CAST((CAST((SELECT TOP 1 pid FROM Participants ORDER BY pid DESC) AS INT) + 1) AS CHAR(10))
BEGIN TRANSACTION
WAITFOR DELAY '00:00:04'
INSERT INTO Participants VALUES (@participantID, 'New Participant')
COMMIT TRANSACTION
 
-- deadlock
-- first transaction
BEGIN TRANSACTION
UPDATE Participants
SET name = 'Update t1'
WHERE pid LIKE '7'
WAITFOR DELAY '00:00:10'
UPDATE Organizers
SET name = 'Update t1'
WHERE oid LIKE '61'
COMMIT TRANSACTION

SELECT * FROM Participants
SELECT * FROM Organizers
GO

-- Stuff for 10.
-- Conflict solving.
ALTER DATABASE EventDatabase SET ALLOW_SNAPSHOT_ISOLATION ON
GO

USE EventDatabase
GO
WAITFOR DELAY '00:00:10'
BEGIN TRANSACTION
UPDATE Participants SET name = 'Update t1' WHERE pid LIKE '8'
WAITFOR DELAY '00:00:10'
COMMIT TRANSACTION

ALTER DATABASE EventDatabase SET ALLOW_SNAPSHOT_ISOLATION OFF
GO

SELECT * FROM Participants