/*#include <mysql.h>
#include <iostream>


using namespace std;
int qstate;
int main() {
	string dateStart, dateEnd,fullName;
	
	MYSQL* conn;MYSQL_ROW row;MYSQL_RES* res;
	///*conn = mysql_init(0);
	//conn = mysql_real_connect(conn, "localhost", "root", "23061998", "recording_studio", 3306, NULL, 0);
	//if (conn) {
	//	string query = " SELECT distinct recording_Technician_Name FROM album, recording_technician, a_musical_scene, a_musical_scene_and_album WHERE recording_technician.recording_Technician_ID = a_musical_scene.recording_Technician_ID AND a_musical_scene_and_album.album_ID = album.album_ID GROUP BY recording_technician.recording_Technician_Name,album.album_Name, album.album_Count_a_Musical_Scene  HAVING count(a_musical_scene.a_Musical_Scene_Name) = album_Count_a_Musical_Scene";
	//	const char* q = query.c_str();
	//	qstate = mysql_query(conn, q);
	//	cout << endl << query << endl;
	//	if (!qstate) {
	//		res = mysql_store_result(conn);
	//	
	//		while (row = mysql_fetch_row(res)) {
	//			if (row[0] != 0) {
	//				std::cout << endl << endl << row[0]<< endl;
	//			}
	//			else{
	//				std::cout << endl << endl<<"Can't" << endl;
	//			
	//			}
	//		}
	//	
	//	}
	//	else {
	//		std::cout << "Query Failed: " << mysql_error(conn) << endl;
	//	}
	//}
	//else {
	//	puts("ERROR");
	//}
	//			
	//return*/
//}
