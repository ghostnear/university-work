USE EXAM;
GO;
GO;

CREATE OR ALTER PROCEDURE TenPercentPriceMarkup(@manufacturerName varchar(max)) AS
    UPDATE Lenses
    SET Price = Price * 110 / 100
    WHERE Manufacturer in (
        SELECT id from Manufacturers WHERE Manufacturers.Company_Name = @manufacturerName
    )
    UPDATE Frames
    SET Price = Price * 110 / 100
    WHERE Manufacturer in (
        SELECT id from Manufacturers WHERE Manufacturers.Company_Name = @manufacturerName
    );

CREATE OR ALTER VIEW ShowSquareOrBlueLightOrders AS
    SELECT ID, Date from Orders WHERE
        Orders.Lenses in  (
            SELECT ID from Lenses WHERE Lenses.Type = 'blue-light'
        ) OR
        Orders.Frame in (
            SELECT ID from Frames WHERE Frames.Shape = 'square'
        );

CREATE OR ALTER FUNCTION ManufacturerSales(@manufacturerName varchar(max)) RETURNS real AS BEGIN
    return (SELECT SUM(Frames.Price + Lenses.Price) as Profit FROM Orders
    INNER JOIN Frames ON Orders.Frame = Frames.ID
    INNER JOIN Lenses ON Orders.Lenses = Lenses.ID
    WHERE Frames.Manufacturer in (SELECT ID FROM Manufacturers WHERE Company_Name = @manufacturerName) AND
          Lenses.Manufacturer in (SELECT ID FROM Manufacturers WHERE Company_Name = @manufacturerName));
END;