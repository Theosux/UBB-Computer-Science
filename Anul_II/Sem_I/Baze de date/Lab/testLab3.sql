USE Restaurante;
GO

SELECT * FROM VersiuneBD;
EXEC SchimbaVersiune 0;
EXEC SchimbaVersiune 1;
EXEC SchimbaVersiune 2;
EXEC SchimbaVersiune 3;
EXEC SchimbaVersiune 4;
EXEC SchimbaVersiune 5;
SELECT * FROM Mese;
INSERT INTO Mese (numarul_mesei, id_restaurant) VALUES
(10, 2);
SELECT * FROM ComenziProduse;