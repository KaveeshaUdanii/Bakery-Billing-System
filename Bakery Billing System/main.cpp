#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
};

void DisplayMenu() {
    // Define your menu items and prices here
    string items[6] = {"Muffins", "Pastries", "Bun", "Cheesecake", "Brownies", "Donuts"};
    int prices[6] = {100, 200, 150, 300, 250, 300};

    cout << "\n------------Bun Talk Restaurant Menu-------------\n";
    for (int i = 0; i < 6; i++) {
        cout << i + 1 << ". " << items[i] << "\t" << prices[i] << "\n";
    }
    cout << "------------------------------------------------\n\n";
}

void SelectItems(int* &selection, int &selectionSize, int &totalBill, string items[], int prices[]) {
    cout << "\n------------Select Items-------------\n";
    int quantities[6] = {0};  // Array to store the quantities of each item

    while (true) {
        int number;
        cout << "Enter item number or 0 to end the selection: ";
        cin >> number;

        if (number == 0) {
            cout << "Selection completed.\n";
            break;
        } else if (number >= 1 && number <= 6) {
            int quantity;
            cout << "Enter the quantity for " << items[number - 1] << ": ";
            cin >> quantity;

            if (quantity > 0) {
                // Expand the selection array and add the selected item
                int* newSelection = new int[selectionSize + 1];
                for (int i = 0; i < selectionSize; i++) {
                    newSelection[i] = selection[i];
                }
                newSelection[selectionSize] = number;
                delete[] selection;
                selection = newSelection;
                selectionSize++;

                // Update the total bill
                totalBill += prices[number - 1] * quantity;

                // Update the quantities array
                quantities[number - 1] += quantity;
            } else {
                cout << "Invalid quantity. Please enter a positive number.\n";
            }
        } else {
            cout << "Invalid number\n";
        }
    }

    // Print the selected items and their quantities
    cout << "\n-------------Selected items and quantities:--------------\n";
    for (int i = 0; i < 6; i++) {
        if (quantities[i] > 0) {
            cout << items[i] << "\t" << quantities[i] << "\n";
        }
    }
}

void CalculateBill(int* selection, int selectionSize, int totalBill, string items[], int prices[]) {
    cout << "\n------------Bill-------------\n";
    for (int i = 0; i < selectionSize; i++) {
        cout << items[selection[i] - 1] << "\t" << prices[selection[i] - 1] << "\n";
    }
    cout << "Total Bill: " << totalBill << "\n";
    cout << "-----------------------------\n";
}

void control(){
	int option;
			    int* selection = nullptr; // Use dynamic memory allocation to store selected items
			    int selectionSize = 0;    // Keep track of the size of the selection array
			    int totalBill = 0;
			    string items[6] = {"Muffins", "Pastries", "Bun", "Cheesecake", "Brownies", "Donuts"};
			    int prices[6] = {100, 200, 150, 300, 250, 300};
			
			    while (true) {
			        cout << "\n---Select an option---\n";
			        cout << "1. Display Menu\n";
			        cout << "2. Select items\n";
			        cout << "3. Calculate Bill\n";
			        cout << "4. Exit\n";
			
			        cin >> option;
			
			        switch (option) {
			            case 1:
			                DisplayMenu();
			                break;
			            case 2:
			                SelectItems(selection, selectionSize, totalBill, items, prices);
			                break;
			            case 3:
			                CalculateBill(selection, selectionSize, totalBill, items, prices);
			                break;
			            case 4:
			                // Clean up dynamically allocated memory before exiting
			                delete[] selection;
			                return ;
			            default:
			                cout << "Invalid choice. Please try again.\n";
			        }
			    }
}

void SignIn() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;

    ifstream userFile(username + ".txt");
    if (userFile.is_open()) {
        userFile >> password;
        userFile.close();
        cout << "Enter your password: ";
        cin >> password;

        ifstream userFile(username + ".txt");
        if (userFile.is_open()) {
            string storedPassword;
            userFile >> storedPassword;
            userFile.close();
            if (password == storedPassword) {
                cout << "Sign in successful!\n";
                // Allow the user to access the system
                control();
                return;
            }
        }
    }
    cout << "Incorrect username or password. Sign in failed.\n";
}

void SignUp() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    ifstream userFile(username + ".txt");
    if (userFile.is_open()) {
        userFile.close();
        cout << "Username already exists. Please choose a different one.\n";
    } else {
        userFile.close();
        cout << "Enter a password: ";
        cin >> password;
        ofstream newUserFile(username + ".txt");
        newUserFile << password;
        newUserFile.close();
        cout << "Sign up successful! You can now sign in.\n";
    }
}

int main() {
    while (true) {
        cout << "---Select an option---\n";
        cout << "1. Sign In/Sign Up\n";
        cout << "2. Help\n";
        cout << "3. Exit\n";

        int option;
        cin >> option;

        switch (option) {
            case 1:
                cout << "1. Sign In\n2. Sign Up\n";
                int signInOption;
                cin >> signInOption;
                if (signInOption == 1) {
                    SignIn();
                } else if (signInOption == 2) {
                    SignUp();
                } else {
                    cout << "Invalid option. Please try again.\n";
                }
                break;
            case 2:
                cout << "\nIf you have not a account with our system, First you need to sign up with our system through enter a username, strong password. Then you are eligible to access it. Then you can view menu, select items, calculate total and also you can print the bill. \n\n";
                break;
            case 3:
            	cout<<"Thank you! come again.";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
