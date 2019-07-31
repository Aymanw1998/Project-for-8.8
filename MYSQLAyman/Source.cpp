//#include <mysqlx/xapi.h>
//#include <iostream>
//
//using namespace std;
//
//int main() {
//	char err_msg[256] = {};
//	int err_code = 0;
//	//creration of an sql connection aka session to the mysql server
//	mysqlx_session_t* sess = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "root", "23061998", "sakila", err_msg, &err_code);
//	if (NULL == sess) {
//		cerr << err_msg << endl;
//		exit(err_code);
//	}
//
//	char query1[] = { "show tables" };
//
//	mysqlx_result_t* res = mysqlx_sql(sess, query1, MYSQLX_NULL_TERMINATED);
//
//	if (NULL != res) {
//		char buff[256]; size_t size = 0;
//
//		do {
//			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
//			while (NULL != row) {
//				size = sizeof(buff);
//				mysqlx_get_bytes(row, 0, 0, buff, &size);
//				cout << buff << endl;
//				row = mysqlx_row_fetch_one(res);
//			}
//		} while (RESULT_OK == mysqlx_next_result(res));
//	}
//	else {
//		cerr << mysqlx_error_message(sess) << endl;
//		exit(mysqlx_error_num(sess));
//	}
//
//	cout << "------------------------" << endl;
//
//	char query2[225] = "SELECT * FROM actor ";
//	
//	//res = mysqlx_sql(sess, query2, MYSQLX_NULL_TERMINATED);
//	mysqlx_stmt_t* stmt = mysqlx_sql_new(sess, query2, MYSQLX_NULL_TERMINATED);
//
//	if (RESULT_OK != mysqlx_stmt_bind(stmt, PARAM_SINT(100), PARAM_END)) {
//		cerr << "error binding parameters\n";
//		exit(2);
//	}
//	res = mysqlx_execute(stmt);
//
//	if (NULL != res) {
//		char buff[256]; size_t size = 0;
//		uint32_t cols = mysqlx_column_get_count(res);
//
//		do {
//			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
//			while (NULL != row) {
//				for (uint32_t i = 0; i < cols; ++i) {
//					int64_t id;
//					size = sizeof(buff);
//					if (i > 0)
//						mysqlx_get_bytes(row, i, 0, buff, &size);
//					else mysqlx_get_sint(row, 0, &id);
//						switch (i) {
//						case 0:
//							/*id = 0;
//							memcpy(&id, buff, size);*/
//							cout << id;
//							break;
//						case 1:
//						case 2:
//						case 3:
//							cout << buff;
//							break;
//						default:
//							cout << "undefined";
//						}
//					if (9 > size)
//						cout << "\t";
//					cout << "\t|\t";
//				}
//				cout << endl;
//				row = mysqlx_row_fetch_one(res);
//			}
//		} while (RESULT_OK == mysqlx_next_result(res));
//	}
//	else {
//		cerr << mysqlx_error_message(sess) << endl;
//		exit(mysqlx_error_num(sess));
//	}
//
//	mysqlx_session_close(sess);
//
//	getchar();
//	return 0;
//}