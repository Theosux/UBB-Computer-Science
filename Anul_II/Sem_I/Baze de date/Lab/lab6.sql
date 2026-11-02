GO
CREATE OR ALTER PROCEDURE usp_add.column AS
	DECLARE @suma INT;
	SELECT @suma = sum(val)
	FROM TABEL

	RETURN @suma

GO
DECLARE @REZULTAT INT
EXEC @REZULTAT = usp_add_column
SELECT @REZULTAT	-- se afiseaza 40
/*
TABEL
ID	VAL
1	14
2	15
3	11

suma = 40