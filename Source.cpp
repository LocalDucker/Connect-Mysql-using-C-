#include <iostream>
#include <mysql.h>
#include <conio.h>
#include <iomanip>

using namespace std;

int main() {

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0); // отримуємо дескриптор
	if (conn == NULL) {
		cout << "Error: can't create descriptor";
		system("pause");
		return 0;
	}

	if (!mysql_real_connect(conn, "localhost", "root", "mysql", "lab", 3306, NULL, 0)) {
		cout << "Error: can't connect to database  " << mysql_error(conn);
		system("pause");
		return 0;
	}
	else {
		cout << "Connection success!\n";
	}

	string insert_query = "INSERT INTO adress(region, city, street) VALUES (\"";
	string region, city, street;

	//консольне меню
	bool exit_menu = true;
	char key;
	while (exit_menu) {
		cout << "1. Output database\n";
		cout << "2. Insert new row\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: \n";
		switch ((key = _getch())) {
			cout << "\n";
		case '1':
			system("cls");
			mysql_query(conn, "SELECT * FROM adress");
			if (res = mysql_store_result(conn)) {
				while (row = mysql_fetch_row(res)) {
					for (int i = 0; i < mysql_num_fields(res); i++) {
						cout << row[i] << "\n";

					}
					cout << "\n";
				}
			}
			else {
				cout << "Query Failed!";
			}
			system("pause");
			system("cls");
			break;
		case '2':
			system("cls");
			cout << "Enter region: "; cin >> region;
			cout << "\nEnter city: "; cin >> city;
			cout << "\nEnter street: "; cin >> street;
			insert_query += region + "\", \"" + city + "\", \"" + street + "\")";
			if (!mysql_query(conn, insert_query.c_str())) {
				cout << "Success!";
			}
			else {
				cout << "Error";
			}
			system("pause");
			system("cls");
			break;
		case '3':
			system("cls");
			exit_menu = false;
			break;
		}
	}
	return 0;
}
