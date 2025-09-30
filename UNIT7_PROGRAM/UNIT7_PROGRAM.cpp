/*
 * Talha Arda Boz
 * 9/30/2025
 * UNIT7_PROGRAM
 * This program calculates federal tax for individuals based on marital
 * status, income, and pension contributions. It uses a menu-driven interface
 * to provide tax calculation services for both single and married taxpayers.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Function to display the main menu
void displayMenu() {
    cout << "===== Federal Tax Calculator Menu =====" << endl;
    cout << "1. Enter User Information" << endl;
    cout << "2. Tax Calculation Summary for Married Couple" << endl;
    cout << "3. Tax Calculation Summary for Single Individual" << endl;
    cout << "4. End Program" << endl;
    cout << "Enter your choice: ";
}

// Function to get user data
void getData(string &maritalStatus, int &numChildren, double &grossSalary, double &pensionPercent) {
    cout << "Enter marital status (single/married): ";
    cin >> maritalStatus;

    if (maritalStatus == "married") {
        cout << "Enter number of children under 14: ";
        cin >> numChildren;
    } else {
        numChildren = 0;
    }

    cout << "Enter gross salary: ";
    cin >> grossSalary;

    cout << "Enter pension fund contribution percentage (0-6%): ";
    cin >> pensionPercent;
}

// Function to calculate tax amount
double taxAmount(string maritalStatus, int numChildren, double grossSalary, double pensionPercent) {
    // Calculate standard exemption
    double standardExemption;
    if (maritalStatus == "single") {
        standardExemption = 4000.0;
    } else {
        standardExemption = 7000.0;
    }

    // Calculate pension contribution
    double pensionContribution = grossSalary * (pensionPercent / 100.0);

    // Calculate personal exemption
    double personalExemption = 1500.0 * (maritalStatus == "married" ? 2 + numChildren : 1);

    // Calculate taxable income
    double taxableIncome = grossSalary - standardExemption - pensionContribution - personalExemption;

    // Ensure taxable income is not negative
    if (taxableIncome < 0) {
        taxableIncome = 0;
    }

    // Calculate tax based on income brackets
    double tax = 0.0;

    if (taxableIncome <= 15000) {
        tax = taxableIncome * 0.15;
    } else if (taxableIncome <= 40000) {
        tax = 2250.0 + (taxableIncome - 15000) * 0.25;
    } else {
        tax = 8460.0 + (taxableIncome - 40000) * 0.35;
    }

    return tax;
}

int main() {
    // Variables for user data
    string maritalStatus = "";
    int numChildren = 0;
    double grossSalary = 0.0;
    double pensionPercent = 0.0;
    bool dataEntered = false;

    int choice;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;
        cout << endl;

        // Process user choice
        if (choice == 1) {
            // Enter User Information
            getData(maritalStatus, numChildren, grossSalary, pensionPercent);
            dataEntered = true;
            cout << endl;

        } else if (choice == 2) {
            // Tax Calculation Summary for Married Couple
            if (!dataEntered) {
                cout << "Error: Please enter user information first (Option 1)." << endl << endl;
            } else if (maritalStatus != "married") {
                cout << "Error: You selected tax summary for married individuals, but marital status is 'single'." << endl << endl;
            } else {
                cout << "---- Tax Calculation Summary ----" << endl;
                cout << "Marital Status: " << maritalStatus << endl;
                cout << "Number of Children Under 14: " << numChildren << endl;
                cout << "Gross Salary: $" << fixed << setprecision(0) << grossSalary << endl;
                cout << "Pension Contribution: " << fixed << setprecision(0) << pensionPercent << "% ($"
                     << fixed << setprecision(0) << (grossSalary * pensionPercent / 100.0) << ")" << endl;
                cout << endl;
                cout << "Federal Tax Owed: $" << fixed << setprecision(0)
                     << taxAmount(maritalStatus, numChildren, grossSalary, pensionPercent) << endl;
                cout << endl;
            }

        } else if (choice == 3) {
            // Tax Calculation Summary for Single Individual
            if (!dataEntered) {
                cout << "Error: Please enter user information first (Option 1)." << endl << endl;
            } else if (maritalStatus != "single") {
                cout << "Error: You selected tax summary for single individuals, but marital status is 'married'." << endl << endl;
            } else {
                cout << "---- Tax Calculation Summary ----" << endl;
                cout << "Marital Status: " << maritalStatus << endl;
                cout << "Gross Salary: $" << fixed << setprecision(0) << grossSalary << endl;
                cout << "Pension Contribution: " << fixed << setprecision(0) << pensionPercent << "% ($"
                     << fixed << setprecision(0) << (grossSalary * pensionPercent / 100.0) << ")" << endl;
                cout << endl;
                cout << "Federal Tax Owed: $" << fixed << setprecision(0)
                     << taxAmount(maritalStatus, numChildren, grossSalary, pensionPercent) << endl;
                cout << endl;
            }

        } else if (choice == 4) {
            // End Program
            cout << "This program ended." << endl;

        } else {
            // Invalid choice
            cout << "Error: Invalid choice. Please select a valid option (1-4)." << endl << endl;
        }

    } while (choice != 4);

    return 0;
}