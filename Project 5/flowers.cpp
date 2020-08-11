//
//  flowers.cpp
//  flowers
//
//  Created by Cody Do on 11/9/19.
//  Copyright © 2019 Cody Do. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const int MAXWORDS = 9000;

//Prototype Declarations
int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
bool checkWord(const char trialWord[], const char words[][MAXWORDLEN+1], int nWords);


//Path for Wordlist
const char WORDFILENAME[] = "/Users/Cody/Documents/School/College/Sophomore Year/Fall Quarter/CS 31/Project 5/wordlist.txt";

int main()
{
    char wordList[MAXWORDS][MAXWORDLEN+1]; //Makes an array to hold C strings
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); //Fills array with words and holds # of words in nWords
    
    if(nWords < 1) { //Checks if there aren't any words present
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    cout << "How many rounds do you want to play? "; //Asks user for # of rounds
    int numRounds;
    cin >> numRounds;
    cin.ignore(10000, '\n');
    
    if (numRounds < 1) { //Checks to make sure # of rounds are positive
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    double totalTries = 0; //Set up variables to hold total tries, max and min of all the rounds the user wants to play
    int minimum = 0;
    int maximum = 0;
    
    for (int k = 0; k < numRounds; k++) {
        cout << "\nRound " << k+1 << endl; //Outputs Round #
        int randNum = randInt(0, nWords-1); //Produces a random number
        cout << "The mystery word is " << strlen(wordList[randNum]) << " letters long." << endl; //Outputs the length of mystery word
        
        int numTries = playOneRound(wordList, nWords, randNum); //Plays game
        
        if (numTries == 1) //Checks amount of tries in the last round. Outputs proper response.
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << numTries << " tries." << endl;
        
        if(minimum == 0) // If first round AKA both min and max = 0, set both to the number of tries
            minimum = numTries;
        if(maximum == 0)
            maximum = numTries;
        
        if(numTries < minimum) // If number of tries less than minimum, then minimum is set equal to the new value
            minimum = numTries;
        if(numTries > maximum)// If number of tries more than maximum, then maximum is set equal to the new value
            maximum = numTries;
        totalTries += numTries; //Add number of recent tries to total tries
        
        double average = totalTries/(k+1); //Computes average of all rounds
        
        cout.setf(ios::fixed); //sets up # of decimal points to output
        cout.precision(2);
        
        cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl; //Outputs statistical data
    }
}

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
    if(nWords < 1 || wordnum < 0 || wordnum >= nWords) //Checks that nWords and wordnum are valid.
        return -1;
    
    int numTries = 0; //Creates variable for number of tries and the input trial word
    char trialWord[101];
    
    while(strcmp(trialWord,words[wordnum]) != 0) {
        cout << "Trial word: "; //Prompts user for trial word
        cin.getline(trialWord, 101);
        
        if(strcmp(trialWord,words[wordnum]) == 0) { //If the word is correct, incremenet numTries and break out of the loop
            numTries++;
            break;
        }
        
        if(checkWord(trialWord, words, nWords)) { //Checks if word is usable in game
            numTries++; //Increments numTries
            //Bool arrays for flowers/bees are made below to keep track of which position in the word are already "taken" by a flower or bee.
            bool flowersPos[] = {false, false, false, false, false, false};
            bool beesPos[] = {false, false, false, false, false, false};
            int flowers = 0;
            int bees = 0;
            
            for (int k = 0; words[wordnum][k] != '\0'; k++) { //Goes through mystery word and checks if any letters match at exact positions. If it does, increment flower and alter position arrays.
                if (trialWord[k] == words[wordnum][k]) {
                    flowers++;
                    flowersPos[k] = true;
                    beesPos[k] = true;
                }
            }
            
            for (int k = 0; trialWord[k] != '\0'; k++) { //Goes through trial word array
                if (flowersPos[k]) //If letter used for flower already, move on to the next position
                    continue;
                for (int j = 0; words[wordnum][j] != '\0'; j++) { //Goes through mystery word array
                    if(words[wordnum][j] == trialWord[k] && !beesPos[j]) { //If trial word and mystery word have matching letters that haven't been noticed yet, increment bees, alter bees position array, and break
                        bees++;
                        beesPos[j] = true;
                        break;
                    }
                }
            }
            cout << "Flowers: " << flowers << ", Bees: " << bees << endl;
        }
    }
    return numTries; //Returns the amount of times it took to find the right word
}

bool checkWord(const char trialWord[], const char words[][MAXWORDLEN+1], int nWords) { //Checks if the word is usable in the game
    if (strlen(trialWord) < 4 || strlen(trialWord) > 6) { //Checks if the trial word is the appropriate length
        cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
        return false;
    }
    
    for (int k = 0; trialWord[k] != '\0'; k++) { //Checks if the word is a non-lowercase letter
        if (!islower(trialWord[k]) || !isalpha(trialWord[k])) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            return false;
        }
    }
            
    for (int k = 0; k < nWords; k++) { //Checks if the word is a word in the list of words for the game
        if (strcmp(words[k], trialWord) == 0)
            return true;
    }
    
    cout << "I don't know that word." << endl; //If the word is of the proper length, all lowercase letters, but doesn't exist in the list of words, output proper response and return false.
    return false;
        
}
