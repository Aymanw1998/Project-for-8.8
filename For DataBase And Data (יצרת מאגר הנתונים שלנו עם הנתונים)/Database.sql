DROP DATABASE recording_studio;
CREATE DATABASE IF NOT EXISTS recording_studio;
USE recording_studio;

-- Musician (מוסיקאי)
CREATE TABLE IF NOT EXISTS Musician (
	musician_ID INT(9) PRIMARY KEY,  
    musician_Name VARCHAR(50) NOT NULL,
    musician_Email VARCHAR(255) NOT NULL,
    musician_Number_Phone INT(10) NOT NULL,
    musician_Type VARCHAR(50) NOT NULL -- Singer(זמר) OR Player(נגן) OR Both(זמר ונגן)
);

-- Album (אלבום)
CREATE TABLE IF NOT EXISTS Album (
	album_ID INT UNSIGNED PRIMARY KEY,
    album_Name VARCHAR(50) NOT NULL,
    album_Date_Start date NOT NULL,
    album_Date_End date NOT NULL,
    album_Count_a_Musical_Scene INT UNSIGNED -- מספר שירים הכללולים בו
);

-- Producer (מפיק)
CREATE TABLE IF NOT EXISTS Producer (
	producer_ID INT(9) PRIMARY KEY,
    producer_Name VARCHAR(50) NOT NULL
); 


-- Author of words for a musical scene (הפרטים על מחבר המילים)
CREATE TABLE IF NOT EXISTS Author_Of_Words (
	author_Of_Words_ID INT(9) PRIMARY KEY,
    author_Of_Words_Name VARCHAR(50) NOT NULL
);

-- Author of Melody for a musical scene (הפרטים על מחבר הלחן)
CREATE TABLE IF NOT EXISTS Author_Of_Melody (
	author_Of_Melody_ID INT(9) PRIMARY KEY,
    author_Of_Melody_Name VARCHAR(50) NOT NULL
);

-- Recording Technician (טכנאי הקלטה)
CREATE TABLE IF NOT EXISTS Recording_Technician (
    recording_Technician_ID INT(9) PRIMARY KEY,
    recording_Technician_Name VARCHAR(100)
);

-- A musical scene (קטע מוסיקלי)
CREATE TABLE IF NOT EXISTS A_Musical_Scene (
    a_Musical_Scene_Name VARCHAR(50) PRIMARY KEY,
    author_Of_Words_ID INT(9) , -- (ת.ז. של מחבר המילים ממנו יודעים פרטים)
		FOREIGN KEY (author_Of_Words_ID) REFERENCES Author_Of_Words(author_Of_Words_ID) ON DELETE RESTRICT ON UPDATE RESTRICT,
    author_Of_Melody_ID INT(9), -- (ת.ז. של מחבר הלחן ממנו יודעים פרטים)
        FOREIGN KEY (author_Of_Melody_ID) REFERENCES Author_Of_Melody(author_Of_Melody_ID) ON DELETE RESTRICT ON UPDATE RESTRICT,
    a_Musical_Scene_Length_sec INT(10),
    a_Musical_Scene_Type VARCHAR(50),
    a_Musical_Scene_Date date NOT NULL,
    recording_Technician_ID INT(9),
		FOREIGN KEY (recording_Technician_ID) REFERENCES Recording_Technician(recording_Technician_ID) ON DELETE RESTRICT ON UPDATE RESTRICT

);


-- A musical instruments (כלי נגינה)
CREATE TABLE IF NOT EXISTS A_Musical_Instruments (
    a_Musical_Instrument_Type VARCHAR(50) PRIMARY KEY,
    a_Musical_Instrument_Maker VARCHAR(50)
);

-- Tיhe relationship between an album and a musician
-- כל מוסיקאי או יותר מקליט\ים אלבום אחד או יותר
CREATE TABLE IF NOT EXISTS Musician_And_Album (
	musician_ID INT(9),
		FOREIGN KEY (musician_ID) REFERENCES Musician(musician_ID) ON DELETE RESTRICT ON UPDATE RESTRICT,
	album_ID INT UNSIGNED,
		FOREIGN KEY (album_ID) REFERENCES Album(album_ID) ON DELETE RESTRICT ON UPDATE RESTRICT
);

-- Tיhe relationship between an album and a producer
-- כל אלבום מופק על ידי מפקיד אחד או יותר
CREATE TABLE IF NOT EXISTS Producer_And_Album (
	album_ID INT UNSIGNED,
		FOREIGN KEY (album_ID) REFERENCES Album(album_ID) ON DELETE RESTRICT ON UPDATE RESTRICT,
    producer_ID INT(9),
		FOREIGN KEY (producer_ID) REFERENCES Producer(producer_ID) ON DELETE RESTRICT ON UPDATE RESTRICT
);

-- Tיhe relationship between an album and a musical scene
-- כל אלבום כולל קטע מוסיקלי אחד או יותר
CREATE TABLE IF NOT EXISTS A_Musical_Scene_And_Album (
	album_ID INT UNSIGNED,
		FOREIGN KEY (album_ID) REFERENCES Album(album_ID) ON DELETE RESTRICT ON UPDATE RESTRICT,
    a_Musical_Scene_Name VARCHAR(50),
		FOREIGN KEY (a_Musical_Scene_Name) REFERENCES A_Musical_Scene(a_Musical_Scene_Name) ON DELETE RESTRICT ON UPDATE RESTRICT
);

-- Tיhe relationship between a musician and a musical instruments
-- למוסיקאי יתכנו מספר כלי נגינה בהם הוא יודע לנגן
CREATE TABLE IF NOT EXISTS A_Musical_Intruments_And_Musician (
	musician_ID INT(9),
		FOREIGN KEY (musician_ID) REFERENCES Musician(musician_ID) ON DELETE RESTRICT ON UPDATE RESTRICT,
    a_Musical_Instrument_Type VARCHAR(50),
		FOREIGN KEY (a_Musical_Instrument_Type) REFERENCES A_Musical_Instruments(a_Musical_Instrument_Type) ON DELETE RESTRICT ON UPDATE RESTRICT
);


-- Tיhe relationship between an a musical scene and a musical instruments
-- כל כלי נגינה שהשתתף בקטעי נגינה
CREATE TABLE IF NOT EXISTS A_Musical_Scene_And_A_Musical_Instruments (
	a_Musical_Scene_Name VARCHAR(50),
		FOREIGN KEY (a_Musical_Scene_Name) REFERENCES A_Musical_Scene(a_Musical_Scene_Name) ON DELETE RESTRICT ON UPDATE RESTRICT,
	a_Musical_Instrument_Type VARCHAR(50),
		FOREIGN KEY (a_Musical_Instrument_Type) REFERENCES A_Musical_Instruments(a_Musical_Instrument_Type) ON DELETE RESTRICT ON UPDATE RESTRICT
);
