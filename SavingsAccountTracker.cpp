
//  Created by Cody Buller
// Calculate the balance of a savings account at the end of a three month period.

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{

// variables
    double savingsStart; // Amount at beginning
    double annualRate; // Annual interest rate
    double deposit; // Amount deposited
    double totalDeposited = 0; // Total cash amount of deposits
    int counter = 1; // Counter for loop
    double balance = 0; // Total balance of account
    double withdrawlAmount; // Amount withdrawn during current month
    double totalWithdrawn = 0; // Total cash withdrawn
    double monthlyInterest; // Monthly Interest based off annual percentage
    double thisMonthInterest; // Interest for current month
    double totalInterest = 0; // Total interest


// Greet user!
    cout << "Hello! this program will calculate the balance of a savings account at the end of a three month period." << endl;

// Ask for starting balance
    cout << "\nWhat is the staring balance of your savings account?: ";
    cin >> savingsStart;

//Check if starting balance is valid
        if (savingsStart < 0)
        {
            cout << "\nStarting balance must be a positive amount.\n";
            exit(0);
        }
        balance += savingsStart; // add starting balance to balance
        cout << endl;

//Get annual interest rate
    cout << "What is the annual interest rate?: ";
    cin >> annualRate;
    cout << endl;

//Check if interest rate is valid
    if (annualRate < 0)
    {
        cout << "\nAnnual interest rate must be a positive amount.\n";
        exit(0);
        
    }

// Ask for information for each month
    do
    {
        // Get deposit information
        cout << "What is the total amount deposited for month " << counter << "?: ";
        cin >> deposit;
        cout << endl;
    
            if (deposit >= 0)
            {
                totalDeposited += deposit;
            }
            else
            {
                cout << "Deposit must be a positive amount.\n";
                exit(0);
            }
        
// Get withdrawl information
        cout << "What is the total amount withdrawn during month " << counter << "?: ";
        cin >> withdrawlAmount;
        cout << endl;
        // Calculate total
            if (withdrawlAmount >= 0 && withdrawlAmount <= balance)
            {
                totalWithdrawn += withdrawlAmount; // total amount withdrawn
                balance -= withdrawlAmount; // Balance after withdrawl
                monthlyInterest = (annualRate/12); // calculate interest per month based off annual rate
                thisMonthInterest = ((balance + (balance + deposit))/2) * monthlyInterest; // calculate this months interest
                balance += (deposit + thisMonthInterest); // Total balance for this month
                totalInterest += thisMonthInterest; // Total interest
                counter++;
            }
            else
            {
                cout << "Withdrawl amount must be a positive number and less than current balance\n";
                exit(0);
            }
    } while (counter <=3);
    
// Display results
    cout << "Starting account balance: " << savingsStart << endl;
    cout << "Total deposited: " << totalDeposited << endl;
    cout << "Total withdrawn: " << totalWithdrawn << endl;
    cout << "Total interest posted: " << totalInterest << endl;
    cout << "Your final balance is: " << fixed << setprecision(2) << balance << endl;
    
    
    return 0;
    
}
