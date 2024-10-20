#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

vector<int> duplicates;
int x;

class Account
{
	int AccNo;
	char name[50];
	int deposit;
	char type;

public:
	int duplicate(int AccNo)
	{
		for (int i = 0; i < duplicates.size() - 1; i++)
		{
			if (AccNo == duplicates[i])
			{
				return 1;
			}
		}
		return 0;
	}
	void create_Account()
	{

		cout << "\nEnter The Account No. :";
		cin >> AccNo;
		duplicates.push_back(AccNo);
		x = duplicate(AccNo);
		if (x == 0)
		{
			cout << "\n\nEnter The Name of The Account Holder : ";
			cin >> name;
			cout << "\nEnter Type of The Account (C/S) : ";
			cin >> type;
			cout << "\nEnter The Initial amount : ";
			cin >> deposit;
			cout << "\n\n\nAccount Created";
		}
		else
		{
			cout << "\n\nAccount already exists !";
		}
	}
	void show_Account() const
	{
		cout << "\nAccount No. : " << AccNo;
		cout << "\nAccount Holder Name : " << name;
		cout << "\nType of Account : " << type;
		cout << "\nBalance amount : " << deposit;
	}

	void dep(int x)
	{
		deposit += x;
	}

	void draw(int x)
	{
		deposit -= x;
	}

	void report() const
	{
		cout << AccNo << setw(10) << " " << name << setw(10) << " " << type << setw(10) << deposit << endl;
	}

	void modify()
	{
		cout << "\nAccount No. : " << AccNo;
		cout << "\nModify Account Holder Name : ";
		cin >> name;
		cout << "\nModify Type of Account : ";
		cin >> type;
		cout << "\nModify Balance amount : ";
		cin >> deposit;
	}

	int retAccNo() const
	{
		return AccNo;
	}

	int retdeposit() const
	{
		return deposit;
	}

	char rettype() const
	{
		return type;
	}
};

void new_Account();
void display_Account(int x);
void delete_Account(int x);
void modify_account(int x);
void display_all();
void deposit_withdraw(int x, int y);

int main()
{

	char ch;
	int num;
	int i = 0;
	do
	{

		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t1. NEW Account";
		cout << "\n\n\t2. DEPOSIT AMOUNT";
		cout << "\n\n\t3. WITHDRAW AMOUNT";
		cout << "\n\n\t4. BALANCE ENQUIRY";
		cout << "\n\n\t5. ALL Account HOLDER LIST";
		cout << "\n\n\t6. CLOSE AN Account";
		cout << "\n\n\t7. EXIT";
		cout << "\n\n\tSelect Your Option (1-7) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			new_Account();
			break;
		case '2':
			cout << "\n\n\tEnter The Account No. : ";
			cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The Account No. : ";
			cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The Account No. : ";
			cin >> num;
			display_Account(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The Account No. : ";
			cin >> num;
			do
			{
				if (num == duplicates[i])
				{
					duplicates[i] = -1;
					break;
				}
				i++;
			} while (i < duplicates.size());
			delete_Account(num);
			break;
		case '7':
			cout << "\n\n\tThanks for using bank managemnt system";
			break;
		default:
			cout << "\a";
		}
	} while (ch != '7');
	return 0;
}

void new_Account()
{

	Account ac;
	ofstream outFile;
	outFile.open("Account.dat", ios::binary | ios::app);
	ac.create_Account();
	if (x == 0)
	{
		outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
		outFile.close();
	}
}

void display_Account(int n)
{

	Account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("Account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open ";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
	{
		if (ac.retAccNo() == n)
		{
			ac.show_Account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found = false;
	Account ac;
	fstream File;
	File.open("Account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
		if (ac.retAccNo() == n)
		{
			ac.show_Account();
			cout << "\n\nEnter The New Details of Account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(Account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *>(&ac), sizeof(Account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

void delete_Account(int n)
{

	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("Account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open ";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
	{
		if (ac.retAccNo() != n)
		{
			outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("Account.dat");
	rename("Temp.dat", "Account.dat");
	cout << "\n\n\tRecord Deleted ..";
}

void display_all()
{

	Account ac;
	ifstream inFile;
	inFile.open("Account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open ";
		return;
	}
	cout << "\n\n\t\tAccount HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type           Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	Account ac;
	fstream File;
	File.open("Account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
		if (ac.retAccNo() == n)
		{
			ac.show_Account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *>(&ac), sizeof(Account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}