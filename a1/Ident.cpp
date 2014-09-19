#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
//=============================== Manager class =============================================
class Manager{
private:
	int num, action;
public:
	void close_account(){
		cout << "close account" << endl; // delete information from database
	}

	void open_account(){
		cout << "open account" << endl; // add information to database
	}

	void display_all(){
		ifstream myReadFile;
					 myReadFile.open("database.txt");
					 int temp_id, temp_chequing, temp_savings;
					 string temp_type;

					 cout << "--------------------ALL ACCOUNT DETAILS----------------------------\n"
							 "\t ID"
							 "\t CHEQUING"
							 "\tSAVINGS \n" << endl;
					 if (myReadFile.is_open()) {
						 while (!myReadFile.eof()) {

							 // check id

							while (myReadFile >> temp_id >> temp_type >> temp_chequing >> temp_savings ){
								if(temp_type == "client"){ // if is a client, then display information

									cout   << "\t " << temp_id << "\t "<< temp_chequing << "\t \t" << temp_savings <<endl;
								}
							}
						 }
					}
					myReadFile.close();
	}

	void display_user(){// shows details of a particular client
		int user_id;

		cout<< "enter customer id:";
		cin >> user_id;

		ifstream myReadFile;
				 myReadFile.open("database.txt");
				 int temp_id, temp_chequing, temp_savings;
				 string temp_type;

				 if (myReadFile.is_open()) {
					 while (!myReadFile.eof()) {

						 // check id

						while (myReadFile >> temp_id >> temp_type >> temp_chequing >> temp_savings ){
							if(temp_id == user_id){ // if the id matches, then print information
								cout<<
									"client ID: " << user_id <<
									"\tchequing: $ " << temp_chequing <<
									"\tsavings: $ " << temp_savings << endl;
							}
						}
					 }
				}
				myReadFile.close();
	}

	void menu(){

		cout<<"-----------------MENU MANAGER--------------------------\n\t"
						"1 - open an account\n\t"
						"2 - close an account\n\t"
						"3 - view an account\n\t"
						"4 - view all accounts"<< endl;
		char action;
		cin >> action;

		switch(action){
			case '1':
				open_account();
				break;
			case'2':
				close_account();
				break;
			case'3':
				display_user();
				break;
			case'4':
				display_all();
				break;
			default:
				cout << "select from the menu" << endl;
		}

		// go back to menu
	}
};
//=============================== Client class =============================================
class Client{
private:
	int num;
	double savingsBalance;
	double chequingBalance;
public:


	Client(int id) {
		this->num=id;
		this->savingsBalance  = 0;
		this->chequingBalance  = 0;
	}

	Client(int id, double savingsBalance, double chequingBalance) {
		this->num=id;
		this->savingsBalance  = savingsBalance;
		this->chequingBalance  = chequingBalance;
	}

	void deposit() {
		cout << "Deposit Amount: $";
		double deposit;
		cin >> deposit;

		cout << "Deposit to Savings or Chequing (s|c)";
		char sc;
		cin >> sc;
		if (sc == 's') savingsBalance += deposit;
		if (sc == 'c') chequingBalance += deposit;

		cout << "Updated ";
		view_balance();
	}

	void withdraw(){
		cout << "\nWithdraw Amount: $";
		double withdraw;
		cin >> withdraw;

		cout << "Withdraw to Savings or Chequing (s|c)";
		char sc;
		cin >> sc;
		if (sc == 's') savingsBalance -= withdraw;
		if (sc == 'c') {
			if ((chequingBalance - withdraw) <= 1000) {
				cout << "Warning - Resulting balance will be less then $1000 - a $2 charge will be levied, proceed? (y|n)";
				char answer;
				cin >> answer;
				if (answer == 'y')
					chequingBalance -= (withdraw + 2.);
			} else {
				chequingBalance -= withdraw;
			}
		}
		cout << "Updated ";
		view_balance();
	}
	void check_sufficient_funds(){

	}
	void transfer(){// change information in database

	}
	void view_balance(){
		cout << "Client Balance:\n\n " <<
				"\tSavings:\t$" << savingsBalance <<
				"\n\tChequing:\t$" <<	chequingBalance << endl;

	}
	void warning_message(){

	}
	void open_new_account(){

	}

	void menu(){
		char action;
		do {
			cout<<"\n-----------------MENU CLIENT--------------------------\n\t"
					"1 - deposit\n\t"
					"2 - withdraw\n\t"
					"3 - transfer\n\t"
					"4 - view balance\n\t"
					"5 - exit"<< endl;

			cin >> action;

			switch(action){
				case '1':
					deposit();
					break;
				case '2':
					withdraw();
					break;
				case '3':
					transfer();
					break;
				case '4':
					view_balance();
					break;
				case '5':
					break;
				default:
					cout << "select from the menu" << endl;
			}

		} while (action != '5');

	}
};
//=============================== Database class =============================================


class Database{
private:
	int num, chequing, savings;
	string user_type; // manager, client, or maint

public:

	void enter_num(){
		cout << "enter your login id: ";
		cin >> num ;
	}
	void get_user_info(){ // retrieves user information from database
		ifstream myReadFile;
		 myReadFile.open("database.txt");
		 int temp_id, temp_chequing, temp_savings;
		 string temp_type;

		 if (myReadFile.is_open()) {
			 while (!myReadFile.eof()) {
				while (myReadFile >> temp_id >> temp_type >> temp_chequing >> temp_savings ){
					if(temp_id == num){ // if the id matches, then store the information
						chequing = temp_chequing;
						savings = temp_savings;
						user_type = temp_type;
					}
				}
			 }
		}
		myReadFile.close();
	}

	void display_user(){

		cout<< 				"------------------------------------------------"<<
							"\n		ID: " << num <<
							"\n		TYPE: " << user_type <<
							"\n		Chequing: " << chequing <<
							"\n		Savings: " << savings <<
							"\n------------------------------------------------"<< endl;
	}

	// switch roles depending on who is using the program
	void login(){
		if (user_type=="manager"){
			Manager m;
			m.menu();
		}
		else if(user_type == "client"){
			Client c(num, savings, chequing);
			c.menu();
		}
		//else if (type == "maint").............
	}
};


int main()
{
	Database temp;
	temp.enter_num();
	temp.get_user_info();
	temp.login();

	return 0;
}
