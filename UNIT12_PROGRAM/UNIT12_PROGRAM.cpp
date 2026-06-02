/*
 * Talha Arda Boz
 * 11/11/2025
 * UNIT12_PROGRAM - Dynamic Bank Account System
 * This program demonstrates mastery of pointers, dynamic memory, and inheritance in C++
 * by implementing a menu-driven banking system that manages both checking and savings
 * accounts using dynamic memory allocation. The program showcases proper use of new/delete
 * operators, specialized account types derived from a base class, and features including
 * deposits, withdrawals, interest posting, service charges, and persistent file storage.
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
    string ownerName;
    double balance;

public:
    // Constructors
    bankAccount() : accountNumber(0), ownerName(""), balance(0.0) {}

    bankAccount(int accNum, string owner, double bal)
        : accountNumber(accNum), ownerName(owner), balance(bal) {}

    // Setters
    void setAccountNumber(int accNum) {
        accountNumber = accNum;
    }

    void setOwnerName(string owner) {
        ownerName = owner;
    }

    // Getters
    int getAccountNumber() const {
        return accountNumber;
    }

    string getOwnerName() const {
        return ownerName;
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
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner: " << ownerName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Virtual saveToFile method (to be overridden)
    virtual void saveToFile(ofstream &outFile) const {
        outFile << "Account Number: " << accountNumber << endl;
        outFile << "Owner: " << ownerName << endl;
        outFile << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Virtual destructor
    virtual ~bankAccount() {}
};

// ========== DERIVED CLASS: checkingAccount ==========

class checkingAccount : public bankAccount {
private:
    double minimumBalance;
    double serviceCharge;
    int checksAllowed;
    int checksWritten;

public:
    // Constructors
    checkingAccount() : bankAccount(), minimumBalance(0.0), serviceCharge(0.0),
                        checksAllowed(0), checksWritten(0) {}

    checkingAccount(int accNum, string owner, double bal, double minBal,
                   double servCharge, int checksAllowed)
        : bankAccount(accNum, owner, bal), minimumBalance(minBal),
          serviceCharge(servCharge), checksAllowed(checksAllowed), checksWritten(0) {}

    // Setters
    void setMinimumBalance(double minBal) {
        minimumBalance = minBal;
    }

    void setServiceCharge(double charge) {
        serviceCharge = charge;
    }

    void setChecksAllowed(int allowed) {
        checksAllowed = allowed;
    }

    // Getters
    double getMinimumBalance() const {
        return minimumBalance;
    }

    double getServiceCharge() const {
        return serviceCharge;
    }

    int getChecksAllowed() const {
        return checksAllowed;
    }

    int getChecksWritten() const {
        return checksWritten;
    }

    // Verify if balance is below minimum
    bool isBelowMinimum() const {
        return balance < minimumBalance;
    }

    // Write a check (withdraw with service charge check)
    void writeCheck(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            checksWritten++;

            // Check if balance fell below minimum after withdrawal
            if (isBelowMinimum()) {
                balance -= serviceCharge;
                cout << "Balance below minimum. Applying service charge of $"
                     << fixed << setprecision(2) << serviceCharge << "." << endl;
            }
        }
    }

    // Override withdraw method
    void withdraw(double amount) override {
        writeCheck(amount);
    }

    // Override print method
    void printAccountInfo() const override {
        cout << "--- Checking Account Info ---" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner: " << ownerName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Minimum Balance: $" << fixed << setprecision(2) << minimumBalance << endl;
        cout << "Service Charge: $" << fixed << setprecision(2) << serviceCharge << endl;
        cout << "Checks Allowed: " << checksAllowed << endl;
        cout << "Checks Written: " << checksWritten << endl;
    }

    // Override saveToFile method
    void saveToFile(ofstream &outFile) const override {
        outFile << "--- Checking Account Info ---" << endl;
        outFile << "Account Number: " << accountNumber << endl;
        outFile << "Owner: " << ownerName << endl;
        outFile << "Balance: $" << fixed << setprecision(2) << balance << endl;
        outFile << "Minimum Balance: $" << fixed << setprecision(2) << minimumBalance << endl;
        outFile << "Service Charge: $" << fixed << setprecision(2) << serviceCharge << endl;
        outFile << "Checks Allowed: " << checksAllowed << endl;
        outFile << "Checks Written: " << checksWritten << endl;
    }
};

// ========== DERIVED CLASS: savingsAccount ==========

class savingsAccount : public bankAccount {
private:
    double interestRate;

public:
    // Constructors
    savingsAccount() : bankAccount(), interestRate(0.0) {}

    savingsAccount(int accNum, string owner, double bal, double intRate)
        : bankAccount(accNum, owner, bal), interestRate(intRate) {}

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
        cout << "--- Savings Account Info ---" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner: " << ownerName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%" << endl;
    }

    // Override saveToFile method
    void saveToFile(ofstream &outFile) const override {
        outFile << endl << "--- Savings Account Info ---" << endl;
        outFile << "Account Number: " << accountNumber << endl;
        outFile << "Owner: " << ownerName << endl;
        outFile << "Balance: $" << fixed << setprecision(2) << balance << endl;
        outFile << "Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%" << endl;
    }
};

// ========== FUNCTION PROTOTYPES ==========

void displayMenu();
double getValidatedAmount(const string &prompt);

// ========== MAIN FUNCTION ==========

int main() {
    // Dynamically allocate checking account using pointers
    // Account 1001, John Doe, $500.00, $300 minimum, $25 service charge, 5 checks allowed
    checkingAccount* checkAccPtr = new checkingAccount(1001, "John Doe", 500.00, 300.00, 25.00, 5);

    // Dynamically allocate savings account using pointers
    // Account 2001, Jane Smith, $1000.00, 3% interest
    savingsAccount* saveAccPtr = new savingsAccount(2001, "Jane Smith", 1000.00, 0.03);

    int choice;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                // View Checking Account Info
                checkAccPtr->printAccountInfo();
                break;
            }

            case 2: {
                // Deposit to Checking Account
                double amount = getValidatedAmount("Enter deposit amount: $");
                checkAccPtr->deposit(amount);
                cout << "Deposit successful. New balance: $" << fixed << setprecision(2)
                     << checkAccPtr->getBalance() << endl;
                break;
            }

            case 3: {
                // Write Check / Withdraw from Checking Account
                double amount = getValidatedAmount("Enter withdrawal amount: $");

                if (amount > checkAccPtr->getBalance()) {
                    cout << "Error: Insufficient funds." << endl;
                } else {
                    checkAccPtr->withdraw(amount);
                    cout << "New balance: $" << fixed << setprecision(2)
                         << checkAccPtr->getBalance() << endl;
                }
                break;
            }

            case 4: {
                // View Savings Account Info
                saveAccPtr->printAccountInfo();
                break;
            }

            case 5: {
                // Deposit to Savings Account
                double amount = getValidatedAmount("Enter deposit amount: $");
                saveAccPtr->deposit(amount);
                cout << "Deposit successful. New balance: $" << fixed << setprecision(2)
                     << saveAccPtr->getBalance() << endl;
                break;
            }

            case 6: {
                // Withdraw from Savings Account
                double amount = getValidatedAmount("Enter withdrawal amount: $");

                if (amount > saveAccPtr->getBalance()) {
                    cout << "Error: Insufficient funds." << endl;
                } else {
                    saveAccPtr->withdraw(amount);
                    cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2)
                         << saveAccPtr->getBalance() << endl;
                }
                break;
            }

            case 7: {
                // Post Interest to Savings Account
                saveAccPtr->postInterest();
                cout << "Interest posted. New balance: $" << fixed << setprecision(2)
                     << saveAccPtr->getBalance() << endl;
                break;
            }

            case 8: {
                // Save Account Summary and Exit
                ofstream outFile("AccountSummary.txt");

                if (!outFile) {
                    cout << "Error: Could not create output file." << endl;
                } else {
                    checkAccPtr->saveToFile(outFile);
                    saveAccPtr->saveToFile(outFile);
                    outFile.close();
                    cout << "Account summaries successfully saved to 'AccountSummary.txt'." << endl;
                    cout << "Exiting program. Goodbye!" << endl;
                }
                break;
            }

            default: {
                cout << "Error: Invalid choice. Please select a valid option (1-8)." << endl;
                break;
            }
        }

        if (choice != 8) {
            cout << endl;
        }

    } while (choice != 8);

    // Clean up dynamically allocated memory
    delete checkAccPtr;
    delete saveAccPtr;

    return 0;
}

// ========== FUNCTION DEFINITIONS ==========

// Function to display the main menu
void displayMenu() {
    cout << "=============================================" << endl;
    cout << "       DYNAMIC BANK ACCOUNT SYSTEM" << endl;
    cout << "=============================================" << endl;
    cout << "1. View Checking Account Info" << endl;
    cout << "2. Deposit to Checking Account" << endl;
    cout << "3. Write Check / Withdraw from Checking Account" << endl;
    cout << "4. View Savings Account Info" << endl;
    cout << "5. Deposit to Savings Account" << endl;
    cout << "6. Withdraw from Savings Account" << endl;
    cout << "7. Post Interest to Savings Account" << endl;
    cout << "8. Save Account Summary and Exit" << endl;
    cout << "Enter your choice (1-8): ";
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