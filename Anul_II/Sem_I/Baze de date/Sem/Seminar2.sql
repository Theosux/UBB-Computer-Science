--adaugarea datelor
INSERT INTO CuvinteCheie (nume) VALUES ('latte'),('spice');
--citirea datelor
SELECT * FROM CuvinteCheie;
SELECT cod_cc, nume FROM CuvinteCheie;
SELECT nume FROM CuvinteCheie;
SELECT nume AS cuvinte_cheie FROM CuvinteCheie;
SELECT nume cuvinte_cheie FROM CuvinteCheie;
SELECT * FROM CuvinteCheie WHERE nume='spice';
--actualizarea datelor
UPDATE CuvinteCheie SET nume='pumpkin';
SELECT * FROM CuvinteCheie;
UPDATE CuvinteCheie SET nume='spice'
WHERE cod_cc=2;
--stergerea datelor
DELETE FROM CuvinteCheie
WHERE cod_cc=1;
SELECT * FROM CuvinteCheie;
DELETE FROM CuvinteCheie;
SELECT * FROM CuvinteCheie;
INSERT INTO Utilizatori (nume_utilizator, email, parola)
VALUES ('user1','user1@gmail.com',N'qewretgrhjtuy435241'),
('user2','user2@gmail.com',N'sfdgretwrtwger');
SELECT * FROM Utilizatori;
UPDATE Utilizatori SET nume_utilizator='Bob',
email='bob@gmail.com' WHERE cod_u=2;
SELECT * FROM Utilizatori;