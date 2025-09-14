-- Je pense que ma procédure est efficace car elle réalise un minimul de wbImprt (8, autant d'importations qu'il y a de fichiers à importer)
-- et qu'elle n'appelle aucun script extérieur
-- Je pense que ma manière de peupler chaque classe est plutôt optimale sauf pour la classe _resultat
-- où j'altère chaque moyenne de chaque module pour retirer les éventuels ~,-c- ou NI qui peuvent ne pas être présent
-- de plus, la classe _resultat utilise 283 commandes, ce qui me semble très peu optimimisé
-- il existe sûrement une méthode bien plus simple et bien moins longue pour faire cela mais
-- ma méthode fonctionne et j'ai déjà passé pas mal de temps sur cette partie de cette SAÉ donc
-- je vais m'en contenter


-- Pour peupler la base, veuillez remplacer /media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/ par le chemin du dossier contenant les .csv
-- et veuillez exécuter sae204_partie2_schema.sql (je n'y ai pas touché, c'est le script trouvable sur Moodle) 
-- avant d'exécuter le script contenu dans ce fichier.




ALTER TABLE _candidat DROP ville_etablissement;
ALTER TABLE _candidat ADD ville_etablissement character varying(100);

ALTER TABLE _candidat DROP ine;
ALTER TABLE _candidat ADD ine character(11) NOT NULL;


ALTER TABLE ONLY partie2._candidat ADD CONSTRAINT fk_candidat_individu FOREIGN KEY (ine) REFERENCES partie2._individu(ine);


ALTER TABLE _programme DROP coefficient;
ALTER TABLE _programme ADD coefficient numeric(3,1);



DROP TABLE IF EXISTS partie2._temp_programme;
DROP TABLE IF EXISTS partie2._temp_candidature;
DROP TABLE IF EXISTS partie2._temp_module;

CREATE TABLE partie2._temp_programme (
    coefficient numeric(3,1),
    num_semestre character varying(5),
    annee_univ character(9),
    id_module character varying(6)
);

WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_programme.csv
         -type=text
         -table=_temp_programme
         -schema=partie2
         -delimiter=';'
         -header=true
         -fileColumns=annee_univ,num_semestre,id_module,coefficient
         ;


CREATE TABLE partie2._temp_module (
    id_module character varying(6) NOT NULL,
    nom_module character varying(150),
    id_ue character(4)
);


WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/ppn.csv
         -type=text
         -table=_temp_module
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=id_module,nom_module,id_ue
         ;

CREATE TABLE partie2._temp_candidature (
    numero_candidat serial,
    classement character varying(100),
    boursier character varying(100),
    profil_candidat character varying(100) NOT NULL,
    libelle_etablissement character varying(100),
    departement_etablissement character varying(100),
    commune_etablissement character varying(100),
    niveau_etudes_actuel character varying(100),
    type_formation character varying(150),
    serie character varying(150),
    dominante character varying(150),
    diplome_specialite character varying(150),
    lv1 character varying(100),
    lv2 character varying(100),
    numero_ine character(11),
    nom character varying(50) NOT NULL,
    prenom character varying(50) NOT NULL,
    date_naissance date NOT NULL,
    code_postal character varying(10),
    ville character varying(50),
    sexe character varying(50) NOT NULL,
    nationalite character varying(50) NOT NULL  
);


WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_candidatures.csv
         -type=text
         -table=_temp_candidature
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=classement,boursier,profil_candidat,libelle_etablissement,departement_etablissement,commune_etablissement,niveau_etudes_actuel,type_formation,serie,dominante,diplome_specialite,lv1,lv2,numero_ine,nom,prenom,sexe,date_naissance,nationalite,code_postal,ville
         ;
         
DROP TABLE IF EXISTS partie2._temp_etudiant;
CREATE TABLE partie2._temp_etudiant (
    num_etudiant character(11) NOT NULL,
    cat_socio_etudiant character varying(100),
    cat_socio_parent character varying(100),
    bourse_superieur character varying(100),
    mention character varying(100),
    bac character varying(100) NOT NULL,
    dominante_bac character varying(100),
    specialite_bac character varying(100),
    annee_bac character(40),
    ine character(11) NOT NULL,
    nom character varying(50) NOT NULL,
    prenom character varying(50) NOT NULL,
    date_naissance date NOT NULL,
    code_postal character varying(10),
    ville character varying(50),
    sexe character varying(50) NOT NULL,
    nationalite character varying(50) NOT NULL  
);

WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_inscriptions.csv
         -type=text
         -table=_temp_etudiant
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=num_etudiant,cat_socio_etudiant,cat_socio_parent,bourse_superieur,mention,bac,annee_bac,ine,nom,prenom,code_postal,ville,sexe,nationalite,date_naissance
         ;

DROP TABLE IF EXISTS partie2._temp_resu_csv;
CREATE TABLE partie2._temp_resu_csv (
    groupe_tp_1a character(2),
    groupe_tp_2a character(2),
    amenagement_evaluation character varying(50),
    m1101 character(5),
    m1102 character(5),
    m1103 character(5),
    m1104 character(5),
    m1105 character(5),
    m1106 character(5),
    m1201 character(5),
    m1202 character(5),
    m1203 character(5),
    m1204 character(5),
    m1205 character(5),
    m1206 character(5),
    m1207 character(5),
    m2101 character(5),
    m2102 character(5),
    m2103 character(5),
    m2104 character(5),
    m2105 character(5),
    m2106 character(5),
    m2107 character(5),
    m2201 character(5),
    m2202 character(5),
    m2203 character(5),
    m2204 character(5),
    m2205 character(5),
    m2206 character(5),
    m2207 character(5),
    m3101 character(5),
    m3102 character(5),
    m3103 character(5),
    m3104 character(5),
    m3105 character(5),
    m3106c character(5),
    m3201 character(5),
    m3202c character(5),
    m3203 character(5),
    m3204 character(5),
    m3205 character(5),
    m3206 character(5),
    m3301 character(5),
    m3302 character(5),
    m3303 character(5),
    m4101c character(5),
    m4102c character(5),
    m4103c character(5),
    m4104c character(5),
    m4105c character(5),
    m41os1 character(5),
    m41os2 character(5),
    m41os3 character(5),
    m4106 character(5),
    m4201c character(5),
    m4202c character(5),
    m4203 character(5),
    m4204 character(5),
    m4301 character(5),
    code_nip character(11) NOT NULL,
    no_semestre character varying(5) NOT NULL,
    annee_univ character(9) NOT NULL
);

WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_resu_s1.csv
         -type=text
         -table=._temp_resu_csv
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=annee_univ,no_semestre,m1101,m1102,m1103,m1104,m1105,m1106,m1201,m1202,m1203,m1204,m1205,m1206,m1207,groupe_tp_1a,code_nip
         ;
         
WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_resu_s2.csv
         -type=text
         -table=._temp_resu_csv
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=annee_univ,no_semestre,m2101,m2102,m2103,m2104,m2105,m2106,m2107,m2201,m2202,m2203,m2204,m2205,m2206,m2207,groupe_tp_1a,code_nip
         ;
         
WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_resu_s3.csv
         -type=text
         -table=._temp_resu_csv
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=annee_univ,no_semestre,m3101,m3102,m3103,m3104,m3105,m3106c,m3201,m3202c,m3203,m3204,m3205,m3206,m3301,m3302,m3303,groupe_tp_2a,code_nip
         ;
         
WbImport -file=/media/mudinyver/PHILIPS UFD/IUT/psql2/s204/data/v_resu_s4.csv
         -type=text
         -table=._temp_resu_csv
         -schema=partie2
         -delimiter=';'
         -header=true
         -importColumns=annee_univ,no_semestre,m4101c,m4102c,m4103c,m4104c,m4105c,m41os1,m41os2,m41os3,m4106,m4201c,m4202c,m4203,m4204,m4301,groupe_tp_2a,code_nip
         ;
         
CREATE TABLE partie2._temp_resu_intermediaire (
    moyenne numeric(4,2) NOT NULL,
    code_nip character(11) NOT NULL,
    num_semestre character varying(5) NOT NULL,
    annee_univ character(9) NOT NULL,
    id_module character varying(6) NOT NULL
);

INSERT INTO partie2._semestre SELECT DISTINCT num_semestre,annee_univ FROM partie2._temp_programme;
INSERT INTO partie2._module SELECT * FROM partie2._temp_module;

INSERT INTO partie2._programme(coefficient,num_semestre,annee_univ,id_module) SELECT coefficient,num_semestre,annee_univ,id_module FROM partie2._temp_programme;




INSERT INTO partie2._individu(ine,nom,prenom,code_postal,ville,sexe,nationalite,date_naissance) SELECT numero_ine,nom,prenom,code_postal,ville,sexe,nationalite,date_naissance FROM partie2._temp_candidature;
INSERT INTO partie2._individu(ine,nom,prenom,code_postal,ville,sexe,nationalite,date_naissance) SELECT ine,nom,prenom,code_postal,ville,sexe,nationalite,date_naissance FROM partie2._temp_etudiant on conflict(ine) do nothing;

INSERT INTO partie2._candidat SELECT numero_candidat,classement,boursier,profil_candidat,libelle_etablissement,departement_etablissement,commune_etablissement,
niveau_etudes_actuel,type_formation,serie,dominante,diplome_specialite,lv1,lv2,numero_ine FROM partie2._temp_candidature;

UPDATE partie2._temp_etudiant SET dominante_bac=dominante FROM partie2._temp_candidature WHERE _temp_etudiant.ine=partie2._temp_candidature.numero_ine;
UPDATE partie2._temp_etudiant SET specialite_bac=diplome_specialite FROM partie2._temp_candidature WHERE _temp_etudiant.ine=partie2._temp_candidature.numero_ine;


INSERT INTO partie2._etudiant SELECT num_etudiant,cat_socio_etudiant,cat_socio_parent,bourse_superieur,mention,bac,dominante_bac,specialite_bac,annee_bac,ine FROM partie2._temp_etudiant on conflict(code_nip) do nothing;

INSERT INTO partie2._inscription SELECT groupe_tp_1a,amenagement_evaluation,code_nip,no_semestre,annee_univ FROM partie2._temp_resu_csv;
INSERT INTO partie2._inscription SELECT groupe_tp_2a,amenagement_evaluation,code_nip,no_semestre,annee_univ FROM partie2._temp_resu_csv on conflict(code_nip, num_semestre, annee_univ) do nothing;

INSERT INTO partie2._temp_resu_intermediaire SELECT -20.0,code_nip,no_semestre,annee_univ,'NA' FROM partie2._temp_resu_csv;



UPDATE partie2._temp_resu_csv SET m1101 = REPLACE(m1101, ',','.');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1101 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1101!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1101' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1101!='' AND id_module='NA';


UPDATE partie2._temp_resu_csv SET m1102 = REPLACE(m1102, ',','.');
UPDATE partie2._temp_resu_csv SET m1102 = REPLACE(m1102, '~','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1102 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1102!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1102' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1102!='' AND id_module='NA';


UPDATE partie2._temp_resu_csv SET m1103 = REPLACE(m1103, ',','.');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1103 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1103!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1103' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1103!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1104 = REPLACE(m1104, ',','.');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1104 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1104!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1104' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1104!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1105 = REPLACE(m1105, ',','.');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1105 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1105!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1105' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1105!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1106 = REPLACE(m1106, ',','.');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1106 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1106!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1106' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1106!='' AND id_module='NA';


UPDATE partie2._temp_resu_csv SET m1201 = REPLACE(m1201, ',','.');
UPDATE partie2._temp_resu_csv SET m1201 = REPLACE(m1201, '~','');
UPDATE partie2._temp_resu_csv SET m1201 = REPLACE(m1201, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1201 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1201!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1201' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1201!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1202 = REPLACE(m1202, ',','.');
UPDATE partie2._temp_resu_csv SET m1202 = REPLACE(m1202, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1202 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1202!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1202' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1202!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1203 = REPLACE(m1203, ',','.');
UPDATE partie2._temp_resu_csv SET m1203 = REPLACE(m1203, '~','');
UPDATE partie2._temp_resu_csv SET m1203 = REPLACE(m1203, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1203 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1203!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1203' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1203!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1204 = REPLACE(m1204, ',','.');
UPDATE partie2._temp_resu_csv SET m1204 = REPLACE(m1204, '~','');
UPDATE partie2._temp_resu_csv SET m1204 = REPLACE(m1204, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1204 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1204!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1204' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1204!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1205 = REPLACE(m1205, ',','.');
UPDATE partie2._temp_resu_csv SET m1205 = REPLACE(m1205, '~','');
UPDATE partie2._temp_resu_csv SET m1205 = REPLACE(m1205, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1205 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1205!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1205' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1205!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1206 = REPLACE(m1206, ',','.');
UPDATE partie2._temp_resu_csv SET m1206 = REPLACE(m1206, '~','');
UPDATE partie2._temp_resu_csv SET m1206 = REPLACE(m1206, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1206 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1206!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1206' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1206!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m1207 = REPLACE(m1207, ',','.');
UPDATE partie2._temp_resu_csv SET m1207 = REPLACE(m1207, '~','');
UPDATE partie2._temp_resu_csv SET m1207 = REPLACE(m1207, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m1207 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m1207!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M1207' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m1207!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2101 = REPLACE(m2101, ',','.');
UPDATE partie2._temp_resu_csv SET m2101 = REPLACE(m2101, '~','');
UPDATE partie2._temp_resu_csv SET m2101 = REPLACE(m2101, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2101 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2101!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2101' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2101!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2102 = REPLACE(m2102, ',','.');
UPDATE partie2._temp_resu_csv SET m2102 = REPLACE(m2102, '~','');
UPDATE partie2._temp_resu_csv SET m2102 = REPLACE(m2102, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2102 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2102!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2102' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2102!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2103 = REPLACE(m2103, ',','.');
UPDATE partie2._temp_resu_csv SET m2103 = REPLACE(m2103, '~','');
UPDATE partie2._temp_resu_csv SET m2103 = REPLACE(m2103, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2103 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2103!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2103' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2103!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2104 = REPLACE(m2104, ',','.');
UPDATE partie2._temp_resu_csv SET m2104 = REPLACE(m2104, '~','');
UPDATE partie2._temp_resu_csv SET m2104 = REPLACE(m2104, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2104 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2104!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2104' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2104!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2105 = REPLACE(m2105, ',','.');
UPDATE partie2._temp_resu_csv SET m2105 = REPLACE(m2105, '~','');
UPDATE partie2._temp_resu_csv SET m2105 = REPLACE(m2105, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2105 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2105!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2105' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2105!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2106 = REPLACE(m2106, ',','.');
UPDATE partie2._temp_resu_csv SET m2106 = REPLACE(m2106, '~','');
UPDATE partie2._temp_resu_csv SET m2106 = REPLACE(m2106, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2106 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2106!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2106' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2106!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2107 = REPLACE(m2107, ',','.');
UPDATE partie2._temp_resu_csv SET m2107 = REPLACE(m2107, '~','');
UPDATE partie2._temp_resu_csv SET m2107 = REPLACE(m2107, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2107 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2107!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2107' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2107!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2201 = REPLACE(m2201, ',','.');
UPDATE partie2._temp_resu_csv SET m2201 = REPLACE(m2201, '~','');
UPDATE partie2._temp_resu_csv SET m2201 = REPLACE(m2201, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2201 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2201!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2201' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2201!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2202 = REPLACE(m2202, ',','.');
UPDATE partie2._temp_resu_csv SET m2202 = REPLACE(m2202, '~','');
UPDATE partie2._temp_resu_csv SET m2202 = REPLACE(m2202, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2202 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2202!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2202' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2202!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2203 = REPLACE(m2203, ',','.');
UPDATE partie2._temp_resu_csv SET m2203 = REPLACE(m2203, '~','');
UPDATE partie2._temp_resu_csv SET m2203 = REPLACE(m2203, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2203 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2203!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2203' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2203!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2204 = REPLACE(m2204, ',','.');
UPDATE partie2._temp_resu_csv SET m2204 = REPLACE(m2204, '~','');
UPDATE partie2._temp_resu_csv SET m2204 = REPLACE(m2204, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2204 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2204!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2204' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2204!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2205 = REPLACE(m2205, ',','.');
UPDATE partie2._temp_resu_csv SET m2205 = REPLACE(m2205, '~','');
UPDATE partie2._temp_resu_csv SET m2205 = REPLACE(m2205, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2205 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2205!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2205' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2205!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2206 = REPLACE(m2206, ',','.');
UPDATE partie2._temp_resu_csv SET m2206 = REPLACE(m2206, '~','');
UPDATE partie2._temp_resu_csv SET m2206 = REPLACE(m2206, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2206 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2206!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2206' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2206!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m2207 = REPLACE(m2207, ',','.');
UPDATE partie2._temp_resu_csv SET m2207 = REPLACE(m2207, '~','');
UPDATE partie2._temp_resu_csv SET m2207 = REPLACE(m2207, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m2207 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m2207!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M2207' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m2207!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3101 = REPLACE(m3101, ',','.');
UPDATE partie2._temp_resu_csv SET m3101 = REPLACE(m3101, '~','');
UPDATE partie2._temp_resu_csv SET m3101 = REPLACE(m3101, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3101 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3101!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3101' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3101!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3102 = REPLACE(m3102, ',','.');
UPDATE partie2._temp_resu_csv SET m3102 = REPLACE(m3102, '~','');
UPDATE partie2._temp_resu_csv SET m3102 = REPLACE(m3102, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3102 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3102!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3102' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3102!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3103 = REPLACE(m3103, ',','.');
UPDATE partie2._temp_resu_csv SET m3103 = REPLACE(m3103, '~','');
UPDATE partie2._temp_resu_csv SET m3103 = REPLACE(m3103, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3103 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3103!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3103' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3103!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3104 = REPLACE(m3104, ',','.');
UPDATE partie2._temp_resu_csv SET m3104 = REPLACE(m3104, '~','');
UPDATE partie2._temp_resu_csv SET m3104 = REPLACE(m3104, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3104 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3104!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3104' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3104!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3105 = REPLACE(m3105, ',','.');
UPDATE partie2._temp_resu_csv SET m3105 = REPLACE(m3105, '~','');
UPDATE partie2._temp_resu_csv SET m3105 = REPLACE(m3105, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3105 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3105!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3105' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3105!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3106c = REPLACE(m3106c, ',','.');
UPDATE partie2._temp_resu_csv SET m3106c = REPLACE(m3106c, '~','');
UPDATE partie2._temp_resu_csv SET m3106c = REPLACE(m3106c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3106c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3106c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3106c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3106c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3201 = REPLACE(m3201, ',','.');
UPDATE partie2._temp_resu_csv SET m3201 = REPLACE(m3201, '~','');
UPDATE partie2._temp_resu_csv SET m3201 = REPLACE(m3201, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3201 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3201!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3201' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3201!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3202c = REPLACE(m3202c, ',','.');
UPDATE partie2._temp_resu_csv SET m3202c = REPLACE(m3202c, '~','');
UPDATE partie2._temp_resu_csv SET m3202c = REPLACE(m3202c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3202c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3202c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3202c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3202c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3203 = REPLACE(m3203, ',','.');
UPDATE partie2._temp_resu_csv SET m3203 = REPLACE(m3203, '~','');
UPDATE partie2._temp_resu_csv SET m3203 = REPLACE(m3203, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3203 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3203!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3203' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3203!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3204 = REPLACE(m3204, ',','.');
UPDATE partie2._temp_resu_csv SET m3204 = REPLACE(m3204, '~','');
UPDATE partie2._temp_resu_csv SET m3204 = REPLACE(m3204, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3204 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3204!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3204' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3204!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3205 = REPLACE(m3205, ',','.');
UPDATE partie2._temp_resu_csv SET m3205 = REPLACE(m3205, '~','');
UPDATE partie2._temp_resu_csv SET m3205 = REPLACE(m3205, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3205 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3205!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3205' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3205!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3206 = REPLACE(m3206, ',','.');
UPDATE partie2._temp_resu_csv SET m3206 = REPLACE(m3206, '~','');
UPDATE partie2._temp_resu_csv SET m3206 = REPLACE(m3206, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3206 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3206!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3206' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3206!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3301 = REPLACE(m3301, ',','.');
UPDATE partie2._temp_resu_csv SET m3301 = REPLACE(m3301, '~','');
UPDATE partie2._temp_resu_csv SET m3301 = REPLACE(m3301, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3301 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3301!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3301' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3301!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3302 = REPLACE(m3302, ',','.');
UPDATE partie2._temp_resu_csv SET m3302 = REPLACE(m3302, '~','');
UPDATE partie2._temp_resu_csv SET m3302 = REPLACE(m3302, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3302 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3302!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3302' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3302!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m3303 = REPLACE(m3303, ',','.');
UPDATE partie2._temp_resu_csv SET m3303 = REPLACE(m3303, '~','');
UPDATE partie2._temp_resu_csv SET m3303 = REPLACE(m3303, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m3303 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m3303!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M3303' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m3303!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4101c = REPLACE(m4101c, ',','.');
UPDATE partie2._temp_resu_csv SET m4101c = REPLACE(m4101c, '~','');
UPDATE partie2._temp_resu_csv SET m4101c = REPLACE(m4101c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4101c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4101c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4101c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4101c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4102c = REPLACE(m4102c, ',','.');
UPDATE partie2._temp_resu_csv SET m4102c = REPLACE(m4102c, '~','');
UPDATE partie2._temp_resu_csv SET m4102c = REPLACE(m4102c, 'NI','');
UPDATE partie2._temp_resu_csv SET m4102c = REPLACE(m4102c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4102c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4102c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4102c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4102c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4103c = REPLACE(m4103c, ',','.');
UPDATE partie2._temp_resu_csv SET m4103c = REPLACE(m4103c, '~','');
UPDATE partie2._temp_resu_csv SET m4103c = REPLACE(m4103c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4103c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4103c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4103c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4103c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4104c = REPLACE(m4104c, ',','.');
UPDATE partie2._temp_resu_csv SET m4104c = REPLACE(m4104c, '~','');
UPDATE partie2._temp_resu_csv SET m4104c = REPLACE(m4104c, 'NI','');
UPDATE partie2._temp_resu_csv SET m4104c = REPLACE(m4104c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4104c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4104c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4104c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4104c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4105c = REPLACE(m4105c, ',','.');
UPDATE partie2._temp_resu_csv SET m4105c = REPLACE(m4105c, '~','');
UPDATE partie2._temp_resu_csv SET m4105c = REPLACE(m4105c, 'NI','');
UPDATE partie2._temp_resu_csv SET m4105c = REPLACE(m4105c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4105c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4105c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4105c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4105c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m41os1 = REPLACE(m41os1, ',','.');
UPDATE partie2._temp_resu_csv SET m41os1 = REPLACE(m41os1, '~','');
UPDATE partie2._temp_resu_csv SET m41os1 = REPLACE(m41os1, 'NI','');
UPDATE partie2._temp_resu_csv SET m41os1 = REPLACE(m41os1, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m41os1 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m41os1!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M41os1' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m41os1!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m41os2 = REPLACE(m41os2, ',','.');
UPDATE partie2._temp_resu_csv SET m41os2 = REPLACE(m41os2, '~','');
UPDATE partie2._temp_resu_csv SET m41os2 = REPLACE(m41os2, 'NI','');
UPDATE partie2._temp_resu_csv SET m41os2 = REPLACE(m41os2, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m41os2 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m41os2!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M41os2' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m41os2!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m41os3 = REPLACE(m41os3, ',','.');
UPDATE partie2._temp_resu_csv SET m41os3 = REPLACE(m41os3, '~','');
UPDATE partie2._temp_resu_csv SET m41os3 = REPLACE(m41os3, 'NI','');
UPDATE partie2._temp_resu_csv SET m41os3 = REPLACE(m41os3, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m41os3 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m41os3!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M41os3' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m41os3!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4106 = REPLACE(m4106, ',','.');
UPDATE partie2._temp_resu_csv SET m4106 = REPLACE(m4106, '~','');
UPDATE partie2._temp_resu_csv SET m4106 = REPLACE(m4106, 'NI','');
UPDATE partie2._temp_resu_csv SET m4106 = REPLACE(m4106, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4106 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4106!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4106' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4106!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4201c = REPLACE(m4201c, ',','.');
UPDATE partie2._temp_resu_csv SET m4201c = REPLACE(m4201c, '~','');
UPDATE partie2._temp_resu_csv SET m4201c = REPLACE(m4201c, 'NI','');
UPDATE partie2._temp_resu_csv SET m4201c = REPLACE(m4201c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4201c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4201c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4201c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4201c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4202c = REPLACE(m4202c, ',','.');
UPDATE partie2._temp_resu_csv SET m4202c = REPLACE(m4202c, '~','');
UPDATE partie2._temp_resu_csv SET m4202c = REPLACE(m4202c, 'NI','');
UPDATE partie2._temp_resu_csv SET m4202c = REPLACE(m4202c, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4202c AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4202c!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4202c' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4202c!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4203 = REPLACE(m4203, ',','.');
UPDATE partie2._temp_resu_csv SET m4203 = REPLACE(m4203, '~','');
UPDATE partie2._temp_resu_csv SET m4203 = REPLACE(m4203, 'NI','');
UPDATE partie2._temp_resu_csv SET m4203 = REPLACE(m4203, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4203 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4203!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4203' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4203!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4204 = REPLACE(m4204, ',','.');
UPDATE partie2._temp_resu_csv SET m4204 = REPLACE(m4204, '~','');
UPDATE partie2._temp_resu_csv SET m4204 = REPLACE(m4204, 'NI','');
UPDATE partie2._temp_resu_csv SET m4204 = REPLACE(m4204, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4204 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4204!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4204' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4204!='' AND id_module='NA';

UPDATE partie2._temp_resu_csv SET m4301 = REPLACE(m4301, ',','.');
UPDATE partie2._temp_resu_csv SET m4301 = REPLACE(m4301, '~','');
UPDATE partie2._temp_resu_csv SET m4301 = REPLACE(m4301, 'NI','');
UPDATE partie2._temp_resu_csv SET m4301 = REPLACE(m4301, '-c-','');
UPDATE partie2._temp_resu_intermediaire SET moyenne=CAST(m4301 AS NUMERIC(4,2)) FROM partie2._temp_resu_csv WHERE _temp_resu_csv.code_nip=_temp_resu_intermediaire.code_nip AND m4301!='' AND id_module='NA';
UPDATE partie2._temp_resu_intermediaire SET id_module='M4301' FROM partie2._temp_resu_csv WHERE _temp_resu_csv.
code_nip=_temp_resu_intermediaire.code_nip AND m4301!='' AND id_module='NA';

INSERT INTO partie2._programme(num_semestre, annee_univ, id_module) SELECT num_semestre, annee_univ, id_module FROM partie2._temp_resu_intermediaire on conflict(num_semestre, annee_univ, id_module) do nothing;

INSERT INTO partie2._resultat SELECT * FROM partie2._temp_resu_intermediaire;

DROP TABLE IF EXISTS partie2._temp_etudiant;
DROP TABLE IF EXISTS partie2._temp_candidature;
DROP TABLE IF EXISTS partie2._temp_module;
DROP TABLE IF EXISTS partie2._temp_programme;
DROP TABLE IF EXISTS partie2._temp_resu_csv;
DROP TABLE IF EXISTS partie2._temp_resu_intermediaire;


