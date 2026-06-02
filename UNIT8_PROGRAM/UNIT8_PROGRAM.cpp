/*
 * Talha Arda Boz
 * 10/7/2025
 * UNIT8_PROGRAM
 * This program demonstrates mastery of arrays by implementing a menu-driven
 * application with three distinct features: a vote summary system using
 * one-dimensional arrays, a score classification tool that processes data
 * from a file using one-dimensional arrays, and a climate data analyzer
 * using two-dimensional arrays.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Constants
const int MAX_CANDIDATES = 5;
const int NUM_MONTHS = 12;
const int NUM_TEMP_TYPES = 2; // High and Low temperatures
const int NUM_SCORE_RANGES = 8;

// Function prototypes for menu and main control
void displayMenu();

// Option 1: Election Summary Report functions
void electionSummaryReport();
void getElectionData(string candidates[], int votes[], int &numCandidates);
void displayElectionResults(string candidates[], int votes[], int numCandidates);
int calculateTotalVotes(int votes[], int numCandidates);
int findWinnerIndex(int votes[], int numCandidates);

// Option 2: Student Score Distribution functions
void studentScoreDistribution();
void processScoreFile(int scoreRanges[]);
void displayScoreDistribution(int scoreRanges[]);
int determineScoreRange(int score);

// Option 3: Annual Temperature Tracker functions
void annualTempTracker();
void getData(double temperatures[][NUM_TEMP_TYPES]);
double averageHigh(double temperatures[][NUM_TEMP_TYPES]);
double averageLow(double temperatures[][NUM_TEMP_TYPES]);
int indexHighTemp(double temperatures[][NUM_TEMP_TYPES]);
int indexLowTemp(double temperatures[][NUM_TEMP_TYPES]);
void displayTempResults(double temperatures[][NUM_TEMP_TYPES]);
string getMonthName(int monthIndex);

// Main function
int main() {
    int choice;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;
        cout << endl;

        // Process user choice
        if (choice == 1) {
            electionSummaryReport();
        } else if (choice == 2) {
            studentScoreDistribution();
        } else if (choice == 3) {
            annualTempTracker();
        } else if (choice == 4) {
            cout << "Thank you for using this program." << endl;
        } else {
            cout << "Error: Invalid choice. Please select a valid option (1-4)." << endl << endl;
        }

    } while (choice != 4);

    return 0;
}

// Function to display the main menu
void displayMenu() {
    cout << "------ Main Menu ------" << endl;
    cout << "1. ElectionSummaryReport" << endl;
    cout << "2. StudentScoreDistribution" << endl;
    cout << "3. AnnualTempTracker" << endl;
    cout << "4. End the program" << endl;
    cout << "Enter your choice: ";
}

// ========== OPTION 1: ELECTION SUMMARY REPORT ==========

void electionSummaryReport() {
    string candidates[MAX_CANDIDATES];
    int votes[MAX_CANDIDATES];
    int numCandidates = MAX_CANDIDATES;

    // Get election data from user
    getElectionData(candidates, votes, numCandidates);

    // Display formatted results
    displayElectionResults(candidates, votes, numCandidates);

    cout << endl;
}

void getElectionData(string candidates[], int votes[], int &numCandidates) {
    cout << "Enter data for " << numCandidates << " candidates:" << endl;

    for (int i = 0; i < numCandidates; i++) {
        cout << "Candidate " << (i + 1) << " last name: ";
        cin >> candidates[i];

        cout << "Votes received: ";
        cin >> votes[i];
    }

    cout << endl;
}

void displayElectionResults(string candidates[], int votes[], int numCandidates) {
    int totalVotes = calculateTotalVotes(votes, numCandidates);
    int winnerIndex = findWinnerIndex(votes, numCandidates);

    // Display header
    cout << left << setw(15) << "Candidate"
         << right << setw(15) << "Votes Received"
         << setw(18) << "% of Total Votes" << endl;

    // Display each candidate's results
    for (int i = 0; i < numCandidates; i++) {
        double percentage = (static_cast<double>(votes[i]) / totalVotes) * 100.0;

        cout << left << setw(15) << candidates[i]
             << right << setw(15) << votes[i]
             << setw(18) << fixed << setprecision(2) << percentage << endl;
    }

    // Display total
    cout << left << setw(15) << "Total"
         << right << setw(15) << totalVotes << endl;

    // Display winner
    cout << endl << "The Winner of the Election is " << candidates[winnerIndex] << "." << endl;
}

int calculateTotalVotes(int votes[], int numCandidates) {
    int total = 0;
    for (int i = 0; i < numCandidates; i++) {
        total += votes[i];
    }
    return total;
}

int findWinnerIndex(int votes[], int numCandidates) {
    int maxIndex = 0;
    for (int i = 1; i < numCandidates; i++) {
        if (votes[i] > votes[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// ========== OPTION 2: STUDENT SCORE DISTRIBUTION ==========

void studentScoreDistribution() {
    int scoreRanges[NUM_SCORE_RANGES] = {0}; // Initialize all to 0

    // Read and process scores from file
    processScoreFile(scoreRanges);

    // Display the distribution
    displayScoreDistribution(scoreRanges);

    cout << endl;
}

void processScoreFile(int scoreRanges[]) {
    ifstream inputFile("scores.txt");

    if (!inputFile) {
        cout << "Error: Could not open scores.txt file." << endl;
        return;
    }

    int score;
    while (inputFile >> score) {
        int rangeIndex = determineScoreRange(score);
        if (rangeIndex >= 0 && rangeIndex < NUM_SCORE_RANGES) {
            scoreRanges[rangeIndex]++;
        }
    }

    inputFile.close();
}

void displayScoreDistribution(int scoreRanges[]) {
    string rangeLabels[NUM_SCORE_RANGES] = {
        "0-24", "25-49", "50-74", "75-99",
        "100-124", "125-149", "150-174", "175-200"
    };

    cout << left << setw(20) << "Score Range"
         << right << setw(20) << "Number of Students" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < NUM_SCORE_RANGES; i++) {
        cout << left << setw(20) << rangeLabels[i]
             << right << setw(20) << scoreRanges[i] << endl;
    }
}

int determineScoreRange(int score) {
    if (score >= 0 && score <= 24) return 0;
    else if (score >= 25 && score <= 49) return 1;
    else if (score >= 50 && score <= 74) return 2;
    else if (score >= 75 && score <= 99) return 3;
    else if (score >= 100 && score <= 124) return 4;
    else if (score >= 125 && score <= 149) return 5;
    else if (score >= 150 && score <= 174) return 6;
    else if (score >= 175 && score <= 200) return 7;
    else return -1; // Invalid score
}

// ========== OPTION 3: ANNUAL TEMPERATURE TRACKER ==========

void annualTempTracker() {
    double temperatures[NUM_MONTHS][NUM_TEMP_TYPES];

    // Get temperature data from user
    getData(temperatures);

    // Display results
    displayTempResults(temperatures);

    cout << endl;
}

void getData(double temperatures[][NUM_TEMP_TYPES]) {
    for (int month = 0; month < NUM_MONTHS; month++) {
        cout << "Enter high temperature for month " << (month + 1) << ": ";
        cin >> temperatures[month][0]; // High temperature

        cout << "Enter low temperature for month " << (month + 1) << ": ";
        cin >> temperatures[month][1]; // Low temperature
    }

    cout << endl;
}

double averageHigh(double temperatures[][NUM_TEMP_TYPES]) {
    double sum = 0.0;
    for (int month = 0; month < NUM_MONTHS; month++) {
        sum += temperatures[month][0];
    }
    return sum / NUM_MONTHS;
}

double averageLow(double temperatures[][NUM_TEMP_TYPES]) {
    double sum = 0.0;
    for (int month = 0; month < NUM_MONTHS; month++) {
        sum += temperatures[month][1];
    }
    return sum / NUM_MONTHS;
}

int indexHighTemp(double temperatures[][NUM_TEMP_TYPES]) {
    int maxIndex = 0;
    for (int month = 1; month < NUM_MONTHS; month++) {
        if (temperatures[month][0] > temperatures[maxIndex][0]) {
            maxIndex = month;
        }
    }
    return maxIndex;
}

int indexLowTemp(double temperatures[][NUM_TEMP_TYPES]) {
    int minIndex = 0;
    for (int month = 1; month < NUM_MONTHS; month++) {
        if (temperatures[month][1] < temperatures[minIndex][1]) {
            minIndex = month;
        }
    }
    return minIndex;
}

void displayTempResults(double temperatures[][NUM_TEMP_TYPES]) {
    double avgHigh = averageHigh(temperatures);
    double avgLow = averageLow(temperatures);
    int highestMonth = indexHighTemp(temperatures);
    int lowestMonth = indexLowTemp(temperatures);

    cout << fixed << setprecision(2);
    cout << "Average High Temperature: " << avgHigh << endl;
    cout << "Average Low Temperature: " << avgLow << endl;
    cout << "Highest High Temp: " << temperatures[highestMonth][0]
         << " in " << getMonthName(highestMonth) << endl;
    cout << "Lowest Low Temp: " << temperatures[lowestMonth][1]
         << " in " << getMonthName(lowestMonth) << endl;
}

string getMonthName(int monthIndex) {
    string months[NUM_MONTHS] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (monthIndex >= 0 && monthIndex < NUM_MONTHS) {
        return months[monthIndex];
    }
    return "Unknown";
}
