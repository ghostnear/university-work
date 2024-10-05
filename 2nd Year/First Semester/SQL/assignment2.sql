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
UPDATE Manga SET MCover = 1
	WHERE MCover IS NULL;
UPDATE Manga SET TotalChapters = 750
	WHERE TotalChapters > 750;
UPDATE ReaderToManga SET ReadChapters = 115
	WHERE ReaderID BETWEEN 1 AND 2 AND ReadChapters > 100;

-- Deletes.
SELECT * FROM Publisher;
SELECT * FROM Reader;
DELETE FROM Publisher
	WHERE NAMING LIKE 'ToDelete%';
DELETE FROM ReaderToManga
	WHERE ReaderID = 3;
DELETE FROM Reader
	WHERE UserName IN ('Somebody', 'SomebodyElse');

-- a) 2 queries with the union operation; use UNION [ALL] and OR;
SELECT DISTINCT * FROM Manga
	WHERE MangaType = 'manga'
UNION
SELECT DISTINCT * FROM Manga
	WHERE MangaType = 'manhwa';

SELECT DISTINCT * FROM Manga
	WHERE MangaType = 'manga' OR MangaType = 'manhwa';

-- b) 2 queries with the intersection operation; use INTERSECT [ALL] and AND;
SELECT * FROM Manga
	WHERE MangaType = 'manga'
INTERSECT
SELECT * FROM Manga
	WHERE PhysicallyOwned = 1;

SELECT * FROM Manga
	WHERE MangaType = 'manga' AND PhysicallyOwned = 1;

-- c) 2 queries with the difference operation; use EXCEPT [ALL] and NOT;
SELECT * FROM Manga
	WHERE MangaType = 'manga'
EXCEPT
SELECT * FROM Manga
	WHERE PhysicallyOwned = 1;

SELECT * FROM Manga
	WHERE MangaType = 'manga' AND NOT PhysicallyOwned = 1;

-- d) 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two many-to-many relationships;
SELECT * FROM Manga
INNER JOIN MangaCover ON Manga.MCover = MangaCover.ID
INNER JOIN MangasToGenres ON Manga.ID = MangasToGenres.MangaID;

SELECT * FROM Manga
LEFT JOIN MangaCover ON Manga.MCover = MangaCover.ID;

SELECT * FROM Manga
RIGHT JOIN MangaCover ON Manga.MCover = MangaCover.ID;

SELECT * FROM Manga
FULL JOIN MangasToGenres ON Manga.ID = MangasToGenres.MangaID
FULL JOIN MangasToAuthors ON Manga.ID = MangasToAuthors.MangaID
FULL JOIN MangaTagsToManga ON Manga.ID = MangaTagsToManga.MangaID;

-- e) 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery must include a subquery in its own WHERE clause;
SELECT * FROM Manga
	WHERE Manga.ID IN (
		SELECT MangaID FROM MangasToGenres
			WHERE GenreID = 'Action'
	);
SELECT * FROM Manga
	WHERE Manga.ID IN (
		SELECT MangaID FROM MangasToGenres
			WHERE GenreID IN (
				SELECT GenreID FROM MangasToGenres
					WHERE MangaID = 1
			)
	);

-- f) 2 queries with the EXISTS operator and a subquery in the WHERE clause;
SELECT * FROM Manga
	WHERE EXISTS (
		SELECT * FROM Manga
			WHERE MangaType = 'manhwa'
	);

SELECT * FROM Manga WHERE EXISTS (
	SELECT * FROM Manga
		WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
)

-- g) 2 queries with a subquery in the FROM clause;
SELECT * FROM (SELECT * FROM Manga WHERE MangaType = 'manga') AS Manga WHERE Manga.PhysicallyOwned = 1;
SELECT * FROM (SELECT * FROM Manga WHERE MangaType = 'manga' AND PhysicallyOwned = 1) AS Manga WHERE Manga.TotalChapters > 100;

-- h) 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;
SELECT MangaType, COUNT(*) FROM Manga GROUP BY MangaType;
SELECT MangaType, COUNT(*) FROM Manga GROUP BY MangaType
	HAVING COUNT(*) > 5;
SELECT MangaType, COUNT(*) FROM Manga GROUP BY MangaType
	HAVING COUNT(*) > (
		SELECT COUNT(*) FROM Manga
			WHERE MangaType = 'manhwa'
	);
SELECT MangaType, COUNT(*) FROM Manga GROUP BY MangaType
	HAVING COUNT(*) > (
		SELECT COUNT(*) FROM Manga
			WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
	);

-- i) 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator);
SELECT * FROM Manga
	WHERE MangaType = 'manga' AND TotalChapters < ANY (
		SELECT TotalChapters FROM Manga
			WHERE MangaType = 'manhwa'
	);
SELECT * FROM Manga
	WHERE MangaType = 'manga' AND TotalChapters > ALL (
		SELECT TotalChapters FROM Manga
			WHERE MangaType = 'manhwa'
	);

SELECT * FROM Manga
	WHERE MangaType = 'manga' AND TotalChapters < ANY (
		SELECT TotalChapters FROM Manga
			WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
	);
SELECT * FROM Manga
	WHERE MangaType = 'manga' AND TotalChapters > ALL (
		SELECT TotalChapters FROM Manga
			WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
	);

-- rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.
SELECT * FROM Manga
	WHERE MangaType = 'manga' AND TotalChapters < (
		SELECT MAX(TotalChapters) FROM Manga
			WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
	);
SELECT * FROM Manga
	WHERE MangaType = 'manga' AND TotalChapters > (
		SELECT MIN(TotalChapters) FROM Manga 
			WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
	);

SELECT * FROM Manga
    WHERE MangaType = 'manga' AND TotalChapters < (
        SELECT TOP 1 TotalChapters FROM Manga
            WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
            ORDER BY TotalChapters DESC
    );
SELECT * FROM Manga
    WHERE MangaType = 'manga' AND TotalChapters > (
        SELECT TOP 1 TotalChapters FROM Manga
            WHERE MangaType = 'manhwa' AND PhysicallyOwned = 1
            ORDER BY TotalChapters ASC
    );