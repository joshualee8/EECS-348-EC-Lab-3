#include <iostream>
#include <string>
using namespace std;

// Base class for bank accounts
class Account {
protected:
    string accountNumber; // Unique identifier for the account
    string accountHolder; // Name of the account holder
    double balance;       // Current balance of the account

public:
    // Constructor to initialize an Account object
    Account(string accountNumber, string accountHolder, double balance)
        : accountNumber(accountNumber), accountHolder(accountHolder), balance(balance) {}

    // Method to deposit an amount into the account
    void deposit(double amount) {
        balance += amount; // Add the amount to the current balance
    }

    // Virtual method to withdraw an amount from the account
    virtual void withdraw(double amount) {
        if (balance >= amount) { // Check for sufficient balance
            balance -= amount;   // Subtract the amount from the balance
        } else {
            cout << "Insufficient balance." << endl; // Display error if balance is insufficient
        }
    }

    // Friend function to overload the << operator for Account class
    friend ostream& operator<<(ostream& os, const Account& account);
};

// Implementation of << operator overloading
ostream& operator<<(ostream& os, const Account& account) {
    // Output account details
    os << "Account Details for " << account.accountNumber << ":\n";
    os << "   Holder: " << account.accountHolder << "\n";
    os << "   Balance: $" << account.balance << "\n";
    return os;
}

// Derived class for Savings Account
class SavingsAccount : public Account {
private:
    double interestRate; // Interest rate for the savings account

public:
    // Constructor to initialize a SavingsAccount object
    SavingsAccount(string accountNumber, string accountHolder, double balance, double interestRate)
        : Account(accountNumber, accountHolder, balance), interestRate(interestRate) {}

    // Overridden withdraw method for SavingsAccount
    void withdraw(double amount) override {
        const double minimumBalance = 500; // Minimum balance requirement
        if (balance - amount >= minimumBalance) { // Check for minimum balance
            Account::withdraw(amount);             // Perform withdrawal
        } else {
            cout << "Insufficient balance (minimum balance requirement)." << endl; // Display error if minimum balance is not maintained
        }
    }

    // Overloading << operator for SavingsAccount class
    friend ostream& operator<<(ostream& os, const SavingsAccount& account);
};

// Implementation of << operator overloading for SavingsAccount
ostream& operator<<(ostream& os, const SavingsAccount& account) {
    // Output account details specific to SavingsAccount
    os << (const Account&)account; // Cast to base class to use base class operator
    os << "   Interest Rate: " << account.interestRate * 100 << "%\n"; // Show interest rate
    return os;
}

// Derived class for Current Account
class CurrentAccount : public Account {
private:
    double overdraftLimit; // Limit for overdraft

public:
    // Constructor to initialize a CurrentAccount object
    CurrentAccount(string accountNumber, string accountHolder, double balance, double overdraftLimit)
        : Account(accountNumber, accountHolder, balance), overdraftLimit(overdraftLimit) {}

    // Overridden withdraw method for CurrentAccount
    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) { // Check if amount is within overdraft limit
            balance -= amount;                    // Perform withdrawal
        } else {
            cout << "Overdraft limit exceeded." << endl; // Display error if overdraft limit is exceeded
        }
    }

    // Overloading + operator to transfer money between accounts
    CurrentAccount& operator+(const SavingsAccount& savings) {
        this->balance += savings.balance; // Add the balance of SavingsAccount to CurrentAccount
        return *this;                     // Return the updated CurrentAccount object
    }

    // Overloading << operator for CurrentAccount class
    friend ostream& operator<<(ostream& os, const CurrentAccount& account);
};

// Implementation of << operator overloading for CurrentAccount
ostream& operator<<(ostream& os, const CurrentAccount& account) {
    // Output account details specific to CurrentAccount
    os << (const Account&)account; // Cast to base class to use base class operator
    os << "   Overdraft Limit: $" << account.overdraftLimit << "\n"; // Show overdraft limit
    return os;
}

// Main function
int main() {
    // Create instances of SavingsAccount and CurrentAccount
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    // Display initial details of both accounts
    cout << savings;
    cout << current;

    // Perform deposit and withdrawal operations
    savings.deposit(500);   // Deposit $500 to savings account
    current.withdraw(1000); // Withdraw $1000 from current account

    // Display account details after deposit and withdrawal
    cout << "\nAccount Details after deposit and withdrawal:\n";
    cout << savings;
    cout << current;

    // Transfer money from savings to current account using overloaded + operator
    current = current + savings;

    // Display account details after transfer
    cout << "\nAccount Details after transfer:\n";
    cout << savings;
    cout << current;

    return 0;
}
