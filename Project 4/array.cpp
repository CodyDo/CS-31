//
//  array.cpp
//  Array Functions
//
//  Created by Cody Do on 11/2/19.
//  Copyright © 2019 Cody Do. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Function Prototypes
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);


// Main Function
int main() {
    string h[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
    assert(lookup(h, 7, "gordon") == 5);
    assert(lookup(h, 7, "fiona") == 2);
    assert(lookup(h, 2, "fiona") == -1);
    assert(positionOfMax(h, 7) == 3);

    string g[4] = { "mick", "marie", "lindsey", "nancy" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "mick?" && g[3] == "nancy?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "marie?");

    string e[4] = { "fiona", "rudy", "", "gordon" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "marie", "marie", "marie", "rudy", "rudy" };
    assert(countRuns(d, 5) == 2);

    string f[3] = { "lindsey", "fiona", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

    assert(separate(h, 7, "lindsey") == 3);

    cout << "All tests succeeded" << endl;
}


// Function Coding

//Function 1
int appendToAll(string a[], int n, string value) {
    if(n < 0) //Checks if negative
        return -1;
    for (int k = 0; k < n; k++) //Loops through and appends to every element
        a[k] += value;
    return n;
}

//Function 2
int lookup(const string a[], int n, string target) {
    if (n < 0) //Checks if negative
        return -1;
    for (int k = 0; k <= n; k++) {
        if (k == n) // Only possible to reach here if none of the elements  match the target
            return -1;
        if (target == a[k]) // If target found, returns position
            return k;
    }
    return -1;
}

//Function 3 (?)
int positionOfMax(const string a[], int n) {
    if (n <= 0) //Checks if n is negative or 0
        return -1;
    int posString = 0;
    for (int k = 0; k < n; k++) { //Loop to show that if current position is > the greatest string (up to that point), then it's stored as the new greatest string
        if (a[k] > a[posString])
            posString = k;
    }
    return posString;
}

//Function 4
int rotateLeft(string a[], int n, int pos) {
    if (n < 0 || pos < 0 || pos >= n) // Checks if n or pos is negative or is the position is > or equal to the unique elements we wish to check
        return -1;
    string temp = a[pos];
    for (int k = pos; k < n-1; k++) { //Loop to move elements forward
        a[k] = a[k+1];
    }
    a[n-1] = temp; //Sets last nth element to original pos element
    return pos;
}

//Function 5
int countRuns(const string a[], int n) {
    if (n < 0) //Checks if negative
        return -1;
    if (n == 0) // If no elements are looked at, then no repeats are found
        return 0;
    int counter = 1;
    for (int k = 0; k < n-1; k++) { //Loop to see if the current element and next element match. If they don't, the counter raises
        if (a[k] != a[k+1])
            counter++;
    }
    return counter;
}

//Function 6
int flip(string a[], int n) {
    if (n < 0) //Checks if negative
        return -1;
    for (int k = 0; k < n/2; k++) { //Loop set up that essentially cuts a string in half. Flips the values of the opposite positions through a temp variable.
        string temp = a[k];
        int p = n-1-k;
        a[k] = a[p];
        a[p] = temp;
    }
    return n;
}

//Function 7
int differ(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0 || (n1 == 0 && n2 == 0)) // Checks if n1 and n2 are negative and if they're both 0
        return -1;
    int maxPosition; //Establishes the max amount of elements to be scanned
    if (n1 <= n2)
        maxPosition = n1;
    else
        maxPosition = n2;
    for (int k = 0; k < maxPosition; k++) { //If corresponding elements don't match, returns proper value
        if (a1[k] != a2[k])
            return k;
    }
    return maxPosition;
}

//Function 8
int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0 || n1 < n2) //Checks if n1 or n2 is negative or if n2 is larger than n1
        return -1;
    if ((n1 == 0 && n2 == 0) || n2 == 0) //Checks if n2 is 0 or if both
        return 0;
    int amtMatched = 0;
    for (int k = 0; k < n1 ; k++)
        for(int j = 0; j < n2; j++) {
            if (a1[k] == a2[j]) { //Nested for loop to check if first element in n2 matches with an element in n1.
                amtMatched++;
                if (amtMatched == n2)
                    return k - amtMatched + 1;
                k++; //Increments k for next iteration check if a1[k] and a2[j] elements match
            }
            else
                amtMatched = 0;
        }
    return -1; //Returns -1 if there are no matches
}

//Function 9
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 <0) //Checks if negative
        return -1;
    for (int k = 0; k < n1; k++) //Nested for loop to check each element in a1 with each element in a2. First match is returned.
        for (int j = 0; j <n2; j++)
            if (a1[k] == a2[j])
                return k;
    return -1;
}

//Function 10
int separate(string a[], int n, string separator) {
    if (n < 0) //Checks if negative
        return -1;
    int counter = 0; //Used to see where the separator would be in the array if it was actually an element
    for (int k = n-1; k >= 0; k--) { //Starts from the end of the array and checks if each element is > separator. If it it, it's pushed to the end.
        if (a[k] >= separator)
            rotateLeft(a, n, k);
        else
            counter++;  // If separator is larger than a value, then that means the separator should be at least one spot higher in the array
    }
    for(int k = 0; k < n; k++)  //Used to deal with situations where the separator already exists in the array.
        if (a[k] == separator) {
            string temp = a[k];
            a[k] = a[counter];
            a[counter] = temp;
            counter++;
        }
            
    for (int k = 0; k < n; k++) // Runs through array after rearranged and outputs first non < string after separator
        if (a[k] >= separator)
            return k;
    return n;
}
