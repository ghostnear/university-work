CREATE DATABASE MangaDB;
GO
USE MangaDB
GO

CREATE TABLE MangaCover(
	ID int PRIMARY KEY IDENTITY,
	FilePath varchar(255)
);

CREATE TABLE Manga(
	-- Properties.
    ID int PRIMARY KEY IDENTITY,
    Title varchar(255) NOT NULL,
	ReadChapters int,
	TotalChapters int,
	MangaType varchar(255) NOT NULL,
	PhysicallyOwned bit DEFAULT 1,
	-- One to many.
	MCover int FOREIGN KEY REFERENCES MangaCover(ID)
);

CREATE TABLE MangaGenre(
	Naming varchar(255) PRIMARY KEY
);

CREATE TABLE MangasToGenres(
	MangaID int FOREIGN KEY REFERENCES Manga(ID),
	GenreID varchar(255) FOREIGN KEY REFERENCES MangaGenre(Naming)
);

CREATE TABLE MangaTag (
	Naming varchar(255) PRIMARY KEY,
);

CREATE TABLE MangaTagsToManga(
	MangaID int FOREIGN KEY REFERENCES Manga(ID),
	TagID varchar(255) FOREIGN KEY REFERENCES MangaTag(Naming)
);

CREATE TABLE Publisher(
	Naming varchar(255) PRIMARY KEY,
);

CREATE TABLE Author(
	Naming varchar(255) PRIMARY KEY,
	SocialLink varchar(255),
	PublisherID varchar(255) FOREIGN KEY REFERENCES Publisher(Naming)
);

CREATE TABLE MangasToAuthors(
	MangaID int FOREIGN KEY REFERENCES Manga(ID),
	AuthorID varchar(255) FOREIGN KEY REFERENCES Author(Naming),
	ReleaseDate datetime
);

CREATE TABLE Reader(
	ID int PRIMARY KEY IDENTITY,
	UserName varchar(255),
	PfPPath varchar(255)
);

CREATE TABLE ReaderToManga(
	MangaID int FOREIGN KEY REFERENCES Manga(ID),
	ReaderID int FOREIGN KEY REFERENCES Reader(ID),
	WhenAdded datetime
);