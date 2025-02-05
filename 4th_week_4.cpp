#include <bits/stdc++.h>

using namespace std;

class BankAccount
{
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
    string getAccountNumber() const
    {
        return accountNumber;
    }

    string getAccountHolderName() const
    {
        return accountHolderName;
    }

    float getBalance() const
    {
        return balance;
    }

    string getAccountType() const
    {
        return accountType;
    }

    // Setter methods
    void setAccountHolderName(const string &holderName)
    {
        accountHolderName = holderName;
    }

    void setBalance(float newBalance)
    {
        balance = newBalance;
    }

    void recordTransaction(float amount, const string &transactionType)
    {
        ofstream file("transactions.txt", ios::app);
        if (file)
        {
            file << accountNumber << "," << fixed << setprecision(2) << amount << "," << transactionType << endl;
            file.close();
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }

    void deposit(float amount)
    {
        balance += amount;
        recordTransaction(amount, "Deposit");
    }

    void withdraw(float amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            recordTransaction(amount, "Withdrawal");
        }
        else
        {
            cout << "Insufficient balance." << endl;
        }
    }

    void report() const
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Account Type: " << accountType << endl;
    }
};

vector<BankAccount> accounts;

void loadAccounts()
{
    ifstream file("accounts.txt");
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string number, holderName, type;
            float balance;
            getline(ss, number, ',');
            getline(ss, holderName, ',');
            ss >> balance;
            ss.ignore();
            getline(ss, type);
            BankAccount account(number, holderName, balance, type);
            accounts.push_back(account);
        }
        file.close();
        cout << "Accounts loaded successfully!" << endl;
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

void saveAccount(const BankAccount &account)
{
    ofstream file("accounts.txt", ios::app);
    if (file)
    {
        file << account.getAccountNumber() << "," << account.getAccountHolderName() << ","
             << fixed << setprecision(2) << account.getBalance() << "," << account.getAccountType() << endl;
        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

void createNewAccount()
{
    string number, holderName, type;
    float initialBalance;

    cout << "Enter Account Number: ";
    getline(cin, number);

    cout << "Enter Account Holder Name: ";
    getline(cin, holderName);

    cout << "Enter Account Type: ";
    getline(cin, type);

    cout << "Enter Initial Balance: $";
    cin >> initialBalance;
    cin.ignore();

    BankAccount account(number, holderName, initialBalance, type);
    accounts.push_back(account);
    saveAccount(account);
    cout << "Account created successfully!" << endl;
}

void updateExistingAccount(const string &accountNumber)
{
    auto it = find_if(accounts.begin(), accounts.end(), [&accountNumber](const BankAccount &account)
                      { return account.getAccountNumber() == accountNumber; });

    if (it != accounts.end())
    {
        string holderName;
        float balance;

        cout << "Enter New Account Holder Name: ";
        getline(cin, holderName);

        cout << "Enter New Account Balance: $";
        cin >> balance;
        cin.ignore();

        it->setAccountHolderName(holderName);
        it->setBalance(balance);

        ofstream file("accounts.txt");
        if (file)
        {
            for (const BankAccount &account : accounts)
            {
                file << account.getAccountNumber() << "," << account.getAccountHolderName() << ","
                     << fixed << setprecision(2) << account.getBalance() << "," << account.getAccountType() << endl;
            }
            file.close();
            cout << "Account updated successfully!" << endl;
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void checkAccountDetails(const string &accountNumber)
{
    auto it = find_if(accounts.begin(), accounts.end(), [&accountNumber](const BankAccount &account)
                      { return account.getAccountNumber() == accountNumber; });

    if (it != accounts.end())
    {
        it->report();
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void depositAmount(const string &accountNumber)
{
    auto it = find_if(accounts.begin(), accounts.end(), [&accountNumber](const BankAccount &account)
                      { return account.getAccountNumber() == accountNumber; });

    if (it != accounts.end())
    {
        float amount;
        cout << "Enter amount to deposit: $";
        cin >> amount;
        cin.ignore();
        it->deposit(amount);
        cout << "Amount deposited successfully!" << endl;
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void withdrawAmount(const string &accountNumber)
{
    auto it = find_if(accounts.begin(), accounts.end(), [&accountNumber](const BankAccount &account)
                      { return account.getAccountNumber() == accountNumber; });

    if (it != accounts.end())
    {
        float amount;
        cout << "Enter amount to withdraw: $";
        cin >> amount;
        cin.ignore();
        it->withdraw(amount);
        cout << "Amount withdrawn successfully!" << endl;
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void searchingAccount(const string &accountNumber)
{
    auto it = find_if(accounts.begin(), accounts.end(), [&accountNumber](const BankAccount &account)
                      { return account.getAccountNumber() == accountNumber; });

    if (it != accounts.end())
    {
        cout << "Account found!" << endl;
        it->report();
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void closeAccount(const string &accountNumber)
{
    auto it = find_if(accounts.begin(), accounts.end(), [&accountNumber](const BankAccount &account)
                      { return account.getAccountNumber() == accountNumber; });

    if (it != accounts.end())
    {
        accounts.erase(it);

        ofstream file("accounts.txt");
        if (file)
        {
            for (const BankAccount &account : accounts)
            {
                file << account.getAccountNumber() << "," << account.getAccountHolderName() << ","
                     << fixed << setprecision(2) << account.getBalance() << "," << account.getAccountType() << endl;
            }
            file.close();
            cout << "Account closed successfully!" << endl;
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

int main()
{
    loadAccounts();

    int choice;
    string accountNumber;

    while (true)
    {
        cout << "\n----- Bank Account Management System -----" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Update Existing Account" << endl;
        cout << "3. Check Account Details" << endl;
        cout << "4. Deposit Amount" << endl;
        cout << "5. Withdraw Amount" << endl;
        cout << "6. Search for an Account" << endl;
        cout << "7. Close an Account" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;
        case 2:
            cout << "Enter Account Number: ";
            getline(cin, accountNumber);
            updateExistingAccount(accountNumber);
            break;
        case 3:
            cout << "Enter Account Number: ";
            getline(cin, accountNumber);
            checkAccountDetails(accountNumber);
            break;
        case 4:
            cout << "Enter Account Number: ";
            getline(cin, accountNumber);
            depositAmount(accountNumber);
            break;
        case 5:
            cout << "Enter Account Number: ";
            getline(cin, accountNumber);
            withdrawAmount(accountNumber);
            break;
        case 6:
            cout << "Enter Account Number: ";
            getline(cin, accountNumber);
            searchingAccount(accountNumber);
            break;
        case 7:
            cout << "Enter Account Number: ";
            getline(cin, accountNumber);
            closeAccount(accountNumber);
            break;
        case 8:
            cout << "Thank you for using the Bank Account Management System!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}