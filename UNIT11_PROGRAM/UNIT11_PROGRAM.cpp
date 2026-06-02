/*
 * Talha Arda Boz
 * 11/3/2025
 * UNIT11_PROGRAM - Banking System with Inheritance
 * This program demonstrates mastery of inheritance and composition1 by implementing
 * a menu-driven banking system that manages both checking and savings accounts.
 * The program showcases specialized account types derived from a base class, with
 * features including interest posting, service charges, minimum balance enforcement,
 * and persistent file storage.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// ========== BASE CLASS: bankAccount ==========

class bankAccount {
protected:
    int accountNumber;
    double balance;

public:
    // Constructors
    bankAccount() : accountNumber(0), balance(0.0) {}

    bankAccount(int accNum, double bal) : accountNumber(accNum), balance(bal) {}

    // Setters
    void setAccountNumber(int accNum) {
        accountNumber = accNum;
    }

    // Getters
    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Virtual withdraw method (to be overridden)
    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }

    // Virtual print method (to be overridden)
    virtual void printAccountInfo() const {
        cout << "Account Number: " << accountNumber << " Balance: $"
             << fixed << setprecision(2) << balance;
    }

    // Virtual saveToFile method (to be overridden)
    virtual void saveToFile(ofstream &outFile) const {
        outFile << "Account Number: " << accountNumber << " Balance: $"
                << fixed << setprecision(2) << balance;
    }

    // Virtual destructor
    virtual ~bankAccount() {}
};

// ========== DERIVED CLASS: checkingAccount ==========

class checkingAccount : public bankAccount {
private:
    double interestRate;
    double minimumBalance;
    double serviceCharge;

public:
    // Constructors
    checkingAccount() : bankAccount(), interestRate(0.0), minimumBalance(0.0), serviceCharge(0.0) {}

    checkingAccount(int accNum, double bal, double intRate, double minBal, double servCharge)
        : bankAccount(accNum, bal), interestRate(intRate), minimumBalance(minBal), serviceCharge(servCharge) {}

    // Setters
    void setInterestRate(double rate) {
        interestRate = rate;
    }

    void setMinimumBalance(double minBal) {
        minimumBalance = minBal;
    }

    void setServiceCharge(double charge) {
        serviceCharge = charge;
    }

    // Getters
    double getInterestRate() const {
        return interestRate;
    }

    double getMinimumBalance() const {
        return minimumBalance;
    }

    double getServiceCharge() const {
        return serviceCharge;
    }

    // Post interest
    void postInterest() {
        double interest = balance * interestRate;
        balance += interest;
    }

    // Verify if balance is below minimum
    bool isBelowMinimum() const {
        return balance < minimumBalance;
    }

    // Write a check (withdraw with service charge check)
    void writeCheck(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;

            // Check if balance fell below minimum after withdrawal
            if (isBelowMinimum()) {
                balance -= serviceCharge;
                cout << "Balance below minimum. Applying service charge of $"
                     << fixed << setprecision(2) << serviceCharge << ". ";
            }
        }
    }

    // Override withdraw method
    void withdraw(double amount) override {
        writeCheck(amount);
    }

    // Override print method
    void printAccountInfo() const override {
        cout << "--- Checking Account Info --- Account Number: " << accountNumber
             << " Balance: $" << fixed << setprecision(2) << balance
             << " Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%"
             << " Minimum Balance: $" << fixed << setprecision(2) << minimumBalance
             << " Service Charge: $" << fixed << setprecision(2) << serviceCharge << endl;
    }

    // Override saveToFile method
    void saveToFile(ofstream &outFile) const override {
        outFile << "--- Checking Account Info --- Account Number: " << accountNumber
                << " Balance: $" << fixed << setprecision(2) << balance
                << " Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%"
                << " Minimum Balance: $" << fixed << setprecision(2) << minimumBalance
                << " Service Charge: $" << fixed << setprecision(2) << serviceCharge << " ";
    }
};

// ========== DERIVED CLASS: savingsAccount ==========

class savingsAccount : public bankAccount {
private:
    double interestRate;

public:
    // Constructors
    savingsAccount() : bankAccount(), interestRate(0.0) {}

    savingsAccount(int accNum, double bal, double intRate)
        : bankAccount(accNum, bal), interestRate(intRate) {}

    // Setters
    void setInterestRate(double rate) {
        interestRate = rate;
    }

    // Getters
    double getInterestRate() const {
        return interestRate;
    }

    // Post interest
    void postInterest() {
        double interest = balance * interestRate;
        balance += interest;
    }

    // Override withdraw method (simple withdrawal)
    void withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }

    // Override print method
    void printAccountInfo() const override {
        cout << "--- Savings Account Info --- Account Number: " << accountNumber
             << " Balance: $" << fixed << setprecision(2) << balance
             << " Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%" << endl;
    }

    // Override saveToFile method
    void saveToFile(ofstream &outFile) const override {
        outFile << "--- Savings Account Info --- Account Number: " << accountNumber
                << " Balance: $" << fixed << setprecision(2) << balance
                << " Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%";
    }
};

// ========== FUNCTION PROTOTYPES ==========

void displayMenu();
double getValidatedAmount(const string &prompt);

// ========== MAIN FUNCTION ==========

int main() {
    // Initialize checking account: Account 1001, $500.00, 2% interest, $300 minimum, $25 service charge
    checkingAccount checkAcc(1001, 500.00, 0.02, 300.00, 25.00);

    // Initialize savings account: Account 2001, $1000.00, 3% interest
    savingsAccount saveAcc(2001, 1000.00, 0.03);

    int choice;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                // View Checking Account Info
                checkAcc.printAccountInfo();
                break;
            }

            case 2: {
                // Deposit to Checking Account
                double amount = getValidatedAmount("Enter deposit amount: $");
                checkAcc.deposit(amount);
                cout << "Deposit successful. New balance: $" << fixed << setprecision(2)
                     << checkAcc.getBalance() << endl;
                break;
            }

            case 3: {
                // Write Check / Withdraw from Checking Account
                double amount = getValidatedAmount("Enter withdrawal amount: $");

                if (amount > checkAcc.getBalance()) {
                    cout << "Error: Insufficient funds." << endl;
                } else {
                    checkAcc.withdraw(amount);
                    cout << "New balance: $" << fixed << setprecision(2)
                         << checkAcc.getBalance() << endl;
                }
                break;
            }

            case 4: {
                // Post Interest to Checking Account
                checkAcc.postInterest();
                cout << "Interest posted. New balance: $" << fixed << setprecision(2)
                     << checkAcc.getBalance() << endl;
                break;
            }

            case 5: {
                // View Savings Account Info
                saveAcc.printAccountInfo();
                break;
            }

            case 6: {
                // Deposit to Savings Account
                double amount = getValidatedAmount("Enter deposit amount: $");
                saveAcc.deposit(amount);
                cout << "Deposit successful. New balance: $" << fixed << setprecision(2)
                     << saveAcc.getBalance() << endl;
                break;
            }

            case 7: {
                // Withdraw from Savings Account
                double amount = getValidatedAmount("Enter withdrawal amount: $");

                if (amount > saveAcc.getBalance()) {
                    cout << "Error: Insufficient funds." << endl;
                } else {
                    saveAcc.withdraw(amount);
                    cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2)
                         << saveAcc.getBalance() << endl;
                }
                break;
            }

            case 8: {
                // Post Interest to Savings Account
                saveAcc.postInterest();
                cout << "Interest posted. New balance: $" << fixed << setprecision(2)
                     << saveAcc.getBalance() << endl;
                break;
            }

            case 9: {
                // Exit and Save Account Summary
                ofstream outFile("AccountSummary.txt");

                if (!outFile) {
                    cout << "Error: Could not create output file." << endl;
                } else {
                    checkAcc.saveToFile(outFile);
                    saveAcc.saveToFile(outFile);
                    outFile.close();
                    cout << "Account summary successfully saved into the data file named 'AccountSummary.txt'. Exiting program. Goodbye!" << endl;
                }
                break;
            }

            default: {
                cout << "Error: Invalid choice. Please select a valid option (1-9)." << endl;
                break;
            }
        }

        if (choice != 9) {
            cout << endl;
        }

    } while (choice != 9);

    return 0;
}

// ========== FUNCTION DEFINITIONS ==========

// Function to display the main menu
void displayMenu() {
    cout << "===== Banking System Menu =====" << endl;
    cout << "1. View Checking Account Info" << endl;
    cout << "2. Deposit to Checking Account" << endl;
    cout << "3. Write Check / Withdraw from Checking Account" << endl;
    cout << "4. Post Interest to Checking Account" << endl;
    cout << "5. View Savings Account Info" << endl;
    cout << "6. Deposit to Savings Account" << endl;
    cout << "7. Withdraw from Savings Account" << endl;
    cout << "8. Post Interest to Savings Account" << endl;
    cout << "9. Exit and Save Account Summary" << endl;
    cout << "Enter your choice: ";
}

// Function to get and validate monetary amount
double getValidatedAmount(const string &prompt) {
    double amount;

    cout << prompt;
    cin >> amount;

    // Input validation
    while (amount < 0) {
        cout << "Error: Amount cannot be negative. Please enter a valid amount: $";
        cin >> amount;
    }

    return amount;
}