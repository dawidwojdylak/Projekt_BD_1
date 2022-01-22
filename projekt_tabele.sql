drop table ksiazka cascade;
drop table e_czytnik cascade;
drop table "plyta_CD" cascade;
drop table autor cascade;
drop table wydawnictwo cascade;
drop table czytelnik cascade;
drop table karta_biblioteczna cascade;
drop table adres_czytelnika cascade;
drop table plyta_muzyka cascade;
drop table plyta_film cascade;
drop table sztuka cascade;

CREATE TABLE "ksiazka" (
  "ksiazka_id" int PRIMARY KEY,
  "tytul" varchar(50),
  "autor" int,
  "wydawnictwo" int
);

CREATE TABLE "e_czytnik" (
  "czytnik_id" int PRIMARY KEY,
  "producent" varchar(50),
  "model" varchar(50)
);

CREATE TABLE "plyta_CD" (
  "plyta_id" int --PRIMARY KEY--(foreign)
);

CREATE TABLE "autor" (
  "autor_id" int PRIMARY KEY,
  --"ksiazka_id" int,
  "imie" varchar(50),
  "nazwisko" varchar(50)
);

CREATE TABLE "wydawnictwo" (
  "wydawnictwo_id" int PRIMARY KEY,
  "nazwa" varchar(50)
);

CREATE TABLE "czytelnik" (
  "czytelnik_id" int PRIMARY KEY,
  "imie" varchar(20),
  "nazwisko" varchar(20),
  --"adres" int,
  "nr_telefonu" varchar(10)
);

CREATE TABLE "karta_biblioteczna" (
  "karta_id" int PRIMARY KEY,
  "wypozyczone" int,
  "naleznosc" varchar(50)
);

CREATE TABLE "adres_czytelnika" (
  "adres_id" int PRIMARY KEY,
  "miasto" varchar(50),
  "ulica" varchar(50),
  "numer_domu" varchar(6),
  "kod_pocztowy" varchar(6)
);

CREATE TABLE "plyta_muzyka" (
  "muzyka_id" int PRIMARY KEY,
  "wykonawca" varchar(50),
  "tytul" varchar(50)
);

CREATE TABLE "plyta_film" (
  "film_id" int PRIMARY KEY,
  "tytul" varchar(50),
  "rezyser" varchar(50)
);

CREATE TABLE "sztuka" (
  "id_sztuka" int PRIMARY KEY, --(foreign),
  "wypozyczona" boolean,
  "data_wyp" date,
  "termin_odd" date,
  "data_odd" date

);

--ALTER TABLE "sztuka" ADD CONSTRAINT sztuka_fk0 FOREIGN KEY ("id_sztuka") REFERENCES "ksiazka" ("ksiazka_id");
ALTER TABLE "ksiazka" ADD CONSTRAINT ksiazka_fk0 FOREIGN KEY ("autor") REFERENCES "autor" ("autor_id");
ALTER TABLE "ksiazka" ADD CONSTRAINT ksiazka_fk1 FOREIGN KEY ("wydawnictwo") REFERENCES "wydawnictwo" ("wydawnictwo_id");
--ALTER TABLE "sztuka" ADD CONSTRAINT sztuka_fk1 FOREIGN KEY ("id_sztuka") REFERENCES "e_czytnik" ("czytnik_id");
ALTER TABLE "sztuka" ADD CONSTRAINT sztuka_fk2 FOREIGN KEY ("id_sztuka") REFERENCES "plyta_CD" ("plyta_id");


ALTER TABLE "czytelnik" ADD FOREIGN KEY ("czytelnik_id") REFERENCES "adres_czytelnika" ("adres_id");
ALTER TABLE "karta_biblioteczna" ADD CONSTRAINT karta_biblioteczna_fk0 FOREIGN KEY ("karta_id") REFERENCES "czytelnik" ("czytelnik_id");
ALTER TABLE "karta_biblioteczna" ADD CONSTRAINT karta_biblioteczna_fk1 FOREIGN KEY ("wypozyczone") REFERENCES "sztuka" ("id_sztuka"); --
--ALTER TABLE "plyta_CD" ADD CONSTRAINT plyta_CD_fk0 FOREIGN KEY ("plyta_id") REFERENCES "plyta_muzyka" ("muzyka_id");
--ALTER TABLE "plyta_CD" ADD CONSTRAINT plyta_CD_fk1 FOREIGN KEY ("plyta_id") REFERENCES "plyta_film" ("film_id");




-- create user admin with password 'admin';

---

INSERT INTO autor (autor_id, imie, nazwisko) VALUES
(1, 'Tadeusz', 'Różewicz')
,(2, 'Carlo', 'Rovelli')
,(3, 'Ralf', 'Konersmann')
,(4, 'Siegfried', 'Zieliński')
,(5, 'Maria', 'Bogucka')
,(6, 'Marah', 'Woolf')
,(7, 'Charles', 'Dickens')
,(8, 'Ignacy', 'Krasicki')
,(9, 'Jerzy', 'Zych')
,(10, 'Antoni', 'Cieśla')
,(11, 'Robert', 'Borkowski')
,(12, 'Agatha', 'Christie')
,(13, 'Adam', 'Mickiewicz')
,(14, 'J. D.', 'Salinger')
,(15, 'Madeline', 'Miller');

INSERT INTO wydawnictwo (wydawnictwo_id, nazwa) VALUES
(1, 'Biuro Literackie')
,(2, 'Oficyna Naukowa')
,(3, 'IBIS')
,(4, 'Wydawnictwo AGH')
,(5, 'Nasza księgarnia')
,(6, 'Znak')
,(7, 'Fabryka Słów')
,(8, 'Buchmann')
,(9, 'Wydawnictwo Dolnośląskie')
,(10, 'Albatros');

INSERT INTO ksiazka (ksiazka_id, tytul, autor, wydawnictwo) VALUES
(1,'Ostatnia wolność', 1, 1)
,(2, 'Siedem krótkich lekcji fizyki', 2, 2)
,(3, 'Krytyka kultury', 3, 2)
,(4, 'Archeologia mediów', 4, 2)
,(5, 'Ludzie z Kresów', 5, 2)
,(6, 'Księżycowy czar', 6, 3)
,(7, 'Opowieść wigilijna', 7, 3)
,(8, 'Wybór bajek i satyr', 8, 3)
,(9, 'Analiza wad odlewów', 9, 4)
,(10, 'Elektrotechnika', 10, 4)
,(11, 'Konflikty współczesnego świata', 11, 4)
,(12, 'Inicjały zbrodni', 12, 9)
,(13, 'I nie było już nikogo', 12, 9)
,(14, 'Kurtyna', 12, 9)
,(15, 'Samotny dom', 12, 9)
,(16, 'Zaloty', 13, 6)
,(17, 'Pan Tadeusz', 13, 7)
,(18, 'Sen', 13, 7)
,(19, 'Buszujący w zbożu', 14, 10)
,(20, 'Pieśń o Achillesie', 15, 8);

---
INSERT INTO adres_czytelnika (adres_id, miasto, ulica, numer_domu, kod_pocztowy) VALUES
(1, 'Brzeg', 'Reymonta Władysława', '109', '49-305')
,(2, 'Poznań', 'Wołczyńska', '52', '60-003')
,(3, 'Kraków', 'Pod Wierzbami', '11', '30-798')
,(4, 'Katowice', 'Barwinków', '33', '40-748')
,(5, 'Świnoujście', 'Dworcowa', '41', '72-606')
,(6, 'Wrocław', 'Gruszowa', '85', '54-530')
,(7, 'Łódź', 'Bukowa', '98', '91-481')
,(8, 'Wrocław', 'Struga Andrzeja', '61', '50-228')
,(9, 'Kraków', 'Lubelska',' 118', '30-003');




INSERT INTO czytelnik (czytelnik_id, imie, nazwisko, nr_telefonu) VALUES
(1, 'Robert', 'Pietrzak', '984432123')
,(2, 'Lucjan', 'Marciniak',  '534324622')
,(3, 'Judyta', 'Jasińska', '234426645')
,(4, 'Anatol', 'Kalinowski', '256456920')
,(5, 'Filip', 'Mazurek', '526600435')
,(6, 'Patrycja', 'Sadowska', '400340030')
,(7, 'Monika', 'Stępień', '325324222')
,(8, 'Maria', 'Sawicka', '515345353')
,(9, 'Karolina', 'Zawadzka', '847399874');

INSERT INTO karta_biblioteczna (karta_id, wypozyczone, naleznosc) VALUES
(1, NULL, '0')
, (2, NULL, '0')
, (3, NULL, '10')
, (4, NULL, '0')
, (5, NULL, '20')
, (6, NULL, '32')
, (7, NULL, '14')
, (8, NULL, '0')
, (9, NULL, '0');

--- works till here

INSERT INTO e_czytnik (czytnik_id, producent, model) VALUES
(100, 'Amazon', 'Kindle 10')
, (101, 'Amazon', 'Kindle 10') 
, (102, 'Amazon', 'Kindle 10') 
, (103, 'Amazon', 'Kindle 10') 
, (104, 'Amazon', 'Kindle 10') 
, (105, 'Amazon', 'Oasis 3') 
, (106, 'Amazon', 'Oasis 3') 
, (107, 'Amazon', 'Oasis 3');

INSERT INTO "plyta_CD" (plyta_id) values
(1001), (1002), (1003), (1004), (1005), (1006), (1007), (1008), (1009), (1010),
(1011), (1012), (1013), (1014), (1015), (1016), (1017), (1018), (1019);


INSERT INTO plyta_film (film_id, tytul, rezyser) values
(1001, 'Zielona mila', 'Frank Darabont')
, (1002, 'Forrest Gump', 'Robert Zemeckis')
, (1003, 'Requiem dla snu', 'Darren Aronofsky')
, (1004, 'Milczenie owiec', 'Jonathan Demme')
, (1005, 'Titanic', 'James Cameron')
, (1006, 'Pianista', 'Roman Polański')
, (1007, 'Bękarty wojny', 'Quentin Tarantino')
, (1008, 'Piękny umysł', 'Ron Howard');

INSERT INTO plyta_muzyka (muzyka_id, wykonawca, tytul) values
(1009, 'The Beatles', 'Abbey Road')
, (1010, 'RHCP', 'Californication')
, (1011, 'Andrea Bocelli', 'Si')
, (1012, 'Rafał Blechacz', 'Chopin - Preludia')
, (1013, 'Perahia Murray', 'Bach: The French Suites PL')
, (1014, 'Queen', 'Forever')
, (1015, 'Pink Floyd', 'The Wall')
, (1016, 'Dżem', 'Złota kolekcja')
, (1017, 'Ed Sheeran', 'Divide')
, (1018, 'Abba', 'Gold Greatest Hits')
, (1019, 'Happysad', 'Podróże z i pod prąd');

--doesnt work
INSERT INTO sztuka (id_sztuka, wypozyczona, data_wyp, termin_odd, data_odd) VALUES 
(1, FALSE, NULL, NULL, NULL)
, (2, FALSE, NULL, NULL, NULL)
, (3, FALSE, NULL, NULL, NULL)
, (4, FALSE, NULL, NULL, NULL)
, (5, FALSE, NULL, NULL, NULL)
, (6, FALSE, NULL, NULL, NULL)
, (7, FALSE, NULL, NULL, NULL)
, (8, FALSE, NULL, NULL, NULL)
, (9, FALSE, NULL, NULL, NULL)
, (10, FALSE, NULL, NULL, NULL)
, (11, FALSE, NULL, NULL, NULL)
, (12, FALSE, NULL, NULL, NULL)
, (13, FALSE, NULL, NULL, NULL)
, (14, FALSE, NULL, NULL, NULL)
, (15, FALSE, NULL, NULL, NULL)
, (16, FALSE, NULL, NULL, NULL)
, (17, FALSE, NULL, NULL, NULL)
, (18, FALSE, NULL, NULL, NULL)
, (19, FALSE, NULL, NULL, NULL)
, (20, FALSE, NULL, NULL, NULL)
, (100, FALSE, NULL, NULL, NULL)
, (101, FALSE, NULL, NULL, NULL)
, (102, FALSE, NULL, NULL, NULL)
, (103, FALSE, NULL, NULL, NULL)
, (104, FALSE, NULL, NULL, NULL)
, (105, FALSE, NULL, NULL, NULL)
, (106, FALSE, NULL, NULL, NULL)
, (107, FALSE, NULL, NULL, NULL)
, (1001, FALSE, NULL, NULL, NULL)
, (1002, FALSE, NULL, NULL, NULL)
, (1003, FALSE, NULL, NULL, NULL)
, (1004, FALSE, NULL, NULL, NULL)
, (1005, FALSE, NULL, NULL, NULL)
, (1006, FALSE, NULL, NULL, NULL)
, (1007, FALSE, NULL, NULL, NULL)
, (1008, FALSE, NULL, NULL, NULL)
, (1009, FALSE, NULL, NULL, NULL)
, (1010, FALSE, NULL, NULL, NULL)
, (1011, FALSE, NULL, NULL, NULL)
, (1012, FALSE, NULL, NULL, NULL)
, (1013, FALSE, NULL, NULL, NULL)
, (1014, FALSE, NULL, NULL, NULL)
, (1015, FALSE, NULL, NULL, NULL)
, (1016, FALSE, NULL, NULL, NULL)
, (1017, FALSE, NULL, NULL, NULL)
, (1018, FALSE, NULL, NULL, NULL)
, (1019, FALSE, NULL, NULL, NULL);



-- widoki

-- DROP VIEW wypozyczone;

-- CREATE VIEW wypozyczone
-- AS
-- SELECT sztuka.id_sztuka, ksiazka.tytul
-- FROM sztuka INNER JOIN ksiazka ON sztuka.id_sztuka = ksiazka.ksiazka_id where sztuka.wypozyczona = true;

-- DROP VIEW dostepne;

-- CREATE VIEW dostepne 
-- AS
-- SELECT sztuka.id_sztuka, ksiazka.tytul
-- FROM sztuka INNER JOIN ksiazka ON sztuka.id_sztuka = ksiazka.ksiazka_id where sztuka.wypozyczona = false;

DROP VIEW wypozyczone;
CREATE VIEW wypozyczone
AS
SELECT sztuka.id_sztuka, ksiazka.tytul as ksiazka_tytul, e_czytnik.model, plyta_muzyka.tytul as muzyka_tytul, plyta_film.tytul as film_tytul
FROM sztuka FULL OUTER JOIN ksiazka ON sztuka.id_sztuka = ksiazka.ksiazka_id
FULL OUTER JOIN e_czytnik ON e_czytnik.czytnik_id = sztuka.id_sztuka
FULL OUTER JOIN plyta_muzyka ON plyta_muzyka.muzyka_id = sztuka.id_sztuka
FULL OUTER JOIN plyta_film ON plyta_film.film_id = sztuka.id_sztuka where sztuka.wypozyczona = true;

DROP VIEW dostepne;
CREATE VIEW dostepne
AS
SELECT sztuka.id_sztuka, ksiazka.tytul as ksiazka_tytul, e_czytnik.model, plyta_muzyka.tytul as muzyka_tytul, plyta_film.tytul as film_tytul
FROM sztuka FULL OUTER JOIN ksiazka ON sztuka.id_sztuka = ksiazka.ksiazka_id
FULL OUTER JOIN e_czytnik ON e_czytnik.czytnik_id = sztuka.id_sztuka
FULL OUTER JOIN plyta_muzyka ON plyta_muzyka.muzyka_id = sztuka.id_sztuka
FULL OUTER JOIN plyta_film ON plyta_film.film_id = sztuka.id_sztuka where sztuka.wypozyczona = false;

CREATE VIEW [Brazil Customers] AS
SELECT CustomerName, ContactName
FROM Customers
WHERE Country = 'Brazil';