#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>


using namespace std;
//=============================== Manager class =============================================
class Manager{
private:
	int num, action;
public:
	void close_account(){

		cout << "close account" << endl; // delete information from database
		cout << "enter client id number to close: " <<endl;
		int close_num;
		cin >> close_num;

		bool deleted = 0;

		ifstream myReadFile;
		myReadFile.open("database.txt");

		ofstream tempFile;
		tempFile.open("temp.txt");

		int temp_id;
		double temp_chequing, temp_savings;
		string temp_type;

		// while not found id to be deleted, copy to temporary file
		// skip line to be deleted
		// rename temporary file to "database.txt"
		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {

				// check id

				while (myReadFile >> temp_id >> temp_type >> temp_chequing
						>> temp_savings) {
					if (temp_id != close_num) {
						tempFile << temp_id << "\t" << temp_type << "\t"
								<<  setprecision(2) << fixed << temp_chequing <<"\t"
								<<  setprecision(2) << fixed << temp_savings<< "\n" ;
					}
					if (temp_id == close_num) { // if is a client, then display information
							deleted = 1;
					}

				}
			}
		}
		myReadFile.close();
		tempFile.close();

		remove("database.txt");
		rename("temp.txt","database.txt");

		if (deleted){
			cout << "account " << close_num << " was deleted" << endl;
		}
		else{
			cout << "account was not found" << endl;
		}
	}

	void open_account(){
		cout << "Open new customer account\n" << endl; // add information to database
		int open_num;
		double open_savings, open_chequing;
		cout << "\nEnter new account number: ";
		cin >> open_num;
		cout << "\nEnter initial amount in chequing: ";
		cin >> open_savings;
		cout << "\nEnter initial amount in savings: ";
		cin >> open_savings;

		ifstream myReadFile;
		myReadFile.open("database.txt");

		ofstream tempFile;
		tempFile.open("temp.txt");

		int temp_id;
		bool exists = false;
		double temp_chequing, temp_savings;
			string temp_type;

		// while not found id to be deleted, copy to temporary file
		// skip line to be deleted
		// rename temporary file to "database.txt"
		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {
				// check id
				while (myReadFile >> temp_id >> temp_type >> temp_chequing >> temp_savings) {
					if (temp_id == open_num) {
						cout << "Client ID already exists, try another..";
						exists = true;
					}
					tempFile << temp_id << "\t" << temp_type << "\t"
							<<  setprecision(2) << fixed << temp_chequing <<"\t"
							<<  setprecision(2) << fixed << temp_savings<< "\n" ;

				}
			}
		}
		if (!exists) {
			tempFile << open_num << "\t" << "client" << "\t"
				<<  setprecision(2) << fixed << open_chequing <<"\t"
				<<  setprecision(2) << fixed << open_savings << "\n" ;
			cout << "New Client added ...\n";
		}

		myReadFile.close();
		tempFile.close();

		remove("database.txt");
		rename("temp.txt","database.txt");



	}

	void display_all(){
		ifstream myReadFile;
		myReadFile.open("database.txt");
		int temp_id;
		double temp_chequing, temp_savings;
		string temp_type;

		cout
				<< "--------------------ALL ACCOUNT DETAILS----------------------------\n"
						"\t ID"
						"\t CHEQUING"
						"\tSAVINGS \n" << endl;
		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {

				// check id

				while (myReadFile >> temp_id >> temp_type >> temp_chequing
						>> temp_savings) {
					if (temp_type == "client") { // if is a client, then display information

						cout << "\t " << temp_id << "\t " <<
								setprecision(2) << fixed<< temp_chequing<< "\t \t" <<
								setprecision(2) << fixed << temp_savings << endl;
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
		int temp_id;
		double temp_chequing, temp_savings;
		string temp_type;

		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {
				// check id
				while (myReadFile >> temp_id >> temp_type >> temp_chequing
						>> temp_savings) {
					if (temp_id == user_id) { // if the id matches, then print information
						cout << "client ID: " << user_id << "\tchequing: $ "
								<<  setprecision(2) << fixed << temp_chequing << "\tsavings: $ "
								<<  setprecision(2) << fixed << temp_savings << endl;
					}
				}
			}
		}
		myReadFile.close();
	}

	void view_aggregate(){
		double total_chequing=0;
		double total_savings=0;
		int num_clients=0;

		ifstream myReadFile;
		myReadFile.open("database.txt");

		int temp_id;
		double temp_chequing, temp_savings;
		string temp_type;

		// while not found id to be deleted, copy to temporary file
		// skip line to be deleted
		// rename temporary file to "database.txt"
		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {

				// check id

				while (myReadFile >> temp_id >> temp_type >> temp_chequing
						>> temp_savings) {
					if (temp_type == "client"){
						num_clients ++;
						total_chequing = total_chequing + temp_chequing;
						total_savings = total_savings + temp_savings;
					}
				}
			}
		}
		myReadFile.close();

		cout << "aggregate data "
				"\ntotal number of clients: " << num_clients <<
				"\ntotal chequing: " <<  setprecision(2) << fixed << total_chequing <<
				"\ntotal savings: "  <<  setprecision(2) << fixed << total_savings << endl;
	}
	void menu(){

		char action;

		do{
			cout<<"-----------------MENU MANAGER--------------------------\n\t"
						"1 - open an account\n\t"
						"2 - close an account\n\t"
						"3 - view an account\n\t"
						"4 - view all accounts\n\t"
						"5 - view aggregate data\n\t"
						"6 - exit"<< endl;
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
				case '4':
					display_all();
					break;
				case '5':
					view_aggregate();
					break;
				case'6':
					break;
				default:
					cout << "select from the menu" << endl;
			}
		}while(action != '6');
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
		update_database();
		view_balance();
	}

	void withdraw(){
		cout << "\nWithdraw Amount: $";
		double withdraw;
		cin >> withdraw;

		cout << "Withdraw to Savings or Chequing (s|c)";
		char sc;
		cin >> sc;

		if (sc == 's' && savingsBalance > withdraw)
			savingsBalance -= withdraw;
		else if (sc == 's' && savingsBalance < withdraw) // if insifficient funds warning
			cout << "Warning - Insufficient funds\n";

		if (sc == 'c' && chequingBalance > withdraw) {
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
		else if(sc == 'c' && chequingBalance < withdraw)
			cout << "Warning - Insufficient funds\n";

		cout << "Updated ";
		update_database();
		view_balance();
	}

	void transfer(){// change information in database
		int action;
		double transfer_amount;
		cout << "1 - chequing to savings\n"
				"2 - savings to chequing\n" ;
		cin >> action;
		cout << "enter amount to transfer: ";
		cin >> transfer_amount;

		if (action ==1){
			savingsBalance = savingsBalance + transfer_amount;
			chequingBalance = chequingBalance - transfer_amount;
		}
		else if(action == 2){
			savingsBalance = savingsBalance - transfer_amount;
			chequingBalance = chequingBalance + transfer_amount;
		}
		update_database();
		view_balance();
	}
	void view_balance(){
		cout << "Client Balance:\n\n " <<
				"\tSavings:\t$" <<  setprecision(2) << fixed << savingsBalance <<
				"\n\tChequing:\t$" << setprecision(2) << fixed << chequingBalance << endl;
	}

	void open_new_account(){

	}

	void update_database(){ // find id number and deposits or withdraws amounts
		ifstream myReadFile;
		 myReadFile.open("database.txt");

		 ofstream tempFile;
		 tempFile.open("temp.txt");

		 int temp_id;
		 double temp_chequing, temp_savings;
		 string temp_type;

		 if (myReadFile.is_open()) {
			 while (!myReadFile.eof()) {
				while (myReadFile >> temp_id >> temp_type >> temp_chequing >> temp_savings ){
					if(temp_id != num){
						tempFile << temp_id << "\t" << temp_type << "\t"
								<<  setprecision(2) << fixed << temp_chequing <<"\t"
								<<  setprecision(2) << fixed<< temp_savings<< "\n" ;
					}
					else{
						// if the id matches, then store the information
						tempFile << temp_id << "\t" << temp_type << "\t"
								<<  setprecision(2) << fixed<< chequingBalance <<"\t"
								<<  setprecision(2) << fixed<< savingsBalance<< "\n" ;
					}
				}
			 }
		}
		myReadFile.close();
		tempFile.close();
		remove("database.txt");
		rename("temp.txt","database.txt");

	}
	void menu(){
		char action;
		do {
			cout<<"\n-----------------MENU CLIENT--------------------------\n\t"
					"1 - deposit\n\t"
					"2 - withdraw\n\t"
					"3 - transfer\n\t"
					"4 - view balance\n\t"
					"5 - transfer\n\t"
					"6 - exit"<< endl;

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
					transfer();
					break;
				case '6':
					break;
				default:
					cout << "select from the menu" << endl;
			}

		} while (action != '6');

	}

};
//=============================== Database class =============================================


class Database{
private:
	int num;
	double chequing, savings;
	string user_type; // manager, client, or maint

public:

	void enter_num(){
		cout << "Banking System:\n\nEnter your login id (manager = 1, maintenance = 2): ";
		cin >> num ;
	}
	void get_user_info(){ // retrieves user information from database
		ifstream myReadFile;
		 myReadFile.open("database.txt");
		 int temp_id;
		 double temp_chequing, temp_savings;
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
	cout << setprecision(2) <<endl; // show 2 decimal precision
	Database temp;
	temp.enter_num();
	temp.get_user_info();
	temp.login();

	return 0;
}
