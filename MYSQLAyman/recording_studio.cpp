#include <mysql.h>
#include <iostream>
#include "recording_studio.h"
using namespace std;
int qstate,boolN = 1;
string query, dateStart, dateEnd,fullName,albumFullName;
MYSQL* conn;MYSQL_ROW row;MYSQL_RES* res;
const char* q;
void commandList()
{
	std::cout << "List of commands:" << endl
		<< "0. Command manual" << endl
		<< "1. How many albums were recorded between Y1 date and Y2 date" << endl
		<< "2. How many  different songs recorded X  musician between Y1 date and Y2 date" << endl
		<< "3. In how many different albums did X muscian participate between Y1 date and Y2 date" << endl
		<< "4. The instrument that participated in the recording of the greatest number of the greatest number of musical passages" << endl
		<< "5. List of instruments in album A" << endl
		<< "6. Producer who became the largest number of albums on Y1 date and Y2 date" << endl
		<< "7. The manufacturer whose musical instruments participated in the recording of the narratore greatest of musical passages" << endl
		<< "8. How many musicians have recorded over the years" << endl
		<< "9. The musician who cooperated with the greatest number (= most) Other musicians" << endl
		<< "10. The most popular song genre (throughout the years)" << endl
		<< "11. The recording technician recorded the largest number of songs between Y1 and Y" << endl
		<< "12. The first album recorded in the studio" << endl
		<< "13. List all songs in 2 or more albums" << endl
		<< "14. List of technicians who have shared the recording of an entire album" << endl
		<< "15. The musician who recorded songs in the widest range of genres" << endl
		<< "16.Exit the project" << endl;
}

void command1()    /* 1 */
{
	boolN = 1;
	std::cout << "Date Start (yyyy-MM-DD): ";std::cin >> dateStart;
	std::cout << "Date End (yyyy-MM-DD): ";std::cin >> dateEnd;
	
	if (dateStart > dateEnd) { cout << "ERROR in Syntax (DateStart not greater than the dateEnd)" << endl;goto NOFund; }

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		query = "SELECT count(*) FROM Album WHERE album_Date_Start >= '" + dateStart + "' AND album_Date_End <= '" + dateEnd + "'";
		q = query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				boolN = 0;
				if (row[0]){
					std::cout << endl << endl << "Count albums were recorded (" << row[0] << ") between: [" << dateStart << "] and [" << dateEnd << "]" << endl;
				}
				else {
					std::cout << endl << endl << "Can't have Album between: [" << dateStart << "] and [" << dateEnd << "]" << endl;
				}
			}
			if(boolN){ std::cout << endl << endl << "Can't have Album between: [" << dateStart << "] and [" << dateEnd << "]" << endl; }

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	NOFund:return;
}

void command2()    /* 2 */
{
	boolN = 1;
	std::cout << "Full name of musician: ";std::cin >> fullName;
	std::cout << "Date Start (yyyy-MM-DD): ";std::cin >> dateStart;
	std::cout << "Date End (yyyy-MM-DD): ";std::cin >> dateEnd;
	if (dateStart > dateEnd) { cout << "ERROR in Syntax (DateStart not greater than the dateEnd)"<<endl;goto NOFund; }
	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {

	query = "SELECT musician_Name FROM Musician WHERE musician_Name='" + fullName + "'";
	q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);row = mysql_fetch_row(res);
			//cout << row << endl;
			if (row== 0000000000000000) {
				cout<<fullName+" does't exist in the Database"<<endl;goto NOFund;
			}
		}

	query = "SELECT count(*) FROM A_Musical_Scene_And_Album WHERE album_ID in (SELECT album_ID FROM Musician_And_Album WHERE album_ID in (SELECT album_ID FROM Album WHERE album_Date_Start >= '" + dateStart + "' AND album_Date_End <= '" + dateEnd + "')AND musician_ID in(SELECT musician_ID FROM Musician WHERE musician_Name='" + fullName + "'))";
	 q = query.c_str();
	qstate = mysql_query(conn, q);
	//cout << query << endl;
	if (!qstate) {
	res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				boolN = 0;
				if (row[0]) {
					std::cout << endl << endl << fullName << " has (" << row[0] << ") Songs between: [" << dateStart << "] and [" << dateEnd << "]" << endl;
				}
				else {
					std::cout << endl << endl << "Can't have Song between: [" << dateStart << "] and [" << dateEnd << "]" << endl;

				}
			}
			if(boolN){
				std::cout << endl << endl << "Can't have Song between: [" << dateStart << "] and [" << dateEnd << "]" << endl;
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}
	NOFund: return;
}

void command3()    /* 3 */
{
	boolN = 1;
	std::cout << "Full name of musician: ";std::cin >> fullName;
	std::cout << "Date Start (yyyy-MM-DD): ";std::cin >> dateStart;
	std::cout << "Date End (yyyy-MM-DD): ";std::cin >> dateEnd;
	
	if (dateStart > dateEnd) { cout << "ERROR in Syntax (DateStart not greater than the dateEnd)" << endl;goto NOFund; }
	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {

		query = "SELECT musician_Name FROM Musician WHERE musician_Name='" + fullName + "'";
	q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);row = mysql_fetch_row(res);
			//cout << row << endl;
			if (row == 0000000000000000) {
				cout << fullName + " does't exist in the Database" << endl;goto NOFund;
			}
		}

		query = "SELECT count(*) FROM Musician_And_Album WHERE album_ID in (SELECT album_ID FROM Album WHERE album_Date_Start >= '" + dateStart + "' AND album_Date_End <= '" + dateEnd + "')AND musician_ID in(SELECT musician_ID FROM Musician WHERE musician_Name='" + fullName + "')";
		q = query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				boolN = 0;
				if (row[0] != 0) {
					std::cout << endl << endl << fullName << " has (" << row[0] << ") Albums between: [" << dateStart << "] and [" << dateEnd << "]" << endl;
				}
				else {
					std::cout << endl << endl << "Can't have Album between: [" << dateStart << "] and [" << dateEnd << "]" << endl;

				}
			}
			if(!boolN){}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	NOFund:return;
}

void command4()    /* 4 */
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		 query = "SELECT a_Musical_Instrument_Type FROM a_musical_scene_and_a_musical_instruments GROUP by a_Musical_Instrument_Type order by count(a_Musical_Instrument_Type) desc limit 1";
		 q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] != 0) {
					std::cout << endl << endl << row[0] << endl;
				}
				else {
					std::cout << endl << endl << "Not Have A Musical Intrument Type  " << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}
	return;
}

void command5()    /* 5 */
{

	std::cout << "Album: ";std::cin >> albumFullName;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {

		query = "SELECT album_Name FROM Album WHERE album_Name='" + albumFullName + "'";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);row = mysql_fetch_row(res);
			//cout << row << endl;
			if (row == 0000000000000000) {
				cout <<albumFullName + " does't exist in the Database" << endl;goto NOFund;
			}
		}

		query = "SELECT a_Musical_Instrument_Type FROM a_musical_scene_and_a_musical_instruments WHERE a_Musical_Scene_Name in(SELECT a_Musical_Scene_Name FROM A_Musical_Scene_And_Album WHERE album_ID in (SELECT album_ID FROM Album WHERE album_Name='" + albumFullName +"'))";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0]) {
					std::cout << endl << row[0];
				}
				else {
					std::cout << endl << albumFullName << ", this Album doesn't have Musical Instrument Types" << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	NOFund:return;
}

void command6()    /* 6 */
{
	boolN = 1;
	std::cout << "Date Start (yyyy-MM-DD): ";std::cin >> dateStart;
	std::cout << "Date End (yyyy-MM-DD): ";std::cin >> dateEnd;
	if (dateStart > dateEnd) { cout << "ERROR in Syntax (DateStart not greater than the dateEnd)" << endl;goto NOFund; }

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		query = "SELECT producer_Name FROM producer,(SELECT *  FROM(SELECT  count(producer_ID) AS A,producer_ID FROM producer_and_album AS B,album WHERE B.album_ID=album.album_ID AND album.album_Date_Start>='"+dateStart+"' AND album.album_Date_End<='"+dateEnd+"' group by producer_ID )AS B  ORDER BY B.A desc limit 1)AS W Where producer.producer_ID = W.producer_ID";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		// cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				boolN = 0;
				if (row[0]) {
					std::cout << endl << endl << row[0]<<" is the pupolar producer" << endl;
				}
				else {
					std::cout << endl << endl <<  "don't have pupolar producer " << endl;

				}
			}
			if(boolN){ std::cout << endl << endl << "don't have pupolar producer " << endl; }

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

NOFund: return ;
}

void command7()    /* 7 */
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		 query = " SELECT a_Musical_Instrument_Maker FROM a_musical_instruments,(SELECT *  FROM( SELECT  count(a_Musical_Instrument_Type) AS A,a_Musical_Instrument_Type FROM a_musical_scene_and_a_musical_instruments AS B group by a_Musical_Instrument_Type)AS B  ORDER BY B.A desc limit 1)AS W WHERE W.a_Musical_Instrument_Type=a_musical_instruments.a_Musical_Instrument_Type";
		 q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] != 0) {
					std::cout << endl << endl << row[0]<<" is the pupolar musical instrument maker" << endl;
				}
				else {
					std::cout << endl << endl << "don't have the pupolar musical instrument maker " << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	return ;
}

void command8()    /* 8 */
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		 query = "SELECT musician_Name FROM musician WHERE musician_ID in(SELECT distinct musician_ID FROM musician_and_album)";
		 q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] != 0) {
					std::cout << endl << row[0];
				}
				else {
					std::cout << endl << endl << "Don't have musican " << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	return;
}

void command9()    /* 9 */
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		query = "SELECT musician_Name FROM Musician WHERE  musician_ID =(SELECT musician_ID FROM(SELECT musician_ID FROM musician_and_album WHERE album_ID in (SELECT album_ID FROM musician_and_album GROUP BY album_ID Having COUNT(*)>1 ORDER BY Count(*) DESC)) AS A  GROUP BY A.musician_ID ORDER BY count(*) DESC LIMIT 1)";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] != 0) {
					std::cout << endl << endl << row[0]<< "is the musician included another musician" << endl;
				}
				else {
					std::cout << endl << endl << "Don't have musician included anther musician" << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	return;
}

void command10()    /* 10 */
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		query = "SELECT a_Musical_Scene_Type FROM a_musical_scene GROUP BY a_Musical_Scene_Type ORDER BY count(a_Musical_Scene_Type) DESC LIMIT 1";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] != 0) {
					std::cout << endl << endl << row[0] <<" is the pupolar musical scene type"<< endl;
				}
				else {
					std::cout << endl << endl << "don't have pupolar musical scene type" << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	return;
}

void command11()    /* 11 */
{
	boolN = 1;
	std::cout << "Date Start (yyyy-MM-DD): ";std::cin >> dateStart;
	std::cout << "Date End (yyyy-MM-DD): ";std::cin >> dateEnd;
	if (dateStart > dateEnd) { cout << "ERROR in Syntax (DateStart not greater than the dateEnd)" << endl;goto NOFund; }

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		query = " SELECT recording_Technician_Name FROM Recording_Technician,(SELECT *  FROM(SELECT  count(recording_Technician_ID) AS A,recording_Technician_ID FROM a_musical_scene  WHERE a_Musical_Scene_Date>='" + dateStart + "' AND a_Musical_Scene_Date<='" + dateEnd + "' group by recording_Technician_ID )AS B  ORDER BY B.A desc limit 1)AS W Where Recording_Technician.recording_Technician_ID = W.recording_Technician_ID";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				boolN = 0;
				if (row[0] != 0) {
					std::cout << endl << endl << row[0]<<" is the pupolar technician between ["+dateStart+"] to ["+dateEnd+"] " << endl;
				}
				else {
					std::cout << endl << endl << "Can't" << endl;

				}
			}
			if(boolN){
				std::cout << endl << " don't have the pupolar technician between [" + dateStart + "] to [" + dateEnd + "] " << endl;
			}
		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	NOFund:return;
}

void command12()    /* 12 */
{
conn = mysql_init(0);
conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
if (conn) {
	query = "SELECT album_Name FROM Album WHERE album_Date_Start in (SELECT MIN(album_Date_Start) FROM Album )";
    q = query.c_str();
	qstate = mysql_query(conn, q);
	//cout<< query << endl;
	if (!qstate) {
		res = mysql_store_result(conn);

		while (row = mysql_fetch_row(res)) {
				std::cout << endl << endl <<row[0] << " is first album" << endl;
		}

	}
	else {
		std::cout << "Query Failed: " << mysql_error(conn) << endl;
	}
}
else {
	puts("ERROR");
}

return;
}

void command13()    /* 13 */
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	if (conn) {
		query = "SELECT a_Musical_Scene_Name FROM (SELECT a_Musical_Scene_Name,Count(a_Musical_Scene_Name) AS countSong FROM a_musical_scene_and_album group by a_Musical_Scene_Name ORDER BY a_Musical_Scene_Name DESC) AS S WHERE countSong>1";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		//cout << endl << query << endl;
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] != 0) {
					std::cout << endl << row[0];
				}
				else {
					std::cout << endl << endl << "don't have Songs included between Two albums or More" << endl;

				}
			}

		}
		else {
			std::cout << "Query Failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("ERROR");
	}

	return;
}

void command14() /* 14 */
{
conn = mysql_init(0);
conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
if (conn) {
	 query = " SELECT distinct recording_Technician_Name FROM album, recording_technician, a_musical_scene, a_musical_scene_and_album WHERE recording_technician.recording_Technician_ID = a_musical_scene.recording_Technician_ID AND a_musical_scene_and_album.album_ID = album.album_ID GROUP BY recording_technician.recording_Technician_Name,album.album_Name, album.album_Count_a_Musical_Scene  HAVING count(a_musical_scene.a_Musical_Scene_Name) = album_Count_a_Musical_Scene";
	 q = query.c_str();
	qstate = mysql_query(conn, q);
	//cout << endl << query << endl;
	if (!qstate) {
		res = mysql_store_result(conn);

		while (row = mysql_fetch_row(res)) {
			if (row[0] != 0) {
				std::cout << endl <<row[0];
			}
			else {
				std::cout << endl << endl << "Can't" << endl;

			}
		}

	}
	else {
		std::cout << "Query Failed: " << mysql_error(conn) << endl;
	}
}
else {
	puts("ERROR");
}

return;
}

void command15() /* 15 */
{

}