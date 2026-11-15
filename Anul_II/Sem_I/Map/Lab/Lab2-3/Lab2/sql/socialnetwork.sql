-- Baza de date a retelei de socializare
-- 1. pgAdmin: Databases -> Create -> Database..., numele: socialnetwork
-- 2. click dreapta pe socialnetwork -> Query Tool, deschidem fisierul si il rulam (F5)

-- id-ul il genereaza baza de date, de aceea INSERT-ul din aplicatie nu da id
CREATE TABLE IF NOT EXISTS users (
                                     id         BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                                     first_name VARCHAR NOT NULL,
                                     last_name  VARCHAR NOT NULL
);

-- o prietenie se salveaza o singura data, cu id1 < id2
-- fara ON DELETE CASCADE: prieteniile unui utilizator sters le sterge service-ul (vezi readme.txt)
CREATE TABLE IF NOT EXISTS friendships (
                                           id1          BIGINT REFERENCES users (id),
    id2          BIGINT REFERENCES users (id),
    friends_from TIMESTAMP NOT NULL,
    PRIMARY KEY (id1, id2),
    CHECK (id1 < id2)
    );
