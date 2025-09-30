/*
 * Author: Talha Arda Boz
 * Creation Date: September 1, 2025
 * Program Name: UNIT2_PROGRAM
 *
 * Program Functionality:
 * This program demonstrates fundamental C++ concepts including:
 * - Formatted output
 * - Variable declarations and arithmetic operations
 * - Circle area and circumference calculations with user input
 * - String handling and formatted text output
 * - Decimal number rounding functionality
*/

#include <iostream>
#include <string>
#include <cmath>     // For mathematical operations and rounding
using namespace std;

int main() {
    // FIRST PART: Display program header with decorative border
    cout << "************************************************" << endl;
    cout << "*  Programming Assignment 1                    *" << endl;
    cout << "*  Computer Programming I                      *" << endl;
    cout << "*          Author: Talha Arda Boz              *" << endl;
    cout << "*  Due Date: Sunday, August 31, 2025           *" << endl;
    cout << "************************************************" << endl;
    cout << endl;

    // SECOND PART: C++
    cout << "PART 2: C++" << endl;
    cout << "CCCCCCCCCC        ++              ++" << endl;
    cout << "CC                ++              ++" << endl;
    cout << "CC          ++++++++++++++  ++++++++++++++" << endl;
    cout << "CC          ++++++++++++++  ++++++++++++++" << endl;
    cout << "CC                ++              ++" << endl;
    cout << "CCCCCCCCCC        ++              ++" << endl;
    cout << endl;

    // THIRD PART: Variable operations and calculations
    cout << "PART 3: Variable Operations" << endl;

    // Declare integer variables as specified
    int num1, num2, num3, average;

    // Assign values to variables
    num1 = 125;
    num2 = 28;
    num3 = -25;

    // Calculate average (using integer division as variables are int type)
    average = (num1 + num2 + num3) / 3;

    // Output the values
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "num3 = " << num3 << endl;
    cout << "average = " << average << endl;
    cout << endl;

    // FOURTH PART: Circle calculations with user input
    cout << "PART 4: Circle Area and Circumference Calculator" << endl;

    // Declare variables for circle calculations
    double radius;
    double area;
    double circumference;
    const double PI = 3.14;

    // Prompt user for radius input
    cout << "Enter the radius: ";
    cin >> radius;

    // Calculate area and circumference
    area = PI * radius * radius;
    circumference = 2 * PI * radius;

    // Output results
    cout << "Area = " << area << endl;
    cout << "Circumference = " << circumference << endl;
    cout << endl;

    // FIFTH PART: String handling and decimal rounding
    cout << "PART 5: Personal Information and Number Rounding" << endl;

    // Declare variables for name and study hours
    string name;
    double studyHours;

    // Clear input buffer before reading string
    cin.ignore();

    // Prompt and input values
    cout << "Enter your first name: ";
    getline(cin, name);
    cout << "Enter study hours for Saturday: ";
    cin >> studyHours;

    // Output formatted message
    cout << "Hello, " << name << "! On Saturday you need to study "
         << studyHours << " hours for the exam." << endl;
    cout << endl;

    // Decimal rounding segment
    cout << "Number Rounding Feature:" << endl;
    double decimalNumber;

    cout << "Enter a decimal number to round: ";
    cin >> decimalNumber;

    // Round to nearest integer using round() function
    int roundedValue = round(decimalNumber);

    cout << "Original number: " << decimalNumber << endl;
    cout << "Rounded to nearest integer: " << roundedValue << endl;

    return 0;
}