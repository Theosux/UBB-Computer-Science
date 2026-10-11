/*
Restaurante
campuri: id int pk, nume varchar(20), rating int, nr angajati int, nr mese int

Mese
campuri: id int pk, nr locuri int, numarul mesei int, id_restaurant int

Angajati
campuri: id int pk, nume varchar(20), functie varchar(20)

Meniu
campuri: id int pk, id_restaurant int

Produse
campuri: id int pk, nume varchar(20), pret int, descriere varchar(20), id_categorii_produse int

Clienti
campuri: id int pk, nume varchar(20), prenume varchar(20), telefon varchar(11), email varchar(20)

Rezervari
campuri: id int pk, data_rezervare DATETIME, nr_persoane int, id_client int, id_masa int

Comenzi
campuri: id int pk, pret int, id_angajat int

Recenzii
campuri: id int pk, rating int, comentariu varchar(255), data_recenzie DATE, id_client int, id_restaurant int

Categorii Produse
campuri: id int pk, nume varchar(20), id_meniu int

Furnizori
campuri: id int pk, nume varchar(20)


Relatii:
Restaurante-Mese: 1:N
Restaurante-Angajati: M:N
Restaurante-Meniu: 1:1
Categorii_Produse-Produse: 1:N
Restaurante-Clienti: M:N
Restaurante-Rezervari: 1:N
Client-Rezervari: 1:N
Angajati-Comenzi: 1:N
Clienti-Comenzi: 1:N
Client-Recenzii: 1:N
Restaurant-Recenzii: 1:N
Restaurant-Categorii_Produse: 1:N
Restaurant-Furnizori: M:N
*/

CREATE DATABASE Restaurante;
USE Restaurante;

CREATE TABLE Restaurante
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(20),
	rating INT,
	nr_angajati INT,
	nr_mese INT
);

CREATE TABLE Mese
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nr_locuri INT,
	numarul_mesei INT,
	id_restaurant INT FOREIGN KEY REFERENCES Restaurante(id)
);

CREATE TABLE Angajati
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(20),
	functie VARCHAR(20)
);

CREATE TABLE Restaurante_Angajati
(
	id_restaurante INT FOREIGN KEY REFERENCES Restaurante(id),
	id_angajati  INT FOREIGN KEY REFERENCES Angajati(id)
	CONSTRAINT pk_Restaurante_Angajati PRIMARY KEY(id_restaurante, id_angajati)
);

CREATE TABLE Meniu
(
	id INT PRIMARY KEY IDENTITY(1,1),
	id_restaurante INT UNIQUE FOREIGN KEY REFERENCES Restaurante(id)
);

CREATE TABLE CategoriiProduse
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(20),
	id_meniu INT FOREIGN KEY REFERENCES Meniu(id)
);

CREATE TABLE Produse
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(20),
	pret INT,
	descriere VARCHAR(20),
	id_categorii_produse INT FOREIGN KEY REFERENCES CategoriiProduse(id)
);

CREATE TABLE Clienti
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(20),
	prenume VARCHAR(20),
	telefon VARCHAR(11),
	email VARCHAR(20)
);

CREATE TABLE Restaurante_clienti
(
	id_restaurante INT FOREIGN KEY REFERENCES Restaurante(id),
	id_clienti INT FOREIGN KEY REFERENCES Clienti(id),
	CONSTRAINT pk_Restaurante_clienti PRIMARY KEY(id_restaurante, id_clienti)

);

CREATE TABLE Rezervari
(
	id INT PRIMARY KEY IDENTITY(1,1),
	data_rezervare DATETIME,
	nr_persoane INT,
	id_client INT FOREIGN KEY REFERENCES Clienti(id),
	id_masa INT FOREIGN KEY REFERENCES Mese(id)
);

CREATE TABLE Comenzi
(
	id INT PRIMARY KEY IDENTITY(1,1),
	pret INT,
	id_angajat INT FOREIGN KEY REFERENCES Angajati(id),
	id_client INT FOREIGN KEY REFERENCES Clienti(id)
);

CREATE TABLE Recenzii
(
	id INT PRIMARY KEY IDENTITY(1,1),
	rating INT,
	comentariu VARCHAR(255),
	data_recenzie DATE,
	id_client INT FOREIGN KEY REFERENCES Clienti(id),
	id_restaurant INT FOREIGN KEY REFERENCES Restaurante(id)
);

CREATE TABLE Furnizori
(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(20)
);

CREATE TABLE Restaurante_Furnizori
(
	id_restaurante INT FOREIGN KEY REFERENCES Restaurante(id),
	id_furnizori INT FOREIGN KEY REFERENCES Furnizori(id)
	CONSTRAINT pk_Restaurante_Furnizori PRIMARY KEY(id_restaurante, id_furnizori)
);