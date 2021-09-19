/* Bank Management System */
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>

#include <string>
#include "function1.h"
#include "function2.h"
using namespace std;

string create_accn(int id){
    string concat;
    static int random = 2021;
    concat = to_string(random) + to_string(id) + to_string(rand());
    return concat;
}

//first function
void bank :: openAccount(){
    id = totalCustomers;
    acc_num = create_accn(totalCustomers);
    cout << "Enter Your Full Name : ";
    cin.ignore();
    cin.getline(name,40);
    cout << "Enter adress : ";
    cin.getline(address,40);
    cout << "Which type of account to create \t 1.Saving \t 2.Current : ";
    cin.getline(type, 10);
    cout << "Amount to deposit : ";
    cin >> balance;
    cout << "Congratulations! Account has been created successfully.\n";
}

//second function
    void bank ::depositMoney(){
        int a;
        cout << "Amount to deposit : ";
        cin >> a;
        balance += a;
        cout << "Total amount deposited = " << balance<<endl;
    }

//third function
    void bank ::displayAccount(){
        cout << "ID : " << id << endl;
        cout << "Account Number : " << acc_num<<endl;
        cout << "Your Name : "<<name<<endl;
        cout << "Your Address : " << address<<endl;
        cout << "Your balance : "<<balance<<endl;
        cout << "Type of account : " << type<<endl;
    }
    
//forth function
    void bank :: withdrawMoney(){
        float amount;
        cout<<"Enter amount to withdraw : ";
        cin >> amount;
        balance = balance - amount;
        cout << "Total balance left : " << balance<<endl;
    }

//fifth function
    void bank::modify(){
        int ch3, chh3;
        cout << "Customer's ID : " << id << "\t Account Number : " << acc_num<<endl;
        cout << "Modify Account holder's name : ";
        cin.ignore();
        cin.getline(name, 40);
        cout << "Modify Account type : ";
        cin.getline(type, 10);
        cout << "1. Add money or 2. Withdraw Money ? : ";
            cin >> ch3; //choice to take or put
            cout << "Enter amount : ";
            cin >> chh3;
        switch(ch3){
            case 1:
                balance += chh3; //for adding
                break;
            case 2:
                balance -= chh3; //for taking out
                break;
        }
    }

//sixth function
    void bank :: report() const{
        cout << id << setw(6) << acc_num << setw(6) << name << setw(6) << address << setw(6) << type << setw(6) << balance << endl;
    }
    
    int main()
    {
        //program execute form here |-->
        char choice2;
        int choice;
        bank object;
        do
        {
            cout << "1.  Create an account \n";
            cout << "2.  Deposit Money \n";
            cout << "3.  Withdraw Money \n";
            cout << "4.  Display Account \n";
            cout << "5.  Exit \n";
            cout << "Enter your choice : ";
            cin >> choice;
            system("cls");

            switch (choice)
            {
            case 1:
                cout << "1. Create account \n";
                object.openAccount();
                break;

            case 2:
                cout << "2. Deposit Money \n";
                object.depositMoney();
                break;

            case 3:
                cout << "3. Withdraw Money \n";
                object.withdrawMoney();
                break;

            case 4:
                cout << "4. Display Account \n";
                object.displayAccount();
                break;
            case 5:
                exit(1);
            default:
                cout << "Invalid input \n";
                continue;
            }

            cout << "Do you want to go back to menu? (Y/N) : \n";
            choice2 = getch();

            if (choice2 == 'N' || choice2 == 'n')
                exit(0);

        } while (choice2 = 'Y' || choice2 == 'y');

        return 0;
}
// functions to write in file
void writeAccount(){
    bank acc;
    ofstream afile;
    afile.open("Bank.dat", ios::binary | ios::app);
    acc.openAccount();
    afile.write(reinterpret_cast<char *>(&acc), sizeof(bank));
    afile.close();
}

//fucntion to read inside file

void displayAccount(int n){
    bank acc;
    bool what = false;
    ifstream inFile;
    inFile.open("bank.dat", ios::binary);
    if(!inFile){
        cout << "File not found!!\n";
        return;
    }
    cout << "\nBalance available is : \n";

    while(inFile.read(reinterpret_cast<char *>(&acc),sizeof(bank)))
        {
            if(acc.ReturnAccnum()==n){
                acc.displayAccount();
                what = true;
            }
        }
        inFile.close();
        if(what == false){
            cout << "Account ID doesn't exist.\n";
        }
}

void modifyAccount(int n){
    bool check = false;
    bank acc;
    fstream File;
    File.open("bank.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout << "File not found!!\n";
        return;
        }
    while(!File.eof() && check == false){
        File.read(reinterpret_cast<char *>(&acc), sizeof(bank));
        if(acc.ReturnAccnum() == n){
            acc.displayAccount();
            cout << "Enter new details of the account"<<endl;
            acc.modify();
            int pos = (-1) * static_cast<int>(sizeof(acc));
            cout << "\n\n\t Recod is modified :)\n";
            check = true;
        }
    }
    File.close();
    if(check == false)
            cout << "Account ID doesn't exist.\n";
}

//function to delete record
void deleteAccount(int n){
    bank acc;
    ifstream inFile;
    ofstream outFile;
    inFile.open("bank.dat", ios::binary);
    if (!inFile){
        cout << "File not found!!\n";
        return;
    }
    outFile.open("temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char *>(&acc), sizeof(bank)))
    {
        if(acc.ReturnAccnum() != n)
        {
            outFile.write(reinterpret_cast<char *>(&acc), sizeof(bank));
        }
    } 
    inFile.close();
    outFile.close();
    remove("bank.dat");
    rename("temp.dat","bank.dat");
    cout << "\n\n\tRecord is deleted :)\n";
}

//////////////Function to display all accounts available//////////////////

void displayAll(){
    bank acc;
    ifstream inFile;
    inFile.open("bank.dat", ios::binary);
    if(!inFile){
        cout << "File not found!!\n";
        return;
        }
        cout << "\n\n\t\tAccount Holders : \n\n";
        cout << "----------------------------------------------------------------------------------------------------------------\n";
        cout << "ID      A/c No.        Name            Address          Type       Balance\n";
        cout << "----------------------------------------------------------------------------------------------------------------\n";

        while(inFile.read(reinterpret_cast<char *>(&acc), sizeof(bank))){
            acc.report();
        }
        inFile.close();
}

/////////////////Function to deposit and Withdraw//////////////////////////////

void DepositWithdraw(int n,int which){
    bool search = false;
    bank acc;
    fstream File;
    File.open("bank.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout << "File not found!!\n";
        return;
    }
    while(!File.eof() && search==false){
        File.read(reinterpret_cast<char *>(&acc), sizeof(bank));
        if(acc.ReturnAccnum() == n){
            acc.displayAccount();
            if (which == 1){
                acc.depositMoney();
            }
            else if(which == 2){
                acc.withdrawMoney();
            }
            int pos=(-1)*static_cast<int>(sizeof(acc));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(bank));
			cout<<"\n\n\t Record is Updated\n";
			which=true;
        }
    }
        File.close();
	if(which==false)
		cout<<"\n\n Account Not Found \n";
}

/////////////////////////////////function for first screen ////////////////////////////////////////////

void FirstScreen(){
    cout<<"\n\n"<<setw(30)<<"  BANK";
	cout<<"\n\n"<<setw(34)<<"MANAGEMENT";
	cout<<"\n\n"<<setw(32)<<"  SYSTEM";
	cout<<"\n\n\n\n"<<setw(25)<<"MADE BY : TheNisham\n\n\n\n";

	cin.get();
}

