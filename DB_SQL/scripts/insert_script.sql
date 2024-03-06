-- deleting all records from the tables
CREATE or replace FUNCTION clean_tables() RETURNS void AS $$
declare
  l_stmt text;
begin
  select 'truncate ' || string_agg(format('%I.%I', schemaname, tablename) , ',')
    into l_stmt
  from pg_tables
  where schemaname in ('public');

  execute l_stmt || ' cascade';
end;
$$ LANGUAGE plpgsql;
select clean_tables();

-- reset sequence

CREATE or replace FUNCTION restart_sequences() RETURNS void AS $$
DECLARE
i TEXT;
BEGIN
 FOR i IN (SELECT column_default FROM information_schema.columns WHERE column_default SIMILAR TO 'nextval%')
  LOOP
         EXECUTE 'ALTER SEQUENCE'||' ' || substring(substring(i from '''[a-z_]*')from '[a-z_]+') || ' '||' RESTART 1;';
  END LOOP;
END $$ LANGUAGE plpgsql;
select restart_sequences();
-- end of reset
-- end of deleting

-- inserting into table 'divadlo' (=theatre)
INSERT into divadlo (nazev_divadla) values ('Divadlo Pro Radost');

-- inserting into table 'sal' (=hall)
INSERT into sal (cislo_salu, kapacita) values (1, 40);
INSERT into sal (cislo_salu, kapacita) values (2, 50);
INSERT into sal (cislo_salu, kapacita) values (3, 20);
-- setting sequence for table 'sal' (=hall)
select setval(pg_get_serial_sequence('sal','cislo_salu'),3);


-- inserting into table 'osoba' (=person)
INSERT into osoba (id_osoba, prijmeni, jmeno) values (1, 'Iffe', 'Junina');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (2, 'Pfaff', 'Fey');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (3, 'Blakeden', 'Richart');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (4, 'MacCambridge', 'Nessy');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (5, 'Dike', 'Alister');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (6, 'Shropsheir', 'Ives');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (7, 'Sarson', 'Lind');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (8, 'Gatland', 'Dorine');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (9, 'Ennals', 'Sigvard');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (10, 'Skehens', 'Wilfred');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (11, 'Attwood', 'Nefen');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (12, 'Tourville', 'Emile');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (13, 'Meegan', 'Hallsy');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (14, 'Lapides', 'Corette');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (15, 'Darton', 'Demetra');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (16, 'Vedekhov', 'Trix');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (17, 'Longthorn', 'Sarah');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (18, 'Leyson', 'Amalita');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (19, 'Bercevelo', 'Byram');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (20, 'Stenners', 'Portia');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (21, 'Lochran', 'Clemente');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (22, 'Eakin', 'August');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (23, 'Lighton', 'Joly');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (24, 'Alywin', 'Doloritas');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (25, 'Rignall', 'Stan');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (26, 'Shakespeare', 'William');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (27, 'Svěrák', 'Zdeněk');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (28, 'Čapek', 'Karel');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (29, 'Beckett', 'Samuel');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (30, 'Jirásek', 'Alois');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (31, 'Nezval', 'Vítězslav');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (32, 'Werich', 'Jan');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (33, 'Preissová', 'Gabriela');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (34, 'Obray', 'Kathye');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (35, 'Dowdell', 'Jameson');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (36, 'Idale', 'Teirtza');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (37, 'Angeli', 'Daniel');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (38, 'Hawkswell', 'Vania');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (39, 'Hunnaball', 'Joeann');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (40, 'Havenhand', 'Gaylor');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (41, 'Sansom', 'Evelina');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (42, 'Slowcock', 'Frazier');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (43, 'Finlay', 'Dominique');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (44, 'Resun', 'Darsey');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (45, 'Strevens', 'Farlie');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (46, 'Atlay', 'Regan');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (47, 'Doddridge', 'Chip');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (48, 'Steane', 'Camila');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (49, 'Ofener', 'Julia');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (50, 'Nilges', 'Elane');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (51, 'Grundle', 'Stanley');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (52, 'Finnigan', 'Dilly');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (53, 'Balasin', 'Shem');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (54, 'Atlee', 'Davida');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (55, 'Gresch', 'Jacklin');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (56, 'Hallad', 'Nadya');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (57, 'Amyes', 'Odille');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (58, 'Ramsell', 'Terry');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (59, 'Shitliff', 'Latisha');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (60, 'Wane', 'Ree');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (61, 'Meller', 'Hernando');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (62, 'Ortell', 'Alvan');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (63, 'Biskup', 'Danny');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (64, 'Howgate', 'Barris');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (65, 'Tutt', 'Darius');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (66, 'Chesson', 'Sherri');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (67, 'Asple', 'Stesha');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (68, 'Dodswell', 'Jeth');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (69, 'Livesey', 'Amabelle');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (70, 'Brunsdon', 'Keith');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (71, 'Woolis', 'Glen');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (72, 'Schukraft', 'Daune');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (73, 'Huston', 'Raffaello');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (74, 'Loosely', 'Web');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (75, 'Van der Kruis', 'Agustin');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (76, 'Cancellieri', 'Krista');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (77, 'Risby', 'Karoly');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (78, 'Strutton', 'Madge');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (79, 'Sunock', 'Ham');
INSERT into osoba (id_osoba, prijmeni, jmeno) values (80, 'Blackshaw', 'Pernell');
-- setting sequence for table 'osoba' (=person)
select setval(pg_get_serial_sequence('osoba','id_osoba'),80);


-- inserting into table 'herec' (=actor)
INSERT into herec (id_osoba, rodne_cislo) values (1, '530-43-5137');
INSERT into herec (id_osoba, rodne_cislo) values (2, '307-80-7113');
INSERT into herec (id_osoba, rodne_cislo) values (3, '669-60-3729');
INSERT into herec (id_osoba, rodne_cislo) values (4, '363-76-5739');
INSERT into herec (id_osoba, rodne_cislo) values (5, null);
INSERT into herec (id_osoba, rodne_cislo) values (6, '883-85-5353');
INSERT into herec (id_osoba, rodne_cislo) values (7, '732-61-0667');
INSERT into herec (id_osoba, rodne_cislo) values (8, '256-88-6060');
INSERT into herec (id_osoba, rodne_cislo) values (9, '589-92-2424');
INSERT into herec (id_osoba, rodne_cislo) values (10, '440-45-9800');
INSERT into herec (id_osoba, rodne_cislo) values (11, '598-96-9849');
INSERT into herec (id_osoba, rodne_cislo) values (12, '778-88-5677');
INSERT into herec (id_osoba, rodne_cislo) values (13, '660-25-3769');
INSERT into herec (id_osoba, rodne_cislo) values (14, '665-18-5844');
INSERT into herec (id_osoba, rodne_cislo) values (15, '384-77-8449');
INSERT into herec (id_osoba, rodne_cislo) values (16, null);
INSERT into herec (id_osoba, rodne_cislo) values (17, '518-65-2550');
INSERT into herec (id_osoba, rodne_cislo) values (18, '604-40-0839');
INSERT into herec (id_osoba, rodne_cislo) values (19, '850-46-5585');
INSERT into herec (id_osoba, rodne_cislo) values (20, '377-10-2245');
-- setting sequence for table 'herec' (=actor)
select setval(pg_get_serial_sequence('herec','id_osoba'),20);


-- inserting into table 'autor' (=author)
INSERT into autor (id_autor, jmeno, prijmeni) values (26, 'William', 'Shakespeare');
INSERT into autor (id_autor, jmeno, prijmeni) values (27, 'Zdeněk', 'Svěrák');
INSERT into autor (id_autor, jmeno, prijmeni) values (28, 'Karel', 'Čapek');
INSERT into autor (id_autor, jmeno, prijmeni) values (29, 'Samuel', 'Beckett');
INSERT into autor (id_autor, jmeno, prijmeni) values (30, 'Alois', 'Jirásek');
INSERT into autor (id_autor, jmeno, prijmeni) values (31, 'Vítězslav', 'Nezval');
INSERT into autor (id_autor, jmeno, prijmeni) values (32, 'Jan', 'Werich');
INSERT into autor (id_autor, jmeno, prijmeni) values (33, 'Gabriela', 'Preissová');
-- setting sequence for table 'autor' (=author)
select setval(pg_get_serial_sequence('autor','id_autor'),33);


-- inserting into table 'divadelni_hra' (=play)
INSERT into divadelni_hra (id, id_autor, nazev) values (1, 26, 'Romeo and Juliet');
INSERT into divadelni_hra (id, id_autor, nazev) values (2, 29, 'Čekání na Godota');
INSERT into divadelni_hra (id, id_autor, nazev) values (3, 29, 'Endgame');
INSERT into divadelni_hra (id, id_autor, nazev) values (4, 27, 'Blaník');
INSERT into divadelni_hra (id, id_autor, nazev) values (5, 28, 'Bílá nemoc');
INSERT into divadelni_hra (id, id_autor, nazev) values (6, 30, 'Otec');
INSERT into divadelni_hra (id, id_autor, nazev) values (7, 31, 'Manon Lescaut');
INSERT into divadelni_hra (id, id_autor, nazev) values (8, 32, 'Fimfárum');
INSERT into divadelni_hra (id, id_autor, nazev) values (9, 33, 'Gazdina Roba');
INSERT into divadelni_hra (id, id_autor, nazev) values (10, 27, 'České nebe');
INSERT into divadelni_hra (id, id_autor, nazev) values (11, 33, 'Její Pastorkyňa');
INSERT into divadelni_hra (id, id_autor, nazev) values (12, 33, 'Cestou se štěstím');
INSERT into divadelni_hra (id, id_autor, nazev) values (13, 28, 'R.U.R.');
INSERT into divadelni_hra (id, id_autor, nazev) values (14, 32, 'Golem');
INSERT into divadelni_hra (id, id_autor, nazev) values (15, 30, 'Emigrant');
-- setting sequence for table 'divadelni_hra' (=play)
select setval(pg_get_serial_sequence('divadelni_hra','id'),15);


-- inserting into table 'predstaveni' (=performance)
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (1, 13, 'Divadlo Pro Radost', 1, 75, '20:45', 'Thursday', 28);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (2, 12, 'Divadlo Pro Radost', 1, 60, '20:15', 'Thursday', 26);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (3, 3, 'Divadlo Pro Radost', 1, 45, '19:30', 'Monday', null);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (4, 9, 'Divadlo Pro Radost', 1, 90, '20:00', 'Sunday', 38);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (5, 3, 'Divadlo Pro Radost', 1, 45, '20:45', 'Thursday', 31);

INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (6, 14, 'Divadlo Pro Radost', 2, 75, '19:30', 'Tuesday', 39);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (7, 15, 'Divadlo Pro Radost', 2, 45, '20:00', 'Monday', 46);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (8, 11, 'Divadlo Pro Radost', 2, 75, '19:15', 'Wednesday', 46);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (9, 9, 'Divadlo Pro Radost', 2, 60, '20:15', 'Monday', 30);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (10, 1, 'Divadlo Pro Radost', 2, 60, '20:15', 'Sunday', 43);

INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (11, 9, 'Divadlo Pro Radost', 3, 75, '20:45', 'Monday', 16);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (12, 8, 'Divadlo Pro Radost', 3, 90, '21:00', 'Thursday', 16);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (13, 4, 'Divadlo Pro Radost', 3, 60, '20:15', 'Friday', 17);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (14, 14, 'Divadlo Pro Radost', 3, 60, '20:30', 'Thursday', null);
INSERT into predstaveni (id_predstaveni, id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel) values (15, 2, 'Divadlo Pro Radost', 3, 60, '20:00', 'Tuesday', 19);
-- setting sequence for table 'predstaveni' (=performance)
select setval(pg_get_serial_sequence('predstaveni','id_predstaveni'),15);


-- inserting into table 'osoba_predstaveni' (=person_performance)
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 21);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 76);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 23);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 24);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 9);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 70);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 74);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 42);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 2);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 19);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 34);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 73);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 20);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 17);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 41);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 77);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 43);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 3);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (1, 78);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 78);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 48);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 42);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 35);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 36);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 77);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 2);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 65);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 22);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 23);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 45);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 54);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 47);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 25);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 11);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (2, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 37);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 25);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 9);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 12);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 19);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 1);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (3, 4);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 21);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 49);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 42);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 46);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 67);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 18);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 74);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 58);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 50);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 22);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 15);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 70);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 20);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 36);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 19);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 45);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 47);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 66);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 78);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (4, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 49);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 4);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 73);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 66);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 65);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 54);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 22);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 6);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 77);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 7);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 10);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 74);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 12);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 72);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 3);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 70);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 14);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 17);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 76);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (5, 68);
 
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 35);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 7);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 73);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 23);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 22);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 34);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 2);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 24);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 41);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 3);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 4);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 21);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 78);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 70);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 36);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 65);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 25);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 76);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 77);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 43);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 19);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 1);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 58);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 6);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (6, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 74);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 6);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 16);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 25);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 36);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 50);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 77);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 73);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 48);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 21);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 18);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 37);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 58);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 66);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 65);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 4);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 2);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 20);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 14);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 3);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 78);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 47);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 45);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 35);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 15);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (7, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 76);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 43);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 45);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 73);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 72);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 74);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 17);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 41);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 20);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 50);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 49);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 24);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 46);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 48);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 2);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 14);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 70);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 15);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 7);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 13);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 37);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 12);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 42);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 35);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 58);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 47);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (8, 61);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 49);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 76);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 5);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 25);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 1);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 58);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 65);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 10);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 54);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 4);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 16);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 3);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 34);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 46);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 66);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 50);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (9, 11);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 67);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 25);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 23);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 74);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 41);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 42);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 45);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 78);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 37);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 38);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 4);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 43);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 21);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 72);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 46);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 49);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 20);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 9);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 11);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 2);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 54);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 1);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 19);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 48);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 15);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 34);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 7);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (10, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 73);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 70);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 7);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 77);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 47);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 52);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 12);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 8);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (11, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 10);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 3);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 60);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 21);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 23);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 48);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 19);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 37);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (12, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 17);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 13);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 46);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 9);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 6);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 24);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 68);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 65);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 79);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 43);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (13, 39);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 36);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 63);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 56);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 51);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 10);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 57);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 55);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 59);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 69);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 35);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (14, 75);

INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 40);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 71);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 61);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 44);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 43);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 47);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 39);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 62);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 27);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 42);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 36);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 64);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 78);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 53);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 75);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 80);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 48);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 12);
INSERT into osoba_predstaveni (id_predstaveni, id_osoba) values (15, 41);

-- inserting into table 'herec_predstaveni' (=actor_performance)
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (14, 1);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (6, 1);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (13, 1);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (10, 2);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (14, 2);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (11, 2);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (15, 2);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (18, 3);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (11, 3);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (8, 3);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (6, 4);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (17, 4);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (5, 4);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (2, 5);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (15, 5);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (16, 5);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (10, 6);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (9, 6);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (13, 7);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (12, 7);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (1, 7);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (11, 8);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (12, 9);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (4, 9);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (2, 9);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (16, 10);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (10, 10);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (5, 11);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (2, 11);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (11, 11);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (11, 12);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (13, 12);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (6, 12);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (1, 12);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (12, 12);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (4, 13);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (5, 13);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (7, 14);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (12, 14);

INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (14, 15);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (17, 15);
INSERT into herec_predstaveni (id_osoba, id_predstaveni) values (5, 15);

-- inserting into table 'financni_dar' (=financial_gift)
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 21, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 76, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 23, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 24, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 42, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 2, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 34, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 73, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 20, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 61, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 3, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (1, 78, 50);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 2, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 65, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 22, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 55, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 23, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 54, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 51, 200);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 47, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (2, 75, 50);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 9, 1000);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 57, 200);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 64, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 12, 600);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 19, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 38, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 56, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (3, 4, 100);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 61, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 57, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 21, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 52, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 49, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 68, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 79, 500);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 38, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 20, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 36, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (4, 19, 250);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 49, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 39, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 61, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 73, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 66, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 65, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 60, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 54, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 22, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 80, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 3, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 71, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (5, 44, 2000);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 7, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 2, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 51, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 24, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 60, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 38, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 21, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 57, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 68, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 69, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 40, 150);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 59, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 58, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (6, 79, 50);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 8, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 77, 300);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 73, 500);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 79, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 48, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 4, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 68, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 55, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 44, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 47, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 52, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (7, 75, 1000);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 20, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 44, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 80, 2000);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 50, 1000);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 2, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 71, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 13, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 58, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (8, 61, 250);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (9, 5, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (9, 25, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (9, 3, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (9, 34, 200);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 42, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 59, 500);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 8, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 4, 1000);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 79, 300);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 2, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 7, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (10, 75, 200);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (11, 7, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (11, 80, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (11, 77, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (11, 69, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (11, 47, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (11, 8, 250);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (12, 37, 200);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (12, 75, 30);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (13, 9, 2000);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (13, 6, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (13, 24, 50);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (13, 68, 100);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (13, 80, 250);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (14, 61, 200);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (14, 55, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (14, 69, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (14, 35, 30);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (14, 75, 30);

INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (15, 47, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (15, 39, 500);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (15, 53, 250);
INSERT into financni_dar (id_predstaveni, id_osoba, vyse) values (15, 75, 3000);
