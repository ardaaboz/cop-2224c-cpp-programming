/*
 * Talha Arda Boz
 * 9/25/2025
 * UNIT6_PROGRAM
 * This program calculates billing amounts for J&J accounting firm's
 * tax consultation services. It uses different pricing structures based
 * on client income level and consultation time, with a function to
 * compute the final billing amount.
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Function to calculate billing amount
double calculateBilling(double hourlyRate, int totalMinutes, bool hasLowIncome) {
    double billingAmount = 0.0;

    if (hasLowIncome) {
        // Low income clients (<=25,000)
        if (totalMinutes <= 30) {
            billingAmount = 0.0;  // No charge for 30 minutes or less
        } else {
            // 40% of regular rate for time over 30 minutes
            int chargeableMinutes = totalMinutes - 30;
            billingAmount = hourlyRate * 0.40 * (chargeableMinutes / 60.0);
        }
    } else {
        // Regular income clients (>25,000)
        if (totalMinutes <= 20) {
            billingAmount = 0.0;  // No charge for 20 minutes or less
        } else {
            // 70% of regular rate for time over 20 minutes
            int chargeableMinutes = totalMinutes - 20;
            billingAmount = hourlyRate * 0.70 * (chargeableMinutes / 60.0);
        }
    }

    return billingAmount;
}

int main() {
    // Input variables
    double hourlyRate;
    int totalMinutes;
    char incomeResponse;
    bool hasLowIncome;
    double billingAmount;

    // Get user input
    cout << "Enter the hourly rate: $";
    cin >> hourlyRate;

    cout << "Enter the total consulting time (in minutes): ";
    cin >> totalMinutes;

    cout << "Does the person have low income (<=25,000)? (y/n): ";
    cin >> incomeResponse;

    // Convert response to boolean
    hasLowIncome = (incomeResponse == 'y' || incomeResponse == 'Y');

    // Calculate billing using the function
    billingAmount = calculateBilling(hourlyRate, totalMinutes, hasLowIncome);

    // Display result
    cout << "\nTotal Billing Amount: $" << fixed << setprecision(2) << billingAmount << endl;

    return 0;
}5