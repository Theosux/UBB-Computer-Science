USE Blog222;
SELECT * FROM CuvinteCheie;
GO
--crearea unei functii scalare
CREATE FUNCTION VerificareCuvantCheie (@nume VARCHAR(50))
RETURNS BIT 
AS
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	RETURN 1;
RETURN 0;
END;
GO
--Apelul functiei scalare
PRINT dbo.VerificareCuvantCheie('Halloween');
PRINT dbo.VerificareCuvantCheie('Latte');
GO
--modificarea definitiei functiei scalare
ALTER FUNCTION VerificareCuvantCheie(@nume VARCHAR(50))
RETURNS VARCHAR(30)
AS
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	RETURN 'Exista acest cuvant cheie';
RETURN 'Nu exista acest cuvant cheie';
END;
GO
--apelul functiei dupa modificarea definitiei
PRINT dbo.VerificareCuvantCheie('Halloween');
PRINT dbo.VerificareCuvantCheie('Latte');
--stergerea functiei scalare 
DROP FUNCTION dbo.VerificareCuvantCheie;
GO
--crearea unei functii inline table valued
CREATE FUNCTION ReturneazaArticole (@data_publicarii DATETIME)
RETURNS TABLE AS
RETURN SELECT titlu, continut, data_publicarii FROM Articole 
WHERE data_publicarii>@data_publicarii;
GO
INSERT INTO Articole (titlu, continut, data_publicarii) VALUES
('articol1','continut1','2002-02-02 12:00:00'),
('articol2','continut2','1999-02-03 11:11:11'),
('no name','continut','2022-02-02 12:00:12');
SELECT * FROM dbo.ReturneazaArticole('2000-02-02 12:12:12');
GO
--crearea unui view
CREATE VIEW vw_Articole 
AS
SELECT titlu, continut, data_publicarii FROM Articole
WHERE titlu LIKE 'a%';
GO
--interogarea view-ului
SELECT * FROM vw_Articole;
SELECT titlu FROM vw_Articole ORDER BY titlu;
GO
--modificarea definitiei view-ului
ALTER VIEW vw_Articole
AS
SELECT titlu, continut FROM Articole WHERE titlu LIKE 'no%';
GO
--interogarea view-ului dupa modificarea definitiei sale
SELECT * FROM vw_Articole;
--stergerea view-ului
DROP VIEW vw_Articole;