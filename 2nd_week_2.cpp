#include <iostream>
#include <vector>
#include <string>
using namespace std;

// BankAccount Class
class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    float balance;
    string accountType;

public:
    // Constructor
    BankAccount(const string &number, const string &holderName, float initialBalance, const string &type)
        : accountNumber(number), accountHolderName(holderName), balance(initialBalance), accountType(type) {}

    // Getter methods
    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    float getBalance() const { return balance; }
    string getAccountType() const { return accountType; }

    // Setter methods
    void setAccountHolderName(const string &holderName) { accountHolderName = holderName; }
    void setBalance(float newBalance) { balance = newBalance; }

    // Display Account Information
    void displayAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Balance: $" << balance << endl;
        cout << "Account Type: " << accountType << endl;
    }
};

// Global Vector to Store Bank Accounts
vector<BankAccount> accounts;

// Function to Create a New Account
void createAccount() {
    string number, holderName, type;
    float initialBalance;

    cout << "Enter Account Number: ";
    cin >> number;
    cin.ignore();

    cout << "Enter Account Holder Name: ";
    getline(cin, holderName);

    cout << "Enter Account Type (e.g., Savings, Current): ";
    getline(cin, type);

    cout << "Enter Initial Balance: $";
    cin >> initialBalance;

    // Create and Add the New Account
    BankAccount newAccount(number, holderName, initialBalance, type);
    accounts.push_back(newAccount);

    cout << "\nAccount Created Successfully!\n";
}

// Function to Display All Accounts
void displayAllAccounts() {
    if (accounts.empty()) {
        cout << "\nNo accounts available.\n";
        return;
    }

    cout << "\n--- All Bank Accounts ---\n";
    for (const auto &account : accounts) {
        account.displayAccountInfo();
    }
}

// Function to Modify an Existing Account
void modifyAccount() {
    string number;
    cout << "Enter Account Number to Modify: ";
    cin >> number;
    cin.ignore();

    for (auto &account : accounts) {
        if (account.getAccountNumber() == number) {
            string holderName;
            float newBalance;

            cout << "Enter New Account Holder Name: ";
            getline(cin, holderName);

            cout << "Enter New Account Balance: $";
            cin >> newBalance;

            // Update Account Details
            account.setAccountHolderName(holderName);
            account.setBalance(newBalance);

            cout << "\nAccount Updated Successfully!\n";
            return;
        }
    }

    cout << "\nAccount Not Found!\n";
}

// Main Function
int main() {
    int choice;

    while (true) {
        cout << "\n--- Bank Management System ---" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Modify Account" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                displayAllAccounts();
                break;
            case 3:
                modifyAccount();
                break;
            case 4:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
