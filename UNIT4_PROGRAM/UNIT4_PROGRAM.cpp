/*
 * Talha Arda Boz
 * 9/8/2025
 * UNIT4_PROGRAM
 * This program calculates hotel room booking costs with discounts.
 * It prompts the user for room cost, number of rooms, days booked,
 * and sales tax, then calculates total billing amount with applicable
 * discounts based on room quantity and booking duration.
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Cconstants for discount values and thresholds
    const double BASE_ROOM_COST = 100.00;
    const double DISCOUNT_10_ROOMS = 0.10;
    const double DISCOUNT_20_ROOMS = 0.20;
    const double DISCOUNT_30_ROOMS = 0.30;
    const double EXTRA_DAYS_DISCOUNT = 0.05;
    const int MIN_ROOMS_FOR_10_PERCENT = 10;
    const int MIN_ROOMS_FOR_20_PERCENT = 20;
    const int MIN_ROOMS_FOR_30_PERCENT = 30;
    const int MIN_DAYS_FOR_EXTRA_DISCOUNT = 3;

    // Declaring input variables
    double roomCost;
    int numRooms;
    int numDays;
    double salesTaxPercent;

    // Prompting user for input values
    cout << "Enter the cost of renting one room: $";
    cin >> roomCost;

    cout << "Enter the number of rooms booked: ";
    cin >> numRooms;

    cout << "Enter the number of days the rooms are booked: ";
    cin >> numDays;

    cout << "Enter the sales tax (as a percent): ";
    cin >> salesTaxPercent;

    // Determining room discount based on number of rooms booked
    double roomDiscountPercent = 0.0;
    if (numRooms >= MIN_ROOMS_FOR_30_PERCENT) {
        roomDiscountPercent = DISCOUNT_30_ROOMS;
    }
    else if (numRooms >= MIN_ROOMS_FOR_20_PERCENT) {
        roomDiscountPercent = DISCOUNT_20_ROOMS;
    }
    else if (numRooms >= MIN_ROOMS_FOR_10_PERCENT) {
        roomDiscountPercent = DISCOUNT_10_ROOMS;
    }

    // Checking if extra days discount applies
    double extraDaysDiscountPercent = 0.0;
    if (numDays >= MIN_DAYS_FOR_EXTRA_DISCOUNT) {
        extraDaysDiscountPercent = EXTRA_DAYS_DISCOUNT;
    }

    // Calculating total discount percentage
    double totalDiscountPercent = roomDiscountPercent + extraDaysDiscountPercent;

    // Calculating costs step by step
    double subtotalBeforeDiscount = roomCost * numRooms * numDays;
    double discountAmount = subtotalBeforeDiscount * totalDiscountPercent;
    double totalCostAfterDiscount = subtotalBeforeDiscount - discountAmount;
    double salesTaxAmount = totalCostAfterDiscount * (salesTaxPercent / 100.0);
    double totalBillingAmount = totalCostAfterDiscount + salesTaxAmount;

    // Outputting all results with proper formatting
    cout << "\n--- BOOKING SUMMARY ---\n";
    cout << fixed << setprecision(2);

    cout << "Cost of renting one room: $" << roomCost << "\n";
    cout << "Discount on each room: " << (totalDiscountPercent * 100) << "%\n";
    cout << "Number of rooms booked: " << numRooms << "\n";
    cout << "Number of days booked: " << numDays << "\n";
    cout << "Total cost of rooms (before discount): $" << subtotalBeforeDiscount << "\n";
    cout << "Total discount amount: $" << discountAmount << "\n";
    cout << "Total cost after discount: $" << totalCostAfterDiscount << "\n";
    cout << "Sales tax (" << salesTaxPercent << "%): $" << salesTaxAmount << "\n";
    cout << "Total billing amount: $" << totalBillingAmount << "\n";

    return 0;
}