/*
Samsari(vand masini)
campuri: id int pk(uq, not null), nume varchar(20), rating int

Masini
campuri: id int pk, model varchar, culoare varchar

Reprezentanta
campuri: id int pk, nume varchar, adresa varchar

Oferte
campuri: id int pk, pret float, negociabil bit(boolean), id_samsar int, id_masina int

Clienti
campuri: id int pk, nume varchar

Piese
campuri: id int pk, pret int, denumire varchar


relatii:

Samsari-Masini: 1:N(one-to-many)
Reprezentanta-Samsari: M:N(many-to-many)
Samsari-Oferte: 1:N(one-to-many)
Samsari-Clienti: M:N(many-to-many)
Masini-Piese: M:N(many-to-many)
*/

CREATE DATABASE VanzareMasini;
USE VanzareMasini;

CREATE TABLE Samsari
(
id INT PRIMARY KEY IDENTITY(1,1), --1 - de la cat pornim 1 - cu cat crestem; autoincrementare pt id
nume VARCHAR(20),
rating INT
);

CREATE TABLE Masini
(
id INT PRIMARY KEY IDENTITY(1,1),
model VARCHAR(20),
culoare VARCHAR,
id_samsar INT FOREIGN KEY REFERENCES Samsari(id)
);

CREATE TABLE Reprezentanta
(
id INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(30),
adresa VARCHAR(50)
);

CREATE TABLE Oferte
(
id INT PRIMARY KEY IDENTITY(1,1),
pret FLOAT,
negociabil BIT,
id_samsar INT FOREIGN KEY REFERENCES Samsari(id),
id_masina INT FOREIGN KEY REFERENCES Masini(id)
);

CREATE TABLE Client
(
id INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(20)
);

CREATE TABLE Piese
(
id INT PRIMARY KEY IDENTITY(1,1),
pret FLOAT,
denumire VARCHAR(30)
);

CREATE TABLE Masini_Piese
(
id_masina INT FOREIGN KEY REFERENCES Masini(id),
id_piesa INT FOREIGN KEY REFERENCES Piese(id),
CONSTRAINT pk_Masina_Piese PRIMARY KEY(id_masina, id_piesa)
);

CREATE TABLE Colaborari
(
id INT PRIMARY KEY IDENTITY(1,1),
id_reprezentanta INT FOREIGN KEY REFERENCES Reprezentanta(id),
id_samsar INT FOREIGN KEY REFERENCES Samsari(id),
data_inceput_contract DATETIME,
data_incheiere_contract DATETIME
);