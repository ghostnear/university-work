CREATE DATABASE PlaneDB;
GO
USE PlaneDB
GO

CREATE TABLE Plane(
	ID int PRIMARY KEY IDENTITY,
	DEPARTURE varchar(255) NOT NULL,
	DESTINATION varchar(255) NOT NULL
);

CREATE TABLE Passenger(
	ID int PRIMARY KEY IDENTITY,
	FirstName varchar(255) NOT NULL,
	LastName varchar(255) NOT NULL,
	-- One to many.
	Plane int FOREIGN KEY REFERENCES Plane(ID)
);

INSERT INTO Plane(DEPARTURE, DESTINATION) VALUES
	('New York', 'Los Angeles'),
	('Los Angeles', 'New York'),
	('New York', 'Chicago'),
	('Chicago', 'New York');

INSERT INTO Passenger(FirstName, LastName, Plane) VALUES
	('John', 'Doe', 1),
	('Jane', 'Doe', 1),
	('John', 'Smith', 2),
	('Jane', 'Smith', 2),
	('John', 'Johnson', 3),
	('Jane', 'Johnson', 3),
	('John', 'Williams', 4),
	('Jane', 'Williams', 4);

SELECT * FROM Plane;
SELECT * FROM Passenger;