# Queries on the database

### Choose the birth numbers of those actors who only play plays written by William Shakespeare. (C; F1; G2; H2)
```SQL
select distinct rodne_cislo from
(select distinct * from predstaveni join divadelni_hra on predstaveni.id=divadelni_hra.id
                                   join autor on divadelni_hra.id_autor=autor.id_autor
                                   join herec_predstaveni on predstaveni.id_predstaveni=herec_predstaveni.id_predstaveni
                                   join herec on herec_predstaveni.id_osoba=herec.id_osoba
                                   where autor.jmeno='William' and autor.prijmeni='Shakespeare'

except

select distinct * from predstaveni P join divadelni_hra DH on P.id=DH.id
                                   join autor A on DH.id_autor=A.id_autor
                                   join herec_predstaveni HP on P.id_predstaveni=HP.id_predstaveni
                                   join herec H on HP.id_osoba=H.id_osoba                               
                                   where A.jmeno!='William' and A.prijmeni!='Shakespeare')rozdil;
```

### Choose those people who have never left a financial donation to the theater. (B; G1)

```SQL
select osoba.jmeno, osoba.prijmeni from osoba
where id_osoba not in(
    select id_osoba from financni_dar
);
```

### Write the names of plays that are performed only in hall number 1. (C; F2; H2)

```SQL
select nazev from
    predstaveni join divadelni_hra using (id)
        where predstaveni.cislo_salu=1
    
    except
    
    select nazev from predstaveni P join divadelni_hra DH using (id)
        where P.cislo_salu!=1;
```

### Choose the birth numbers of the actors who played in hall number 1. (A; F2; G2)

```SQL
select distinct rodne_cislo
from (
    select distinct *
    from predstaveni
    natural join herec_predstaveni
    where cislo_salu = 1
) R1
natural join herec;
```

### List the birth numbers of all the actors who have never acted in a play written by Karel Čapek. (A; F1; F2)

```SQL
select distinct rodne_cislo from predstaveni join herec_predstaveni on predstaveni.id_predstaveni=herec_predstaveni.id_predstaveni
                                             join herec on herec_predstaveni.id_osoba=herec.id_osoba
                                             natural join autor
                                             where autor.jmeno='Karel' and autor.prijmeni='Čapek';
```

### Select a performance (all attributes) that took place in hall number 2 and the number of occupied seats was greater than 30.

```SQL
select distinct * from predstaveni
                  where predstaveni.cislo_salu=2 and predstaveni.pocet_obsazenych_sedadel>30;
```

### Select all persons (name, surname, amount of financial donation) who gave the theater a financial donation of more than 1000 CZK. (A; F1)

```SQL
select distinct jmeno, prijmeni, vyse from financni_dar join osoba on financni_dar.id_osoba=osoba.id_osoba
                                      where financni_dar.vyse>1000;
```

### List the persons (name, surname) who only visited hall number 2 in the theater. (C; F1; H2)

```SQL
select distinct osoba.jmeno, osoba.prijmeni from predstaveni join osoba_predstaveni on predstaveni.id_predstaveni=osoba_predstaveni.id_predstaveni
                                            join osoba on osoba_predstaveni.id_osoba=osoba.id_osoba
                                            where predstaveni.cislo_salu=2
                                       
except
    
select distinct O.jmeno, O.prijmeni from predstaveni P join osoba_predstaveni OP on P.id_predstaveni=OP.id_predstaveni
                                    join osoba O on OP.id_osoba=O.id_osoba
                                    where P.cislo_salu!=2;
```

### Select all performances (all attributes) that were in hall number 3.

```SQL
select * from predstaveni
         where predstaveni.cislo_salu=3;
```

### Select all performances (hall number, length, start_time) in which a play by Zdeněk Svěrák was performed that lasted 60 minutes or more. (A; F1)

```SQL
select distinct predstaveni.cislo_salu, predstaveni.delka, predstaveni.cas_zacatku from predstaveni join divadelni_hra on predstaveni.id=divadelni_hra.id
                                                                                   join autor on divadelni_hra.id_autor=autor.id_autor
                                                                                   where autor.jmeno='Zdeněk' and autor.prijmeni='Svěrák' and predstaveni.delka>=60;
```

### Select the persons (name, surname) who were at all performances. (D1; G1; G4)

```SQL
select O.jmeno, O.prijmeni from osoba O
where not exists(
    select * from predstaveni P where not exists(
        select O from osoba_predstaveni OP
        where OP.id_predstaveni=P.id_predstaveni and O.id_osoba=OP.id_osoba
    )
);
```

### Calculate how many performances would be needed to play each play in each hall. (F3; I1)

```SQL
select count(*) as pocetPredstaveni
from sal cross join divadelni_hra;
```

### List all the authors (first and last name) and for each the play they wrote. (A; F4)

```SQL
select autor.jmeno, autor.prijmeni, divadelni_hra.nazev
from autor left join divadelni_hra on autor.id_autor=divadelni_hra.id_autor;
```

### Select all records of financial donations, including people who did not make a financial donation (financial donations cannot be made anonymously) (A; F5)

```SQL
select * from financni_dar full join osoba on financni_dar.id_osoba=osoba.id_osoba;
```

### Select all performances where the play Gazdina Roba was performed and an actor with the birth number 363-76-5739 played in it. (A; F1; F2; H1)

```SQL
select P.* from predstaveni P join divadelni_hra DH on P.id=DH.id
where DH.nazev='Gazdina Roba'

union

select P.* from predstaveni P join herec_predstaveni HP using (id_predstaveni) join herec H using (id_osoba)
where H.rodne_cislo='363-76-5739';
```

### Write down the number of financial gifts given by each person. (G3; I1)

```SQL
select *, (select count(*) from financni_dar where osoba.id_osoba=financni_dar.id_osoba) as pocetDaru
from osoba;
```

### List the actors (id, first name, last name) who played the stage play Endgame and did not leave a financial donation at the same time. (A; F2; G1; H3)

```SQL
select osoba.id_osoba, osoba.jmeno, osoba.prijmeni from osoba where id_osoba not in(
                                                   select id_osoba from financni_dar)
                          
intersect                          
                          
select O.id_osoba, O.jmeno, O.prijmeni from predstaveni P join divadelni_hra DH using (id)
                                       join herec_predstaveni HP using (id_predstaveni)
                                       join osoba O using (id_osoba)
                                       where DH.nazev='Endgame;
```

### For each play, write how many times it was performed and how many actors played it. (A; F2; I1; I2)

```SQL
select nazev, count(nazev) as mnozstvi, count(distinct id_osoba) as pocetHercu from divadelni_hra join predstaveni using (id)
                            join herec_predstaveni using (id_predstaveni)
group by nazev order by mnozstvi;
```

### Choose those people who have never left a financial donation to the theater. (A; F2; G1; G4; H2; J)

```SQL
select * from osoba
where not exists ( select 1 from financni_dar where osoba.id_osoba=financni_dar.id_osoba );

select * from osoba
where id_osoba not in(
    select id_osoba from financni_dar where id_osoba is not null
);

select * from osoba
except
select O.* from osoba O join financni_dar using (id_osoba);
```

### For each play, write how many times it has been performed in total. We are only interested in performances in hall number 2, and the play was played more than once, or just once. (A; F2; I1; I2; K)

```SQL
select nazev, count(nazev) as pocetHer
                           from divadelni_hra
                           join predstaveni using (id) 
                           where cislo_salu=2
                           group by divadelni_hra.nazev
                           having count(nazev) >= 1
                           order by pocetHer desc;
```

### Insert the last inserted performance record into the "predstaveni" table.

```SQL
begin;

select * from predstaveni;
insert into predstaveni (id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel)

select id, nazev_divadla, cislo_salu, delka, cas_zacatku, den_konani, pocet_obsazenych_sedadel from predstaveni
order by id_predstaveni desc
limit(1);
select * from predstaveni;
rollback;
```

### It is necessary to set the amount of all financial donations from the person with identification number 73 and 77 to 0. This money was stolen. (G1; O)

```SQL
begin;
select * from financni_dar where id_osoba=73 or id_osoba=77;
update financni_dar set vyse = 0
where id_osoba in(
select distinct id_osoba from financni_dar where id_osoba=77 or id_osoba=73
);
select * from financni_dar where id_osoba=73 or id_osoba=77;
rollback;
```
