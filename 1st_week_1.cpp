#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;      
    string accountHolderName;  
    float balance;              
    string accountType;         

public:

    BankAccount(const string &number, const string &holderName, float initialBalance, const string &type) 
        : accountNumber(number), accountHolderName(holderName), balance(initialBalance), accountType(type) {}

    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    float getBalance() const { return balance; }
    string getAccountType() const { return accountType; }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Balance: $" << balance << endl;
        cout << "Account Type: " << accountType << endl;
    }
};


int main() {

    cout << "Welcome to the Bank Management System (Console-Based)" << endl;
    cout << "Project Initialization and Setup Completed for Week 1!" << endl;

  
    BankAccount account("123456789", "John Doe", 1000.0, "Savings");

    cout << "\nSample Bank Account Details:" << endl;
    account.displayAccountInfo();

    return 0;
}
