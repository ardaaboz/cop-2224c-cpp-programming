/*
 * Talha Arda Boz
 * 9/2/2025
 * UNIT3_PROGRAM
 * This program reads employee data from a file,
 * calculates their paycheck with bonus and taxes,
 * computes travel speed, determines coffee sales revenue
 * and outputs all results and information to another file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // Declaring file variables
    ifstream inFile;
    ofstream outFile;

    // Opening files to opearte on them
    inFile.open("inData.txt");
    outFile.open("outData.txt");

    // Checking if they are correctly opened
    if (!inFile.is_open()) {
        cerr << "Error: Could not open inData.txt" << endl;
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Error: Could not open outData.txt" << endl;
        return 1;
    }

    // Reading from file word by word and putting them
    // inside an array for later access
    string wordsArray[10];
    int i = 0;
    while (inFile >> wordsArray[i]) {
        i++;
    }
    // Closing file for memory management
    inFile.close();

    // Naming each array item to make code easier to read
    string firstName = wordsArray[0];
    string lastName = wordsArray[1];
    string department = wordsArray[2];

    double monthlySalary = stod(wordsArray[3]);
    double bonusPercent = stod(wordsArray[4]);
    double taxPercent = stod(wordsArray[5]);
    double distanceTravelled = stod(wordsArray[6]);
    double travellingTime = stod(wordsArray[7]);
    double coffeeCupsSold = stod(wordsArray[8]);
    double coffeeCost = stod(wordsArray[9]);


    // Printing out name and department
    outFile << "Name: " << firstName << " " << lastName
            << ", Department: " << department << "\n";

    // Printing out salary, bonus and taxes
    outFile << fixed << setprecision(2)
            << "Monthly Gross Salary: $" << monthlySalary
            << ", Monthly Bonus: " << bonusPercent
            << "%, Taxes: " << taxPercent << "%\n";

    // Calculating and printing paycheck
    double paycheck = (monthlySalary + (monthlySalary * bonusPercent / 100)) * (1 - taxPercent / 100);
    outFile << fixed << setprecision(2)
            << "Paycheck: "<< paycheck << "\n\n";

    // Printing distance and travel time
    outFile << fixed << setprecision(2)
            << "Distance Travelled: " << distanceTravelled
            << " Travelling Time: " << travellingTime << "\n";

    // Calculating and printing average speed
    double avgSpeed = distanceTravelled / travellingTime;
    outFile << fixed << setprecision(2)
            << "Average Speed: " << avgSpeed << " miles per hour" << "\n\n";

    // Printing out coffee cup information
    outFile << fixed << setprecision(0)
            << "Number of Coffee Cups Sold: " << coffeeCupsSold;

    outFile << fixed << setprecision(2)
            << ", Cost: $" << coffeeCost << "\n";

    // Calculating and printing out sales amount
    double salesAmount = coffeeCupsSold * coffeeCost;

    outFile << fixed << setprecision(2)
            << "Sales Amount = $" << salesAmount << "\n";

    // Closing file for memory management
    outFile.close();

    return 0;
}