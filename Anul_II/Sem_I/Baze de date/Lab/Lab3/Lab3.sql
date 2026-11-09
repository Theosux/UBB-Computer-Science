USE Restaurante;
GO

-- 1. modifica tipul unei coloane
-- v0 -> v1: email VARCHAR(20) e prea scurt, il marim la VARCHAR(100)
CREATE OR ALTER PROCEDURE ModificaTipEmailClienti
AS
BEGIN
	ALTER TABLE Clienti
	ALTER COLUMN email VARCHAR(100);
	PRINT 'v1: Clienti.email este acum VARCHAR(100)';
END;
GO

-- 2. inversul lui 1
-- v1 -> v0: email inapoi la VARCHAR(20)
CREATE OR ALTER PROCEDURE RevinoTipEmailClienti
AS
BEGIN
	ALTER TABLE Clienti
	ALTER COLUMN email VARCHAR(20);
	PRINT 'v0: Clienti.email este din nou VARCHAR(20)';
END;
GO

-- 3. adauga o constrangere default
-- v1 -> v2: o masa noua are 4 locuri
CREATE OR ALTER PROCEDURE AdaugaDefaultNrLocuri
AS
BEGIN
	ALTER TABLE Mese
	ADD CONSTRAINT df_Mese_nr_locuri DEFAULT 4 FOR nr_locuri;
	PRINT 'v2: default 4 pentru Mese.nr_locuri';
END;
GO

-- 4. inversul lui 3
-- v2 -> v1: stergem constrangerea default (dupa nume!)
CREATE OR ALTER PROCEDURE StergeDefaultNrLocuri
AS
BEGIN
	ALTER TABLE Mese
	DROP CONSTRAINT df_Mese_nr_locuri;
	PRINT 'v1: default-ul de pe Mese.nr_locuri a fost sters';
END;
GO

-- 5. creeaza o tabela
-- v2 -> v3: tabela de legatura Comenzi <-> Produse (m:n), cu cantitate
CREATE OR ALTER PROCEDURE CreeazaTabelComenziProduse
AS
BEGIN
	CREATE TABLE ComenziProduse
	(
		id_comanda INT FOREIGN KEY REFERENCES Comenzi(id),
		id_produs INT FOREIGN KEY REFERENCES Produse(id),
		cantitate INT,
		CONSTRAINT pk_ComenziProduse PRIMARY KEY (id_comanda, id_produs)
	);
	PRINT 'v3: tabela ComenziProduse a fost creata';
END;
GO

-- 6. inversul lui 5
-- v3 -> v2: stergem tabela de legatura
CREATE OR ALTER PROCEDURE StergeTabelComenziProduse
AS
BEGIN
	DROP TABLE ComenziProduse;
	PRINT 'v2: tabela ComenziProduse a fost stearsa';
END;
GO

-- 7. adauga un camp nou
-- v3 -> v4: fiecare comanda trebuie sa stie in ce restaurant s-a dat
CREATE OR ALTER PROCEDURE AdaugaColoanaRestaurantComenzi
AS
BEGIN
	ALTER TABLE Comenzi
	ADD id_restaurant INT;
	PRINT 'v4: coloana Comenzi.id_restaurant a fost adaugata';
END;
GO

-- 8. inversul lui 7
-- v4 -> v3: stergem coloana
CREATE OR ALTER PROCEDURE StergeColoanaRestaurantComenzi
AS
BEGIN
	ALTER TABLE Comenzi
	DROP COLUMN id_restaurant;
	PRINT 'v3: coloana Comenzi.id_restaurant a fost stearsa';
END;
GO

-- 9. creeaza o cheie straina
-- v4 -> v5: Comenzi.id_restaurant devine cheie straina spre Restaurante(id)
CREATE OR ALTER PROCEDURE AdaugaFKComenziRestaurante
AS
BEGIN
	ALTER TABLE Comenzi
	ADD CONSTRAINT fk_Comenzi_Restaurante FOREIGN KEY (id_restaurant) REFERENCES Restaurante(id);
	PRINT 'v5: cheia straina fk_Comenzi_Restaurante a fost adaugata';
END;
GO

-- 10. inversul lui 9
-- v5 -> v4: stergem cheia straina (coloana ramane)
CREATE OR ALTER PROCEDURE StergeFKComenziRestaurante
AS
BEGIN
	ALTER TABLE Comenzi
	DROP CONSTRAINT fk_Comenzi_Restaurante;
	PRINT 'v4: cheia straina fk_Comenzi_Restaurante a fost stearsa';
END;
GO

-- 11. versionare: tabela VersiuneBD + procedura SchimbaVersiune
-- tabela care tine minte versiunea curenta a structurii (un singur rand)
CREATE TABLE VersiuneBD
(
	versiune INT
);
INSERT INTO VersiuneBD (versiune) VALUES (0);
GO

CREATE OR ALTER PROCEDURE SchimbaVersiune @versiune INT
AS
BEGIN
	IF @versiune < 0 OR @versiune > 5
	BEGIN
		RAISERROR('Versiunea trebuie sa fie intre 0 si 5!', 16, 1);
		RETURN;
	END;

	DECLARE @curenta INT;
	SELECT @curenta = versiune FROM VersiuneBD;

	-- mergem inainte: v+1, v+2, ... pana la @versiune
	WHILE @curenta < @versiune
	BEGIN
		SET @curenta = @curenta + 1;
		IF @curenta = 1 EXEC ModificaTipEmailClienti;
		IF @curenta = 2 EXEC AdaugaDefaultNrLocuri;
		IF @curenta = 3 EXEC CreeazaTabelComenziProduse;
		IF @curenta = 4 EXEC AdaugaColoanaRestaurantComenzi;
		IF @curenta = 5 EXEC AdaugaFKComenziRestaurante;
		UPDATE VersiuneBD SET versiune = @curenta;
	END;

	-- mergem inapoi: anulam versiunea curenta, apoi scadem
	WHILE @curenta > @versiune
	BEGIN
		IF @curenta = 5 EXEC StergeFKComenziRestaurante;
		IF @curenta = 4 EXEC StergeColoanaRestaurantComenzi;
		IF @curenta = 3 EXEC StergeTabelComenziProduse;
		IF @curenta = 2 EXEC StergeDefaultNrLocuri;
		IF @curenta = 1 EXEC RevinoTipEmailClienti;
		SET @curenta = @curenta - 1;
		UPDATE VersiuneBD SET versiune = @curenta;
	END;

	PRINT 'Baza de date este acum la versiunea:';
	PRINT @curenta;
END;
GO