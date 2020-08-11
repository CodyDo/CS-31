//
//  main.cpp
//  fine project
//
//  Created by Cody Do on 10/10/19.
//  Copyright © 2019 Cody Do. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Defendant: "; // Code asking for Defendant name
    string name;
    getline(cin,name);
    
    cout << "Amount paid (in thousands): "; // Code asking for amount paid
    double amtPaid;
    cin >> amtPaid;
    cin.ignore(10000,'\n');
    
    cout << "Fake athlete? (y/n): "; // Code asking for "y" or "n"
    char fake;
    cin >> fake;
    
    cout << "---\n";
    
    if (name == "") // Checks if name string is empty
    {
        cout << "You must enter a defendant name.\n";
        return(0);
    }
    else if (amtPaid < 0) // Checks if the amount paid is negative
    {
        cout << "The amount paid must not be negative.\n";
        return(0);
    }
    else if (fake != 'y'  &&  fake != 'n') //Checks if either "y" or "n" was not an input
    {
        cout << "You must enter y or n.\n";
        return(0);
    }
    
    double base_fine = 20; // Sets base amount for the fine (20 thousand)
    double fine_1 = 0.0, fine_2 = 0.0 , fine_3 = 0.0; // Creates fine_1/2/3 variables
    
    if (amtPaid <= 40) // Conditions to create fine_1 (the 66% of the first 40 million)
        fine_1 = amtPaid*.66;
    else if (amtPaid > 40)
        fine_1 = 40*.66;
    
    if (amtPaid <=40) // Conditions to create fine_2
        fine_2 = 0.0;
    else if (amtPaid > 40)
    {
        if (amtPaid <= 250) // set up conditions to do fine_2 = amtPaid-40 * 10% if fake = n, 22% if fake = y
        {
            if (fake == 'n')
                fine_2 = (amtPaid-40)*.10;
            else if (fake == 'y')
                fine_2 = (amtPaid-40)*.22;
        }
        else if (amtPaid > 250) // set up conditions to do fine_2 = 210 * 10% if fake = n, 22% if fake = y
        {
             if (fake == 'n')
                 fine_2 = 210*.10;
             else if (fake == 'y')
                 fine_2 = 210*.22;
         }
    }
    
    if (amtPaid <= 250) // Conditions to create fine_3
        fine_3 = 0.0;
    else if (amtPaid > 250)
        fine_3= (amtPaid-250)*.14;
    
    double final_fine= base_fine + fine_1 + fine_2 + fine_3;
    
    cout.setf(ios::fixed);
    cout.precision(1);
    cout << "The suggested fine for " << name << " is $" << final_fine << " thousand.\n";
}
