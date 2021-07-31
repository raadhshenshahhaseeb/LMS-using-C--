#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
int userAccess();
int adminAccess();
int loginAdmin();
int userLogin();
int details();
int signUp(int op);
int issueBook();
int submitBook();
int deleteBook();
int addBook();

using namespace std;

int main()
{
	int ch = 1, op;
	system("cls");
	do
	{
		cout << "\nPress 1 to Login as Admin\nPress 2 to Login as User\nPress 3 to Signup\nPress 4 to quit\n";
		cin >> ch;
	} while (ch != 1 && ch != 2 && ch != 3 && ch != 4);
	switch (ch)
	{
	case 1:
		loginAdmin();
		main();
	case 2:
		userLogin();
		main();
	case 3:
		cout << "Sign Up as \n1:Admin\n2:User\n";
		cin >> op;
		signUp(op);
		break;
	case 4:
		exit(1);
	default:
		cout << "Wrong input\n";
	}
	return 1;
}

int signUp(int op)
{
	fstream file;
	string username, password, up;
	system("cls");
	cout << "Enter Userame:\n";
	cin.sync();
	getline(cin, username);
	cout << "\nEnter Password:\n";
	getline(cin, password);
	username = username + password;
	if (op == 1)
	{
		file.open("signupAdmin.txt", ios::app);
		file << username << endl;
		file.close();
	}
	if (op == 2)
	{
		file.open("signupUser.txt", ios::app);
		file << username << endl;
		file.close();
	}
}

int loginAdmin()
{
	system("cls");
	ifstream file;
	int userInput;
	string username, password, up, line;
	cout << "Enter Username:\n";
	cin.sync();
	getline(cin, username);
	cout << "\nEnter Password:\n";
	getline(cin, password);
	username = username + password;
	file.open("signupAdmin.txt", ios::app);
	bool found = false;
	if (file.is_open())
	{
		while (getline(file, line) && !found)
		{
			if (line.compare(username) == 0)
			{ //match strings exactly!
				found = true;
				cout << "found"; // found is true => break loop
			}
		}
		file.close(); //close the file before recursivly opening it again later
		if (found)
		{
			adminAccess();
		}

		else
		{
			cout << "\nWrong Password\nEnter q to quit\nPress any key to return main menu\n";
			cin >> userInput;
		}
		if (userInput == 'q' || userInput == 'Q')
		{
			exit(1);
		}
		else
		{
			main();
		}
	}
}

int adminAccess()
{
	int choice = 0;
	while (choice != 5)
	{
		system("cls");
		cout << "\t\t\tWelcome\n\n\n";
		cout << "\t\tPress 1 to Issue book\n";
		cout << "\t\tPress 2 to Add book\n";
		cout << "\t\tPress 3 to Submit book\n";
		cout << "\t\tPress 4 to Delete book\n";
		cout << "\t\tPress 5 to See All Details\n";
		cout << "\t\tPress 6 to Logout\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			issueBook();
			adminAccess();
			break;
		case 2:
			addBook();
			adminAccess();
			break;
		case 3:
			submitBook();
			adminAccess();
			break;
		case 4:
			deleteBook();
			adminAccess();
			break;
		case 5:
			details();
			adminAccess();
			break;
		case 6:
			exit(1);
			break;

		default:
			adminAccess();
			break;
		}
	}
}
int userLogin()
{
	system("cls");
	ifstream file;
	int userInput;
	string reg, pass, up, line;
	cout << "Enter Reg:\n";
	cin.sync();
	getline(cin, reg);
	cout << "\nEnter Password:\n";
	getline(cin, pass);
	reg = reg + pass;
	file.open("signupUser.txt", ios::app);
	bool found = false;
	if (file.is_open())
	{
		while (getline(file, line) && !found)
		{
			if (line.compare(reg) == 0)
			{				  //match strings exactly!
				found = true; // found is true => break loop
			}
		}
		file.close(); //close the file before recursivly opening it again later
		if (found)
		{
			userAccess();
		}
		else
		{
			cout << "\nWrong Password\nEnter q to quit\nPress any key to return main menu\n";
			cin >> userInput;
		}
		if (userInput == 'q' || userInput == 'Q')
		{
			exit(1);
		}
		else
		{
			main();
		}
	}
}

int addBook()
{
	fstream file;
	string bookName, bookId, bookWriter;
	cout << "Enter Book Name:\n";
	cin.sync();
	getline(cin, bookName);
	cout << "\nEnter Writer:\n";
	getline(cin, bookWriter);
	file.open("bookName.txt", ios::app);
	file << endl
		 << bookName << endl;
	file << bookWriter << endl;
	file.close();
	cout << "Book Added";
	return 1;
}

int deleteBook()
{
	string line, name;
	int skip = 0;
	cout << "\nPlease Enter the name of record you want to delete: \n";
	cin >> name;
	ifstream file;
	file.open("bookName.txt");
	ofstream temp;
	temp.open("temp.txt");

	//	bool found = false;
	//	if(file.is_open()) {
	//		while(getline(file,line) && !found) {
	//			if (line.compare(name) == 0) { //match strings exactly!
	//				found = true; // found is true => break loop
	//			}
	//		}
	//		file.close(); //close the file before recursivly opening it again later
	//
	//	}
	//	if(!found){
	//		cout<<"\nWrong Book: No Record Found\n";
	//		system("pause");
	//		adminAccess();
	//	}

	while (getline(file, line))
	{
		if ((line != name) && !(skip > 0))
		{
			temp << line << endl;
		}
		else
		{
			if (skip == 0)
			{
				skip = 2; // Skip the next two lines also
			}
			else
			{
				--skip;
			}
		}
	}

	temp.close();
	file.close();
	remove("bookName.txt");
	rename("temp.txt", "bookName.txt");
	cout << endl
		 << endl
		 << endl;
	cout << "\nBook was deleted successfully\n";
	system("pause");
	return 1;
}

int issueBook()
{
	fstream file;
	int bookId, days;
	char choice;
	char nameSt[12], nameBook[12], regNum[11];
	system("cls");
	do
	{

		cout << "\n\n\n\t\t\t\t\tIssue Book\n\n\n";
		cout << "Enter Book Name:\n";
		cin >> nameBook;
		cout << "\nEnter reg number: e.g. Fa16BSENUM\n";
		cin >> regNum;
		cout << "Issue Days: # only\n";
		cin >> days;
		cout << "\nPress N to Edit info, any other key to continue...\n";
		cin >> choice;
	} while (choice == 'N' || choice == 'N');

	string name(nameBook);
	string reg(regNum);
	name += reg;

	file.open("issuebook.txt", ios::app);
	file << endl;
	file << name << endl;
	file << "days:" << days << endl;
	file.close();
	cout << "\nBook Added Sucessfully\n";
	system("pause");
	return 1;
}
int submitBook()
{

	char choice;
	char nameBook[12], regNum[11];
	system("cls");
	do
	{

		cout << "\n\n\n\t\t\t\t\tIssue Book\n\n\n";
		cout << "Enter Book Name:\n";
		cin >> nameBook;
		cout << "\nEnter reg number: e.g. Fa16BSENUM\n";
		cin >> regNum;
		cout << "\nPress N to Edit info, any other key to continue...\n";
		cin >> choice;
	} while (choice == 'N' || choice == 'N');

	string name(nameBook);
	string reg(regNum);
	name += reg;

	string line;
	int skip = 0;

	ifstream file;
	file.open("issueBook.txt");
	ofstream temp;
	temp.open("temp.txt");

	while (getline(file, line))
	{
		if ((line != name) && !(skip > 0))
		{
			temp << line << endl;
		}
		else
		{
			if (skip == 0)
			{
				skip = 2; // Skip the next two lines also
			}
			else
			{
				--skip;
			}
		}
	}

	temp.close();
	file.close();
	remove("issueBook.txt");
	rename("temp.txt", "issueBook.txt");
	cout << endl
		 << endl
		 << endl;
}
int details()
{

	ifstream file;
	file.open("issueBook.txt");
	char output[100];
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> output;
			cout << output << endl;
		}
	}
	file.close();
	system("pause");
}
int userAccess()
{
	int choice = 0;
	while (choice != 5)
	{
		system("cls");
		cout << "\t\t\tWelcome\n\n\n";
		cout << "\t\tPress 1 to Issue book\n";
		cout << "\t\tPress 2 to See books\n";
		cout << "\t\tPress 3 to Logout\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			issueBook();
			userAccess();
			break;
		case 2:

			break;

		case 3:
			exit(1);
			break;

		default:
			userAccess();
			break;
		}
	}
}
