USE Restaurante;

--populam baza de date
INSERT INTO Restaurante (nume, rating, nr_angajati, nr_mese) VALUES
('La Mama', 5, 5, 3),
('Casa Ardeleana', 5, 5, 3),
('Pizza Napoli', 3, 3, 2),
('Sushi Zen', 2, 2, 2),
('Bistro Central', 4, 4, 2),
('Gradina Verde', 2, 2, 2),
('Steak House', 5, 4, 3);

--angajati
INSERT INTO Angajati (nume, functie) VALUES
('Ion Popescu', 'bucatar'),
('Maria Ionescu', 'ospatar'),
('Andrei Pop', 'ospatar'),
('Elena Dumitru', 'manager'),
('Mihai Stan', 'bucatar'),
('Ioana Rusu', 'ospatar'),
('Vlad Munteanu', 'barman'),
('Ana Moldovan', 'ospatar'),
('George Lazar', 'bucatar'),
('Cristina Pavel', 'manager'),
('Radu Toma', 'ospatar'),
('Diana Sima', 'barman'),
('Paul Matei', 'bucatar'),
('Alina Barbu', 'ospatar'),
('Sorin Ilie', 'manager'),
('Bianca Nistor', 'ospatar');

--clienti
INSERT INTO Clienti (nume, prenume, telefon, email) VALUES
('Popa', 'Andrei', '0741234567', 'andrei.p@gmail.com'),
('Marin', 'Ioana', '0752345678', 'ioana.m@yahoo.com'),
('Rusu', 'Vlad', '0763456789', 'vlad.rusu@gmail.com'),
('Stoica', 'Elena', '0724567890', 'elena.s@outlook.com'),
('Dobre', 'Mihai', '0735678901', 'mihai.d@gmail.com'),
('Lungu', 'Ana', '0746789012', NULL),
('Ene', 'Cristian', '0757890123', 'cristi.e@yahoo.com'),
('Neagu', 'Laura', '0768901234', 'laura.n@gmail.com'),
('Tudor', 'Bogdan', '0729012345', 'bogdan.t@gmail.com'),
('Florea', 'Raluca', '0730123456', 'raluca.f@yahoo.com');

--furnizori
INSERT INTO Furnizori (nume) VALUES
('Agro Transilvania'),
('Lactate Napoca'),
('Carmangeria Cluj'),
('Metro Cash'),
('Peste Proaspat SRL'),
('Vinuri Jidvei');

--mese (17 mese), numarul mesei e numarul din restaurantul respectiv
INSERT INTO Mese (nr_locuri, numarul_mesei, id_restaurant) VALUES
(4, 1, 1), (2, 2, 1), (6, 3, 1),
(4, 1, 2), (8, 2, 2), (2, 3, 2),
(4, 1, 3), (6, 2, 3),
(2, 1, 4), (4, 2, 4),
(4, 1, 5), (6, 2, 5),
(4, 1, 6), (2, 2, 6),
(4, 1, 7), (6, 2, 7), (8, 3, 7);

--meniu (7 restaurante = 7 meniuri), fiecare restaurant are un meniu
INSERT INTO Meniu (id_restaurante) VALUES
(1), (2), (3), (4), (5), (6), (7);

--restaurante - angajati (unii angajati lucreaza la 2 restaurante)
INSERT INTO Restaurante_Angajati (id_restaurante, id_angajati) VALUES
(1, 1), (1, 2), (1, 3), (1, 4), (1, 7),
(2, 5), (2, 6), (2, 8), (2, 10), (2, 11),
(3, 7), (3, 9), (3, 14),
(4, 13), (4, 16),
(5, 1), (5, 3), (5, 12), (5, 15),
(6, 13), (6, 16),
(7, 2), (7, 9), (7, 10), (7, 14);

--restaurante - clienti (clientii inregistrati la fiecare restaurant)
INSERT INTO Restaurante_clienti (id_restaurante, id_clienti) VALUES
(1, 1), (1, 2), (1, 3), (1, 5), (1, 8),
(2, 1), (2, 4), (2, 6), (2, 9),
(3, 3), (3, 5), (3, 7),
(4, 2), (4, 10),
(5, 8), (5, 9),
(6, 6),
(7, 1), (7, 3), (7, 4);

--restaurante - furnizori
INSERT INTO Restaurante_Furnizori (id_restaurante, id_furnizori) VALUES
(1, 1), (1, 3), (1, 4),
(2, 3), (2, 6),
(3, 2), (3, 4),
(4, 2), (4, 5),
(5, 1), (5, 4),
(6, 1),
(7, 3), (7, 6);

--categorii de produse (id 1-19)
INSERT INTO CategoriiProduse (nume, id_meniu) VALUES
('Ciorbe', 1), ('Fel principal', 1), ('Desert', 1),
('Ciorbe', 2), ('Fel principal', 2), ('Desert', 2),
('Pizza', 3), ('Paste', 3), ('Desert', 3),
('Sushi', 4), ('Supe', 4),
('Salate', 5), ('Fel principal', 5), ('Bauturi', 5),
('Salate', 6), ('Bauturi', 6),
('Steak', 7), ('Garnituri', 7), ('Bauturi', 7);

--produse
INSERT INTO Produse (nume, pret, descriere, id_categorii_produse) VALUES
('Ciorba de burta', 22, 'cu smantana si ardei', 1),
('Ciorba de perisoare', 19, 'reteta casei', 1),
('Sarmale cu mamaliga', 35, 'cu smantana', 2),
('Snitel de pui', 32, 'cu cartofi prajiti', 2),
('Papanasi', 25, 'cu dulceata', 3),
('Clatite', 18, 'cu ciocolata', 3),
('Ciorba radauteana', 24, 'cu smantana', 4),
('Supa de galuste', 18, 'supa de pui', 4),
('Tochitura', 42, 'cu mamaliga si ou', 5),
('Varza a la Cluj', 36, 'la cuptor', 5),
('Papanasi', 27, 'cu smantana', 6),
('Cozonac', 15, 'cu nuca', 6),
('Pizza Margherita', 30, 'rosii si mozzarella', 7),
('Pizza Diavola', 34, 'cu salam picant', 7),
('Pizza Capricciosa', 36, 'sunca si ciuperci', 7),
('Paste Carbonara', 32, 'cu bacon si ou', 8),
('Lasagna', 35, 'cu carne de vita', 8),
('Tiramisu', 22, 'cu mascarpone', 9),
('Panna cotta', 20, 'cu fructe de padure', 9),
('Maki somon', 28, '8 bucati', 10),
('California roll', 32, 'crab si avocado', 10),
('Nigiri ton', 30, '4 bucati', 10),
('Supa miso', 15, 'cu tofu', 11),
('Supa ramen', 29, 'cu porc si ou', 11),
('Salata Caesar', 27, 'cu pui si parmezan', 12),
('Salata greceasca', 24, 'cu branza feta', 12),
('Burger clasic', 38, 'cu cartofi', 13),
('Risotto cu ciuperci', 34, 'cu parmezan', 13),
('Limonada', 14, 'cu menta', 14),
('Espresso', 9, 'cafea scurta', 14),
('Salata de quinoa', 26, 'cu legume', 15),
('Bowl vegan', 31, 'cu tofu si avocado', 15),
('Smoothie verde', 18, 'spanac si mar', 16),
('Fresh portocale', 16, '300 ml', 16),
('Ribeye', 95, '300 g, vita Angus', 17),
('Muschi de vita', 88, '250 g', 17),
('Ceafa de porc', 45, '300 g', 17),
('Cartofi prajiti', 12, 'portie 200 g', 18),
('Legume la gratar', 15, 'de sezon', 18),
('Vin rosu', 22, 'pahar 150 ml', 19),
('Bere draft', 14, '500 ml', 19);

--rezervari
INSERT INTO Rezervari (data_rezervare, nr_persoane, id_client, id_masa) VALUES
('2026-10-24 19:00', 4, 1, 1),
('2026-10-24 20:00', 2, 2, 2),
('2026-10-24 21:00', 4, 5, 1),
('2026-10-03 19:30', 2, 1, 2),
('2026-09-26 18:00', 3, 1, 1),
('2026-09-20 13:00', 8, 4, 5),
('2026-09-20 19:00', 2, 9, 6),
('2026-10-25 20:00', 3, 6, 4),
('2026-09-12 19:00', 6, 3, 8),
('2026-10-04 20:30', 2, 7, 7),
('2026-10-08 19:00', 2, 2, 9),
('2026-10-10 18:30', 4, 10, 10),
('2026-09-15 12:30', 2, 8, 11),
('2026-10-22 19:00', 5, 9, 12),
('2026-09-27 20:00', 6, 1, 16),
('2026-10-11 20:00', 8, 3, 17),
('2026-10-17 19:30', 4, 4, 15),
('2026-10-14 19:00', 2, 5, 7),
('2026-10-27 13:00', 4, 8, 1),
('2026-09-19 20:00', 2, 5, 2);

--comenzi
INSERT INTO Comenzi (pret, id_angajat, id_client) VALUES
(85, 2, 1),
(42, 2, 5),
(120, 3, 2),
(64, 6, 4),
(230, 6, 9),
(55, 8, 6),
(98, 11, 4),
(150, 14, 3),
(72, 14, 7),
(45, 16, 10),
(88, 16, 2),
(310, 2, 1),
(67, 3, 8),
(40, 11, 9),
(190, 14, 3);

--recenzii
INSERT INTO Recenzii (rating, comentariu, data_recenzie, id_client, id_restaurant) VALUES
(5, 'Mancare excelenta, ca la mama acasa', '2026-09-27', 1, 1),
(4, 'Ciorba foarte buna, servire rapida', '2026-09-20', 5, 1),
(5, 'Cea mai buna tochitura din Cluj', '2026-09-21', 4, 2),
(4, 'Atmosfera placuta, portii mari', '2026-09-21', 9, 2),
(2, 'Pizza a venit rece', '2026-10-05', 7, 3),
(4, 'Pizza buna, preturi ok', '2026-09-13', 3, 3),
(3, 'Sushi bun, dar scump', '2026-10-09', 2, 4),
(1, 'Am asteptat o ora mancarea', '2026-10-11', 10, 4),
(4, 'Salate proaspete', '2026-09-16', 8, 5),
(2, 'Personal nepoliticos', '2026-10-02', 6, 6),
(5, 'Steak perfect gatit', '2026-09-28', 1, 7),
(5, 'Merita fiecare leu', '2026-10-12', 3, 7),
(4, 'Vin bun, servire ok', '2026-10-18', 4, 7);






-- INTEROGARI
/*
 - 5 interogări ce folosesc WHERE : 8
 - 3 interogări ce folosesc GROUP BY : 4
 - 2 interogări ce folosesc DISTINCT : 2
 - 2 interogări cu HAVING : 2
 - 7 interogări ce extrag informaţii din mai mult de 2 tabele( 3T ) : 8
 - 2 interogări pe tabele alfate în relaţie m-n. : 3
*/

SELECT * 
FROM Restaurante

-- 1. meniu sub un buget(30): WHERE, 3T
SELECT P.nume, P.pret, CP.nume AS categorie
FROM Restaurante R
  INNER JOIN Meniu M ON R.id = M.id_restaurante
  INNER JOIN CategoriiProduse CP ON M.id = CP.id_meniu
  INNER JOIN Produse P ON CP.id = P.id_categorii_produse
WHERE R.nume = 'La Mama' AND P.pret < 30
ORDER BY P.pret;

-- 2. rezervarile dintr-o seara: WHERE, 3T
SELECT C.nume, C.prenume, C.telefon, Me.numarul_mesei, Rez.nr_persoane, Rez.data_rezervare
FROM Restaurante R
	INNER JOIN Mese Me ON R.id = Me.id_restaurant
	INNER JOIN Rezervari Rez ON Me.id = Rez.id_masa
	INNER JOIN Clienti C ON Rez.id_client = C.id
WHERE R.nume = 'La Mama'
	AND Rez.data_rezervare BETWEEN '2026-10-24 00:00' AND '2026-10-24 23:50'
ORDER BY Rez.data_rezervare;

-- 3. unde lucreaza angajatii, mai exact bucatarii: WHERE, 3T, m-n
SELECT A.nume, R.nume AS restaurant
FROM Angajati A
	INNER JOIN Restaurante_Angajati RA ON A.id = RA.id_angajati
	INNER JOIN Restaurante R ON RA.id_restaurante = R.id
WHERE A.functie = 'bucatar'
ORDER BY A.nume;

-- 4. cati ospatari are un restaurant: WHERE, GROUP BY, 3T, m-n
SELECT R.nume, COUNT(*) AS nr_ospatari
FROM Restaurante R
	INNER JOIN Restaurante_Angajati RA ON R.id = RA.id_restaurante
	INNER JOIN Angajati A ON RA.id_angajati = A.id
WHERE A.functie = 'ospatar'
GROUP BY R.id, R.nume;

-- 5. ce restaurante au minim 1 recenzie si media minim 4 stele: GROUP BY, HAVING
SELECT R.nume, AVG(Rec.rating * 1.0) AS media, COUNT(*) AS nr_recenzii
FROM Restaurante R
	INNER JOIN Recenzii Rec ON R.id = Rec.id_restaurant
GROUP BY R.id, R.nume
HAVING AVG(Rec.rating) >= 4 AND COUNT(*) >= 1
ORDER BY media DESC;

-- 6. ce restaurante au avut minim 2 rezervari de minim 4 persoane: WHERE, GROUP BY, HAVING, 3T
SELECT R.nume, COUNT(*) AS rezervari
FROM Restaurante R
	INNER JOIN Mese Me ON R.id = Me.id_restaurant
	INNER JOIN Rezervari Rez ON Me.id = Rez.id_masa
WHERE Rez.nr_persoane >= 4
GROUP BY R.id, R.nume
HAVING COUNT(*) >= 2;

-- 7. clientii si nr lor de tlf care au facut o rezervare macar o data la un restaurant(La Mama): DISTINCT, WHERE, 3T
SELECT DISTINCT C.nume, C.prenume, C.telefon
FROM Clienti C
	INNER JOIN Rezervari Rez ON C.id = Rez.id_client
	INNER JOIN Mese Me ON Rez.id_masa = Me.id
	INNER JOIN Restaurante R ON Me.id_restaurant = R.id
WHERE R.nume = 'La Mama';

-- 8. ce posturi exista la un restaurant: DISTINCT, WHERE, 3T, m-n
SELECT DISTINCT A.functie as post
FROM Restaurante R
	INNER JOIN Restaurante_Angajati RA ON R.id = RA.id_restaurante
	INNER JOIN Angajati A ON RA.id_angajati = A.id
WHERE R.nume = 'Casa Ardeleana';

-- 9. cate comenzi a preluat fiecare angajat si ce valoare totala au: GROUP BY
SELECT A.nume, COUNT(*) AS nr_comenzi, SUM(Co.pret) AS valoare_totala
FROM Angajati A
	INNER JOIN Comenzi Co ON A.id = Co.id_angajat
GROUP BY A.id, A.nume
ORDER BY valoare_totala DESC;

-- 10. mese fara nicio rezervare: WHERE, 3T
SELECT R.nume AS restaurant, Me.numarul_mesei, Me.nr_locuri
FROM Restaurante R
	INNER JOIN Mese Me ON R.id = Me.id_restaurant
	LEFT JOIN Rezervari Rz ON Me.id = Rz.id_masa	-- pastram toate mesele
WHERE Rz.id IS NULL;

