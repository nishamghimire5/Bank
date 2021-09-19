#include <string>
class bank
{
    char name[40],address[40],type[10];
    int balance,id;
    std::string acc_num;
    static int totalCustomers;

public:
    //functions available
        void openAccount(); //open a new account
        void depositMoney(); //put money or add money
        void modify(); // to add new datas
        void withdrawMoney(); //take money out or subtract
        void displayAccount(); //show account details
        void report() const; //to show data in tabular form
        void minusTotal(){totalCustomers--;}
        int ReturnAccnum() const { return id; }
        int ReturnBalance(int acc_num) const{ return balance; }
};

int bank::totalCustomers;