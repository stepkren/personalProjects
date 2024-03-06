DROP FUNCTION IF EXISTS remove_all();

CREATE or replace FUNCTION remove_all() RETURNS void AS $$
DECLARE
    rec RECORD;
    cmd text;
BEGIN
    cmd := '';

    FOR rec IN SELECT
            'DROP SEQUENCE ' || quote_ident(n.nspname) || '.'
                || quote_ident(c.relname) || ' CASCADE;' AS name
        FROM
            pg_catalog.pg_class AS c
        LEFT JOIN
            pg_catalog.pg_namespace AS n
        ON
            n.oid = c.relnamespace
        WHERE
            relkind = 'S' AND
            n.nspname NOT IN ('pg_catalog', 'pg_toast') AND
            pg_catalog.pg_table_is_visible(c.oid)
    LOOP
        cmd := cmd || rec.name;
    END LOOP;

    FOR rec IN SELECT
            'DROP TABLE ' || quote_ident(n.nspname) || '.'
                || quote_ident(c.relname) || ' CASCADE;' AS name
        FROM
            pg_catalog.pg_class AS c
        LEFT JOIN
            pg_catalog.pg_namespace AS n
        ON
            n.oid = c.relnamespace WHERE relkind = 'r' AND
            n.nspname NOT IN ('pg_catalog', 'pg_toast') AND
            pg_catalog.pg_table_is_visible(c.oid)
    LOOP
        cmd := cmd || rec.name;
    END LOOP;

    EXECUTE cmd;
    RETURN;
END;
$$ LANGUAGE plpgsql;
select remove_all();


CREATE TABLE autor (
    id_autor SERIAL NOT NULL,
    jmeno VARCHAR(40) NOT NULL,
    prijmeni VARCHAR(40) NOT NULL
);
ALTER TABLE autor ADD CONSTRAINT pk_autor PRIMARY KEY (id_autor);

CREATE TABLE divadelni_hra (
    id SERIAL NOT NULL,
    id_autor INTEGER NOT NULL,
    nazev VARCHAR(70) NOT NULL
);
ALTER TABLE divadelni_hra ADD CONSTRAINT pk_divadelni_hra PRIMARY KEY (id);

CREATE TABLE divadlo (
    nazev_divadla VARCHAR(50) NOT NULL
);
ALTER TABLE divadlo ADD CONSTRAINT pk_divadlo PRIMARY KEY (nazev_divadla);

CREATE TABLE financni_dar (
    id_predstaveni INTEGER NOT NULL,
    id_osoba INTEGER NOT NULL,
    vyse INTEGER NOT NULL
);
ALTER TABLE financni_dar ADD CONSTRAINT pk_financni_dar PRIMARY KEY (id_predstaveni, id_osoba);
ALTER TABLE financni_dar ADD CONSTRAINT u_fk_financni_dar_osoba_predsta UNIQUE (id_predstaveni, id_osoba);

CREATE TABLE herec (
    id_osoba INTEGER NOT NULL,
    rodne_cislo VARCHAR(20)
);
ALTER TABLE herec ADD CONSTRAINT pk_herec PRIMARY KEY (id_osoba);

CREATE TABLE osoba (
    id_osoba SERIAL NOT NULL,
    prijmeni VARCHAR(40) NOT NULL,
    jmeno VARCHAR(40) NOT NULL
);
ALTER TABLE osoba ADD CONSTRAINT pk_osoba PRIMARY KEY (id_osoba);

CREATE TABLE osoba_predstaveni (
    id_predstaveni INTEGER NOT NULL,
    id_osoba INTEGER NOT NULL
);
ALTER TABLE osoba_predstaveni ADD CONSTRAINT pk_osoba_predstaveni PRIMARY KEY (id_predstaveni, id_osoba);

CREATE TABLE predstaveni (
    id_predstaveni SERIAL NOT NULL,
    id INTEGER NOT NULL,
    nazev_divadla VARCHAR(50) NOT NULL,
    cislo_salu INTEGER NOT NULL,
    delka INTEGER NOT NULL,
    cas_zacatku TIME NOT NULL,
    den_konani VARCHAR(15) NOT NULL,
    pocet_obsazenych_sedadel INTEGER
);
ALTER TABLE predstaveni ADD CONSTRAINT pk_predstaveni PRIMARY KEY (id_predstaveni);

CREATE TABLE sal (
    cislo_salu SERIAL NOT NULL,
    kapacita INTEGER NOT NULL
);
ALTER TABLE sal ADD CONSTRAINT pk_sal PRIMARY KEY (cislo_salu);

CREATE TABLE herec_predstaveni (
    id_osoba INTEGER NOT NULL,
    id_predstaveni INTEGER NOT NULL
);
ALTER TABLE herec_predstaveni ADD CONSTRAINT pk_herec_predstaveni PRIMARY KEY (id_osoba, id_predstaveni);

ALTER TABLE divadelni_hra ADD CONSTRAINT fk_divadelni_hra_autor FOREIGN KEY (id_autor) REFERENCES autor (id_autor) ON DELETE CASCADE;

ALTER TABLE financni_dar ADD CONSTRAINT fk_financni_dar_osoba_predstave FOREIGN KEY (id_predstaveni, id_osoba) REFERENCES osoba_predstaveni (id_predstaveni, id_osoba) ON DELETE CASCADE;

ALTER TABLE herec ADD CONSTRAINT fk_herec_osoba FOREIGN KEY (id_osoba) REFERENCES osoba (id_osoba) ON DELETE CASCADE;

ALTER TABLE osoba_predstaveni ADD CONSTRAINT fk_osoba_predstaveni_predstaven FOREIGN KEY (id_predstaveni) REFERENCES predstaveni (id_predstaveni) ON DELETE CASCADE;
ALTER TABLE osoba_predstaveni ADD CONSTRAINT fk_osoba_predstaveni_osoba FOREIGN KEY (id_osoba) REFERENCES osoba (id_osoba) ON DELETE CASCADE;

ALTER TABLE predstaveni ADD CONSTRAINT fk_predstaveni_divadelni_hra FOREIGN KEY (id) REFERENCES divadelni_hra (id) ON DELETE CASCADE;
ALTER TABLE predstaveni ADD CONSTRAINT fk_predstaveni_divadlo FOREIGN KEY (nazev_divadla) REFERENCES divadlo (nazev_divadla) ON DELETE CASCADE;
ALTER TABLE predstaveni ADD CONSTRAINT fk_predstaveni_sal FOREIGN KEY (cislo_salu) REFERENCES sal (cislo_salu) ON DELETE CASCADE;

ALTER TABLE herec_predstaveni ADD CONSTRAINT fk_herec_predstaveni_herec FOREIGN KEY (id_osoba) REFERENCES herec (id_osoba) ON DELETE CASCADE;
ALTER TABLE herec_predstaveni ADD CONSTRAINT fk_herec_predstaveni_predstaven FOREIGN KEY (id_predstaveni) REFERENCES predstaveni (id_predstaveni) ON DELETE CASCADE;
