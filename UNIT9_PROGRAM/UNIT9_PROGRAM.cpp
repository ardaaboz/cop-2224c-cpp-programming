/*
 * Talha Arda Boz
 * 10/16/2025
 * Football Player Performance Management System
 * This program demonstrates effective use of structs, arrays, file input/output,
 * and menu-driven design through an application that manages and analyzes
 * football player performance data.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Constants
const int MAX_PLAYERS = 10;

// Struct definition for football player
struct FootballPlayer {
    string name;
    string position;
    int touchdowns;
    int catches;
    int passingYards;
    int receivingYards;
    int rushingYards;
};

// Function prototypes
void displayMenu();
void loadData(FootballPlayer players[], int &numPlayers);
void displayData(FootballPlayer players[], int numPlayers);
int searchPlayer(FootballPlayer players[], int numPlayers, string playerName);
void updatePlayer(FootballPlayer players[], int numPlayers);
void saveDataToFile(FootballPlayer players[], int numPlayers);

// Main function
int main() {
    FootballPlayer players[MAX_PLAYERS];
    int numPlayers = 0;
    bool dataLoaded = false;
    bool dataModified = false;
    int choice;

    // Load data at program start
    cout << "Loading player data from file..." << endl;
    loadData(players, numPlayers);
    if (numPlayers > 0) {
        dataLoaded = true;
        cout << "Successfully loaded " << numPlayers << " players." << endl;
    } else {
        cout << "No data file found or file is empty. Starting with empty database." << endl;
    }
    cout << endl;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore();
        cout << endl;

        switch (choice) {
            case 1: // Display All Players
                if (!dataLoaded || numPlayers == 0) {
                    cout << "No player data available. Please ensure footballData.txt exists." << endl;
                } else {
                    displayData(players, numPlayers);
                }
                break;

            case 2: // Search for Player
                if (!dataLoaded || numPlayers == 0) {
                    cout << "No player data available. Please ensure footballData.txt exists." << endl;
                } else {
                    string searchName;
                    cout << "Enter player name to search: ";
                    getline(cin, searchName);

                    int index = searchPlayer(players, numPlayers, searchName);

                    if (index != -1) {
                        cout << searchName << " found at index " << index << "." << endl;
                        cout << "Position: " << players[index].position << endl;
                        cout << "Touchdowns: " << players[index].touchdowns << endl;
                        cout << "Catches: " << players[index].catches << endl;
                        cout << "Passing Yards: " << players[index].passingYards << endl;
                        cout << "Receiving Yards: " << players[index].receivingYards << endl;
                        cout << "Rushing Yards: " << players[index].rushingYards << endl;
                    } else {
                        cout << "Player '" << searchName << "' not found in the database." << endl;
                    }
                }
                break;

            case 3: // Update Player Data
                if (!dataLoaded || numPlayers == 0) {
                    cout << "No player data available. Please ensure footballData.txt exists." << endl;
                } else {
                    updatePlayer(players, numPlayers);
                    dataModified = true;
                }
                break;

            case 4: // Save Data to File
                if (!dataLoaded || numPlayers == 0) {
                    cout << "No player data to save." << endl;
                } else {
                    saveDataToFile(players, numPlayers);
                    dataModified = false;
                }
                break;

            case 5: // Exit
                if (dataModified) {
                    char saveChoice;
                    cout << "Do you want to save changes before exiting? (Y/N): ";
                    cin >> saveChoice;
                    if (saveChoice == 'Y' || saveChoice == 'y') {
                        saveDataToFile(players, numPlayers);
                    }
                }
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                break;
        }

        if (choice != 5) {
            cout << endl;
        }

    } while (choice != 5);

    return 0;
}

// Function to display the main menu
void displayMenu() {
    cout << "=== Football Player Menu ===" << endl;
    cout << "1. Display All Players" << endl;
    cout << "2. Search for Player" << endl;
    cout << "3. Update Player Data" << endl;
    cout << "4. Save Data to File" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice (1-5): ";
}

// Function to load player data from file
void loadData(FootballPlayer players[], int &numPlayers) {
    ifstream inFile("footballData.txt");

    if (!inFile) {
        numPlayers = 0;
        return;
    }

    numPlayers = 0;
    string line;

    while (numPlayers < MAX_PLAYERS && getline(inFile, players[numPlayers].name)) {
        // Read position
        if (!getline(inFile, players[numPlayers].position)) {
            break;
        }

        // Read statistics (all on one line)
        if (!(inFile >> players[numPlayers].touchdowns
                     >> players[numPlayers].catches
                     >> players[numPlayers].passingYards
                     >> players[numPlayers].receivingYards
                     >> players[numPlayers].rushingYards)) {
            break;
        }

        // Clear the newline after reading numbers
        inFile.ignore();

        numPlayers++;
    }

    inFile.close();
}

// Function to display all players in a formatted table
void displayData(FootballPlayer players[], int numPlayers) {
    // Display header
    cout << left << setw(20) << "Name"
         << setw(18) << "Position"
         << right << setw(5) << "TD"
         << setw(8) << "Catch"
         << setw(8) << "Pass"
         << setw(8) << "Recv"
         << setw(8) << "Rush" << endl;

    cout << string(75, '-') << endl;

    // Display each player's data
    for (int i = 0; i < numPlayers; i++) {
        cout << left << setw(20) << players[i].name
             << setw(18) << players[i].position
             << right << setw(5) << players[i].touchdowns
             << setw(8) << players[i].catches
             << setw(8) << players[i].passingYards
             << setw(8) << players[i].receivingYards
             << setw(8) << players[i].rushingYards << endl;
    }
}

// Function to search for a player by name
int searchPlayer(FootballPlayer players[], int numPlayers, string playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].name == playerName) {
            return i;
        }
    }
    return -1; // Player not found
}

// Function to update a player's data
void updatePlayer(FootballPlayer players[], int numPlayers) {
    string playerName;
    cout << "Enter player name to update: ";
    getline(cin, playerName);

    int index = searchPlayer(players, numPlayers, playerName);

    if (index == -1) {
        cout << "Player '" << playerName << "' not found in the database." << endl;
        return;
    }

    // Update position
    cout << "Enter new position: ";
    getline(cin, players[index].position);

    // Update statistics
    cout << "Touchdowns: ";
    cin >> players[index].touchdowns;

    cout << "Catches: ";
    cin >> players[index].catches;

    cout << "Passing Yards: ";
    cin >> players[index].passingYards;

    cout << "Receiving Yards: ";
    cin >> players[index].receivingYards;

    cout << "Rushing Yards: ";
    cin >> players[index].rushingYards;

    cout << "Player data updated." << endl;
}

// Function to save all player data to file
void saveDataToFile(FootballPlayer players[], int numPlayers) {
    ofstream outFile("footballData_updated.txt");

    if (!outFile) {
        cout << "Error: Could not create output file." << endl;
        return;
    }

    for (int i = 0; i < numPlayers; i++) {
        outFile << players[i].name << endl;
        outFile << players[i].position << endl;
        outFile << players[i].touchdowns << " "
                << players[i].catches << " "
                << players[i].passingYards << " "
                << players[i].receivingYards << " "
                << players[i].rushingYards << endl;
    }

    outFile.close();
    cout << "Data saved to footballData_updated.txt" << endl;
}