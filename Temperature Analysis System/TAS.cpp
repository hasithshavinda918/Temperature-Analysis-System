#include <iostream>    // For input/output operations
#include <iomanip>     // For manipulating output formatting
#include <fstream>     // For file handling operations
#include <string>      // For using the string class

using namespace std;

const int DAYS_IN_MONTH = 30;  // Define the number of days in a month as a constant

// Function prototypes
bool login();   // Handles user login
void inputTemperatures(float dayTemps[], float nightTemps[], int days);   // Inputs temperatures
void displayTemperatures(float dayTemps[], float nightTemps[], int days); // Displays temperatures
void calculateFluctuations(float dayTemps[], float nightTemps[], float fluctuations[], int days);  // Calculates temperature fluctuations
void analyzeSuitability(float dayTemps[], float nightTemps[], int days);  // Analyzes temperature suitability for orchids
float celsiusToFahrenheit(float celsius);   // Converts Celsius to Fahrenheit
void saveData(float dayTemps[], float nightTemps[], int days);   // Saves data to a file

int main() {
    if (!login()) {   // Attempt login and exit if unsuccessful
        cout << "Login failed. Try again later.\n";
        return 1;   // Exit the program with a non-zero status
    }

    float dayTemps[DAYS_IN_MONTH];   // Array to store daytime temperatures
    float nightTemps[DAYS_IN_MONTH]; // Array to store nighttime temperatures
    float fluctuations[DAYS_IN_MONTH];  // Array to store temperature fluctuations
    int choice;   // Variable to store the user's menu choice

    do {
        // Display main menu
        cout << "\n=============================================\n";
        cout << "      Orchi-flora Temperature Analysis System      \n";
        cout << "=============================================\n";
        cout << "1. Input Temperatures\n";
        cout << "2. Display Temperatures\n";
        cout << "3. Calculate Daily Fluctuations\n";
        cout << "4. Analyze Temperature Suitability for Orchids\n";
        cout << "5. Convert Celsius to Fahrenheit\n";
        cout << "6. Save Data to File\n";
        cout << "7. Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;   // Get user's menu choice

        switch (choice) {
            case 1:
                inputTemperatures(dayTemps, nightTemps, DAYS_IN_MONTH);  // Input temperatures
                break;
            case 2:
                displayTemperatures(dayTemps, nightTemps, DAYS_IN_MONTH);  // Display temperatures
                break;
            case 3:
                calculateFluctuations(dayTemps, nightTemps, fluctuations, DAYS_IN_MONTH);  // Calculate fluctuations
                break;
            case 4:
                analyzeSuitability(dayTemps, nightTemps, DAYS_IN_MONTH);  // Analyze temperature suitability
                break;
            case 5: {
                float celsius;
                cout << "Enter temperature in Celsius: ";
                cin >> celsius;
                cout << "Temperature in Fahrenheit: " << celsiusToFahrenheit(celsius) << " °F\n";  // Convert and display temperature
                break;
            }
            case 6:
                saveData(dayTemps, nightTemps, DAYS_IN_MONTH);  // Save data to a file
                break;
            case 7:
                cout << "Exiting program. Thank you for using the system!\n";  // Exit program
                break;
            default:
                cout << "Invalid choice! Please try again.\n";  // Handle invalid input
        }
    } while (choice != 7);  // Repeat until the user chooses to exit

    return 0;  // Successful program termination
}

bool login() {
    string username;   // To store the entered username
    string password;   // To store the entered password
    const string correctUsername = "admin";  // Hardcoded correct username
    const string correctPassword = "password";  // Hardcoded correct password

    cout << "Enter username: ";
    cin >> username;   // Input username
    cout << "Enter password: ";
    cin >> password;   // Input password

    if (username == correctUsername && password == correctPassword) {  // Validate credentials
        cout << "Login successful!\n";
        return true;   // Return true if credentials are correct
    } else {
        cout << "Invalid username or password. Try again later.\n";
        return false;   // Return false if credentials are incorrect
    }
}

void inputTemperatures(float dayTemps[], float nightTemps[], int days) {
    for (int i = 0; i < days; i++) {
        cout << "Day " << i + 1 << " - Enter daytime temperature (°F): ";
        cin >> dayTemps[i];   // Input daytime temperature for each day
        cout << "Day " << i + 1 << " - Enter nighttime temperature (°F): ";
        cin >> nightTemps[i];  // Input nighttime temperature for each day
    }
}

void displayTemperatures(float dayTemps[], float nightTemps[], int days) {
    // Display header for the temperature table
    cout << "\nDay\tDay Temp (°F)\tNight Temp (°F)\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < days; i++) {
        // Display temperatures for each day
        cout << i + 1 << "\t" << dayTemps[i] << "\t\t" << nightTemps[i] << "\n";
    }
}

void calculateFluctuations(float dayTemps[], float nightTemps[], float fluctuations[], int days) {
    float totalFluctuation = 0;   // Initialize total fluctuation
    for (int i = 0; i < days; i++) {
        fluctuations[i] = dayTemps[i] - nightTemps[i];   // Calculate daily fluctuation
        totalFluctuation += fluctuations[i];   // Accumulate total fluctuation
        cout << "Day " << i + 1 << " - Temperature fluctuation: " << fluctuations[i] << " °F\n";   // Display daily fluctuation
    }
    // Display average fluctuation over the month
    cout << "Average temperature fluctuation of the month: " << totalFluctuation / days << " °F\n";
}

void analyzeSuitability(float dayTemps[], float nightTemps[], int days) {
    float maxDayTemp = dayTemps[0], minDayTemp = dayTemps[0];   // Initialize max and min daytime temps
    float maxNightTemp = nightTemps[0], minNightTemp = nightTemps[0];   // Initialize max and min nighttime temps
    float totalDayTemp = 0, totalNightTemp = 0;   // Initialize total temperatures

    for (int i = 1; i < days; i++) {
        if (dayTemps[i] > maxDayTemp) maxDayTemp = dayTemps[i];  // Update max daytime temp
        if (dayTemps[i] < minDayTemp) minDayTemp = dayTemps[i];  // Update min daytime temp
        if (nightTemps[i] > maxNightTemp) maxNightTemp = nightTemps[i];  // Update max nighttime temp
        if (nightTemps[i] < minNightTemp) minNightTemp = nightTemps[i];  // Update min nighttime temp
        
        totalDayTemp += dayTemps[i];   // Accumulate total daytime temp
        totalNightTemp += nightTemps[i];  // Accumulate total nighttime temp
    }

    totalDayTemp += dayTemps[0];  // Include first day's temps in total
    totalNightTemp += nightTemps[0];

    float avgDayTemp = totalDayTemp / days;  // Calculate average daytime temp
    float avgNightTemp = totalNightTemp / days;  // Calculate average nighttime temp

    // Display max, min, and average temperatures
    cout << "\nDaytime temperatures: Max = " << maxDayTemp << " °F, Min = " << minDayTemp << " °F\n";
    cout << "Nighttime temperatures: Max = " << maxNightTemp << " °F, Min = " << minNightTemp << " °F\n";
    cout << "Average daytime temperature: " << avgDayTemp << " °F\n";
    cout << "Average nighttime temperature: " << avgNightTemp << " °F\n";

    // Determine if the temperature conditions are suitable for orchid growth
    if (avgDayTemp >= 70 && avgDayTemp <= 80 && avgNightTemp >= 60 && avgNightTemp <= 62) {
        cout << "The temperature conditions are suitable for orchid growth.\n";
    } else {
        cout << "The temperature conditions are not ideal for orchid growth.\n";
    }
}

float celsiusToFahrenheit(float celsius) {
    return (celsius * 9 / 5) + 32;  // Convert Celsius to Fahrenheit
}

void saveData(float dayTemps[], float nightTemps[], int days) {
    ofstream outFile("temperature_data.txt");   // Open file for writing
    if (!outFile) {   // Check if file opened successfully
        cout << "Error opening file for writing!\n";
        return;
    }

    // Write header to file
    outFile << "Day\tDay Temp (°F)\tNight Temp (°F)\n";
    outFile << "-----------------------------------------\n";
    for (int i = 0; i < days; i++) {
        // Write temperatures for each day to file
        outFile << i + 1 << "\t" << dayTemps[i] << "\t\t" << nightTemps[i] << "\n";
    }

    outFile.close();   // Close the file
    cout << "Data saved to temperature_data.txt\n";  // Confirm data saved
}

