-- The correctitude of the data is not guaranteed, trust me it's probably wrong.

-- Inserts.
INSERT INTO MangaCover(FilePath) VALUES
    ('./covers/unknown.jpg'),
    ('./covers/onepunchman.jpg'),
    ('./covers/berserk.jpg'),
    ('./covers/jojo.jpg'),
    ('./covers/blackclover.jpg');

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

INSERT INTO MangaGenre(Naming) VALUES
    ('Action'),
    ('Adventure'),
    ('Comedy'),
    ('Fantasy'),
    ('Slice of Life'),
    ('Supernatural');

INSERT INTO MangasToGenres(MangaID, GenreID) VALUES
    (1, 'Action'), (1, 'Comedy'),
    (2, 'Action'), (2, 'Adventure'), (2, 'Fantasy'),
    (3, 'Action'), (3, 'Adventure'), (3, 'Fantasy'), (3, 'Supernatural'),
    (4, 'Action'), (4, 'Adventure'),
    (5, 'Action'), (5, 'Adventure'), (5, 'Comedy');

-- Integrity failure
INSERT INTO MangasToGenres(MangaID, GenreID) VALUES
    (6, 'InexistentGenre'), (13, 'InexistendGenreAndManga'), (13, 'Comedy');

INSERT INTO MangaTag(Naming) VALUES
    ('Another World'), ('School'), ('Big Swords');

INSERT INTO MangaTagsToManga(MangaID, TagID) VALUES
    (1, 'Another World'), (1, 'School'),
    (2, 'Big Swords'),
    (3, 'School'),
    (4, 'Another World'),
    (9, 'Another World'), (9, 'School'), (9, 'Big Swords');

-- Integrity failure
INSERT INTO MangaTagsToManga(MangaID, TagID) VALUES
    (2, 'InexistentTag'), (11, 'InexistentTagAndManga'), (11, 'School');

INSERT INTO Publisher(Naming) VALUES
    ('Shueisha'), ('Square Enix'), ('Webtoon'), ('ToDelete1'), ('ToDelete2');

INSERT INTO Author(Naming, SocialLink) VALUES
    ('Unknown', 'https://twitter.com/unknown'),
    ('ONE', 'https://twitter.com/ONE_rakugaki'),
    ('Kentaro Miura', 'https://twitter.com/berserk_project'),
    ('Hirohiko Araki', 'https://twitter.com/araki_jojo'),
    ('Yuki Tabata', 'https://twitter.com/YukiTabata'),
    ('Eiichiro Oda', 'https://twitter.com/Eiichiro_Staff'),
    ('Yongje Park', 'https://twitter.com/TOG_info');

INSERT INTO MangasToAuthors(MangaID, AuthorID, PublisherID, ReleaseDate) VALUES
    (1, 'ONE', 'Shueisha', '2012-06-14'),
    (2, 'Kentaro Miura', 'Square Enix', '1989-08-25'),
    (3, 'Hirohiko Araki', 'Shueisha', '1987-01-01'),
    (4, 'Yuki Tabata', 'Shueisha', '2015-02-16'),
    (5, 'Eiichiro Oda', 'Shueisha', '1997-07-22'),
    (7, 'Unknown', 'Webtoon', '2016-07-25'),
    (8, 'Unknown', 'Webtoon', '2010-06-30'),
    (9, 'Yongje Park', 'Webtoon', '2011-04-08'),
    (10, 'Unknown', 'Webtoon', '2013-09-05');

-- Integrity failure
INSERT INTO MangasToAuthors(MangaID, AuthorID, PublisherID, ReleaseDate) VALUES
    (1, 'InexistentAuthor', 'Shueisha', '2012-06-14'),
    (2, 'Kentaro Miura', 'InexistentPublisher', '1989-08-25');

INSERT INTO Reader(UserName, PfPPath) VALUES
    ('Unknown', './pfp/unknown.jpg'),
    ('MangaFan', './pfp/mangafan.jpg'),
    ('Somebody', './pfp/unknown.jpg');

INSERT INTO ReaderToManga(MangaID, ReaderID, ReadChapters, WhenAdded) VALUES
    (2, 3, 3, '2021-10-1'),
    (3, 3, 20, '2022-10-12'),
    (4, 3, 9, '2023-12-1'),
    (5, 2, 100, '2023-10-1'),
    (6, 2, 126, '2022-10-15');

-- Updates.
SELECT * FROM Manga;
SELECT * FROM ReaderToManga;
UPDATE Manga SET MCover = 1 WHERE MCover IS NULL;
UPDATE Manga SET TotalChapters = 750 WHERE TotalChapters > 750;
UPDATE ReaderToManga SET ReadChapters = 115 WHERE ReaderID BETWEEN 1 AND 2 AND ReadChapters > 100;

-- Deletes.
SELECT * FROM Publisher;
SELECT * FROM Reader;
DELETE FROM Publisher WHERE NAMING LIKE 'ToDelete%';
DELETE FROM ReaderToManga WHERE ReaderID = 3;
DELETE FROM Reader WHERE UserName IN ('Somebody', 'SomebodyElse');
