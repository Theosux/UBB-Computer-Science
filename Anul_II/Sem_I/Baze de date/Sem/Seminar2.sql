	--adaugarea datelor
	INSERT INTO CuvinteCheie (nume) VALUES ('latte'),('spice');
	--citirea datelor
	SELECT * FROM CuvinteCheie;
	SELECT cod_cc, nume FROM CuvinteCheie;
	SELECT nume FROM CuvinteCheie;
	SELECT nume AS cuvinte_cheie FROM CuvinteCheie;
	SELECT * FROM CuvinteCheie WHERE nume='spice';
	--actualizarea datelor
	UPDATE CuvinteCheie SET nume='pumpkin';
	UPDATE CuvinteCheie Set nume='spice'
	WHERE cod_cc=2;
	--stergerea datelor
	DELETE FROM CuvinteCheie
	WHERE cod_cc=1;
	SELECT * FROM CuvinteCheie;