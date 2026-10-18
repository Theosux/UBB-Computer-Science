CREATE DATABASE parc;
USE parc;

CREATE TABLE categorii_de_vizitatori (
id INT PRIMARY KEY IDENTITY(1,1),
nume varchar(20)
);

CREATE TABLE vizitatori (
id INT PRIMARY KEY IDENTITY(1,1),
nume varchar(20),
email varchar(20),
id_categorie INT FOREIGN KEY REFERENCES categorii_de_vizitatori(id)
);

CREATE TABLE sectiuni (
id INT PRIMARY KEY IDENTITY(1,1),

);

CREATE TABLE atractii (
id INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(20),
descriere VARCHAR(100),
varsta_min INT,
id_sectiuni INT FOREIGN KEY REFERENCES sectiuni(id)
);

CREATE TABLE atractii_vizitatori (
id_vizitatori INT FOREIGN KEY REFERENCES vizitatori(id),
id_atractii INT FOREIGN KEY REFERENCES atractii(id),
CONSTRAINT pk_atractii_vizitatori PRIMARY KEY(id_vizitatori, id_atractii)
);