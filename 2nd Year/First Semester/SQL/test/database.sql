USE EXAM;
GO;
GO;

CREATE TABLE Prescriptions(
    ID int PRIMARY KEY,
    Diagnosis varchar(max),
    Left_Diopter real,
    Right_Diopter real,

    CONSTRAINT CK_Diopter_Check CHECK (
        Left_Diopter >= -15 AND Left_Diopter <= 15 AND Right_Diopter >= -15 AND Right_Diopter <= 15
    )
);

DROP TABLE Prescriptions;

CREATE TABLE Manufacturers(
    ID int PRIMARY KEY,
    Company_Name varchar(256) UNIQUE,
    Address varchar(max),
    Email varchar(max)
);

DROP TABLE Manufacturers;

CREATE TABLE Lenses(
    ID int PRIMARY KEY,
    Name varchar(max),
    Type varchar(max),
    Price real,
    Manufacturer int FOREIGN KEY REFERENCES Manufacturers(ID),
    CONSTRAINT CK_Type_Check CHECK (
        Type in ('sunglasses', 'progressive', 'bifocals', 'blue-light')
    )
);

DROP TABLE Lenses;

CREATE TABLE Frames(
    ID int PRIMARY KEY,
    Name varchar(max),
    Description varchar(max),
    Color varchar(max),
    Shape varchar(max),
    Price real,
    Manufacturer int FOREIGN KEY REFERENCES Manufacturers(ID)
);

DROP TABLE Frames;

CREATE TABLE Orders(
    ID int PRIMARY KEY,
    Date datetime,
    Prescription int FOREIGN KEY REFERENCES Prescriptions(ID),
    Lenses int FOREIGN KEY REFERENCES Lenses(ID),
    Frame int FOREIGN KEY REFERENCES Frames(ID)
);

DROP TABLE Orders;