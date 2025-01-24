#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
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

    // Deposit money into the account
    void deposit(float amount) {
        balance += amount;
        cout << "Deposit successful! Updated Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Withdraw money from the account
    void withdraw(float amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal successful! Updated Balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Insufficient balance. Withdrawal failed." << endl;
        }
    }

    // Display account details
    void displayAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Account Type: " << accountType << endl;
    }
};

// Global variables
vector<BankAccount> accounts;

// Function to load accounts from file
void loadAccountsFromFile() {
    ifstream file("accounts.txt");
    if (file) {
        string number, holderName, type;
        float balance;

        while (file >> number >> holderName >> balance >> type) {
            BankAccount account(number, holderName, balance, type);
            accounts.push_back(account);
        }
        file.close();
        cout << "Accounts loaded from file successfully!" << endl;
    } else {
        cout << "No existing account data found. Starting fresh." << endl;
    }
}

// Function to save accounts to file
void saveAccountsToFile() {
    ofstream file("accounts.txt");
    if (file) {
        for (const auto &account : accounts) {
            file << account.getAccountNumber() << " "
                 << account.getAccountHolderName() << " "
                 << account.getBalance() << " "
                 << account.getAccountType() << endl;
        }
        file.close();
        cout << "Accounts saved to file successfully!" << endl;
    } else {
        cout << "Error saving account data to file." << endl;
    }
}

// Function to create a new account
void createAccount() {
    string number, holderName, type;
    float initialBalance;

    cout << "Enter Account Number: ";
    cin >> number;
    cin.ignore();

    cout << "Enter Account Holder Name: ";
    getline(cin, holderName);

    cout << "Enter Account Type (Savings/Current): ";
    cin >> type;

    cout << "Enter Initial Balance: $";
    cin >> initialBalance;

    // Create and add the new account
    BankAccount newAccount(number, holderName, initialBalance, type);
    accounts.push_back(newAccount);

    saveAccountsToFile(); // Save updated data to file
    cout << "Account created successfully!" << endl;
}

// Function to modify an existing account
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

            account.setAccountHolderName(holderName);
            account.setBalance(newBalance);

            saveAccountsToFile(); // Save updated data to file
            cout << "Account modified successfully!" << endl;
            return;
        }
    }

    cout << "Account not found!" << endl;
}

// Function to perform deposit
void depositAmount() {
    string accountNumber;
    float amount;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    for (auto &account : accounts) {
        if (account.getAccountNumber() == accountNumber) {
            cout << "Enter amount to deposit: $";
            cin >> amount;
            account.deposit(amount);
            saveAccountsToFile(); // Save updated data to file
            return;
        }
    }
    cout << "Account not found!" << endl;
}

// Function to perform withdrawal
void withdrawAmount() {
    string accountNumber;
    float amount;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    for (auto &account : accounts) {
        if (account.getAccountNumber() == accountNumber) {
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            account.withdraw(amount);
            saveAccountsToFile(); // Save updated data to file
            return;
        }
    }
    cout << "Account not found!" << endl;
}

// Function to display all accounts
void displayAllAccounts() {
    if (accounts.empty()) {
        cout << "No accounts available." << endl;
        return;
    }

    for (const auto &account : accounts) {
        account.displayAccountInfo();
    }
}

// Main function
int main() {
    loadAccountsFromFile(); // Load accounts from file at startup

    int choice;

    while (true) {
        cout << "\n--- Bank Management System ---" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Modify Existing Account" << endl;
        cout << "3. Display All Accounts" << endl;
        cout << "4. Deposit Amount" << endl;
        cout << "5. Withdraw Amount" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                modifyAccount();
                break;
            case 3:
                displayAllAccounts();
                break;
            case 4:
                depositAmount();
                break;
            case 5:
                withdrawAmount();
                break;
            case 6:
                cout << "Exiting the system. Goodbye!" << endl;
                saveAccountsToFile(); // Save accounts to file before exiting
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
