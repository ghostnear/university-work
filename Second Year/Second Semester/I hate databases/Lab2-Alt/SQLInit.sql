CREATE DATABASE MangaDB;
GO
USE MangaDB
GO

CREATE TABLE Manga(
	-- Properties.
    ID int PRIMARY KEY IDENTITY,
    Title varchar(255) NOT NULL,
	TotalChapters int,
	MangaType varchar(255) NOT NULL,
	PhysicallyOwned bit,
);

CREATE TABLE MangaCover(
	ID int PRIMARY KEY IDENTITY,
	FilePath varchar(255),
	-- One to many.
	Manga int FOREIGN KEY REFERENCES Manga(ID)
);

INSERT INTO Manga(Title, TotalChapters, MangaType, PhysicallyOwned) VALUES
    ('One Punch Man', 23, 'manga', 1),
    ('Berserk', 40, 'manga', 0),
    ('Jojos Bizarre Adventure', 130, 'manga', 1),
    ('Black Clover', 27, 'manga', 1),
    ('One Piece', 1000, 'manga', 1),
    ('Bleach', 686, 'manga', 0),
    ('Solo Leveling', 150, 'manhwa', 0),
    ('Tower of God', 500, 'manhwa', 1),
    ('The God of High School', 500, 'manhwa', 0),
    ('The Gamer', 400, 'manhwa', 1);

INSERT INTO MangaCover(FilePath, Manga) VALUES
    ('./cover/opm.jpg', 1),
	('./cover/berserk.jpg', 2),
	('./cover/jojo.jpg', 3),
	('./cover/blackclover.jpg', 4),
	('./cover/onepiece.jpg', 5),
	('./cover/bleach.jpg', 6),
	('./cover/sololeveling.jpg', 7),
	('./cover/towerofgod.jpg', 8),
	('./cover/godofhighschool.jpg', 9),
	('./cover/thegamer.jpg', 10);