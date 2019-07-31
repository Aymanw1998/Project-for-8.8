
#include <mysql.h>
#include <iostream>
#include "recording_studio.h"
int main(int argc, char* argv[])
{
	commandList();
	while (1)
	{
		int cmdNum;
		cout <<endl<<endl<< "Choose command number: ";cin >> cmdNum;

		if (cin.fail()) {cin.clear();cin.ignore();}
		cout << endl;
		switch (cmdNum)
		{
		case 0:commandList();break;
		case 1:command1();break;
		case 2:command2();break;
		case 3:command3();break;
		case 4:command4();break;
		case 5:command5();break;
		case 6:command6();break;
		case 7:command7();break;
		case 8:command8();break;
		case 9:command9();break;
		case 10:command10();break;
		case 11:command11();break;
		case 12:command12();break;
		case 13:command13();break;
		case 14:command14();break;
		case 15:command15();break;
		case 16:return 0;
		}

		cout << endl;
	}

	return 0;
}

