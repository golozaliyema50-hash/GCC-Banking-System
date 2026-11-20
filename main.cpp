// Gauteng City College - Introduction to Programming (NQF 4)
// Assignment: Banking System in C++
// Replace the sample users and PINs with your own test details if required.

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

// At least three users are stored in parallel arrays.
const int USER_COUNT = 3;
string names[USER_COUNT] = {"Liyema goloza", "Thabo Nkosi", "Aisha Khan"};
int accountNumbers[USER_COUNT] = {1002, 1003, 1004};
int pins[USER_COUNT] = {1111, 3333, 4444};
double balances[USER_COUNT] = {2000.00, 29000.00, 4000.00};

// Function declarations
void displayMenu();
int getInteger(string message);
double getPositiveAmount(string message);
int login();
void deposit(int userIndex);
void withdraw(int userIndex);
void sendCash(int senderIndex);
void checkBalance(int userIndex);
int findAccount(int accountNumber);
void showUserDetails(int userIndex);

int main()
{
    cout << "=================================\n";
    cout << "          GCC BANK\n";
    cout << "=================================\n";

    int currentUser = login();

    if (currentUser == -1)
    {
        cout << "Too many incorrect login attempts. Goodbye.\n";
        return 0;
    }

    cout << "\nWelcome, " << names[currentUser] << "!\n";

    int choice;

    // The menu repeats until the user chooses Exit.
    do
    {
        displayMenu();
        choice = getInteger("Enter choice: ");

        switch (choice)
        {
            case 1:
                deposit(currentUser);
                break;

            case 2:
                withdraw(currentUser);
                break;

            case 3:
                sendCash(currentUser);
                break;

            case 4:
                checkBalance(currentUser);
                break;

            case 5:
                cout << "\nThank you for using GCC Bank. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid menu choice. Please choose 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}

// Displays the banking menu.
void displayMenu()
{
    cout << "\n========== GCC BANK ==========\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "==============================\n";
}

// Reads an integer and handles letters or other invalid input.
int getInteger(string message)
{
    int value;

    while (true)
    {
        cout << message;
        cin >> value;

        if (!cin.fail())
        {
            return value;
        }

        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads an amount greater than zero.
double getPositiveAmount(string message)
{
    double amount;

    while (true)
    {
        cout << message;
        cin >> amount;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (amount <= 0)
        {
            cout << "Amount must be more than 0.\n";
        }
        else
        {
            return amount;
        }
    }
}

// Checks the account number and PIN. Returns the user's array index,
// or -1 if all three login attempts are incorrect.
int login()
{
    int enteredAccount;
    int enteredPin;

    for (int attempt = 1; attempt <= 3; attempt++)
    {
        cout << "\nAccount number: ";
        enteredAccount = getInteger("");

        cout << "PIN: ";
        enteredPin = getInteger("");

        for (int i = 0; i < USER_COUNT; i++)
        {
            if (accountNumbers[i] == enteredAccount && pins[i] == enteredPin)
            {
                return i;
            }
        }

        cout << "Incorrect account number or PIN. Attempts left: "
             << 3 - attempt << "\n";
    }

    return -1;
}

// Adds money to the logged-in user's balance.
void deposit(int userIndex)
{
    double amount = getPositiveAmount("Enter amount to deposit: R");

    balances[userIndex] = balances[userIndex] + amount;

    cout << fixed << setprecision(2);
    cout << "Deposit successful. New balance: R"
         << balances[userIndex] << "\n";
}

// Removes money only when the user has enough funds.
void withdraw(int userIndex)
{
    double amount = getPositiveAmount("Enter amount to withdraw: R");

    if (amount <= balances[userIndex])
    {
        balances[userIndex] = balances[userIndex] - amount;

        cout << fixed << setprecision(2);
        cout << "Withdrawal successful. New balance: R"
             << balances[userIndex] << "\n";
    }
    else
    {
        cout << "Insufficient funds. You cannot withdraw more than your balance.\n";
    }
}

// Finds an account number and returns its position in the arrays.
// Returns -1 when the account does not exist.
int findAccount(int accountNumber)
{
    for (int i = 0; i < USER_COUNT; i++)
    {
        if (accountNumbers[i] == accountNumber)
        {
            return i;
        }
    }

    return -1;
}

// Transfers money between two users and updates both balances.
void sendCash(int senderIndex)
{
    int recipientAccount = getInteger("Enter recipient account number: ");
    int recipientIndex = findAccount(recipientAccount);

    if (recipientIndex == -1)
    {
        cout << "Invalid account number. Recipient was not found.\n";
        return;
    }

    if (recipientIndex == senderIndex)
    {
        cout << "You cannot send cash to your own account.\n";
        return;
    }

    double amount = getPositiveAmount("Enter amount to send: R");

    if (amount <= balances[senderIndex])
    {
        balances[senderIndex] = balances[senderIndex] - amount;
        balances[recipientIndex] = balances[recipientIndex] + amount;

        cout << fixed << setprecision(2);
        cout << "Cash sent successfully to " << names[recipientIndex] << ".\n";
        cout << "Your new balance is R" << balances[senderIndex] << "\n";
    }
    else
    {
        cout << "Insufficient funds. Cash was not sent.\n";
    }
}

// Displays the logged-in user's current balance.
void checkBalance(int userIndex)
{
    cout << fixed << setprecision(2);
    cout << "\nAccount holder: " << names[userIndex] << "\n";
    cout << "Account number: " << accountNumbers[userIndex] << "\n";
    cout << "Current balance: R" << balances[userIndex] << "\n";
}
