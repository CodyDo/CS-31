//
//  main.cpp
//  testPlot
//
//  Created by Cody Do on 10/22/19.
//  Copyright © 2019 Cody Do. All rights reserved.
//

#include "grid.h"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

//Prototype declarations
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
void FGplotHorizontalLine(int r, int c, int distance, char ch);
void FGplotVerticalLine(int r, int c, int distance, char ch);
void BGplotHorizontalLine(int r, int c, int distance, char ch);
void BGplotVerticalLine(int r, int c, int distance, char ch);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);


// Main Function (Taken from Specs)

int main()
{
    setSize(20,30);
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
    int position;
    int status = performCommands(cmd, currentChar, currentMode, position);
    switch (status)
    {
      case 0:
            draw();
        break;
      case 1:
            cout << "Syntax error at position " << position+1 << endl;
        break;
      case 2:
            cout << "Cannot perform command at position " << position+1 << endl;
        break;
      default:
          // It should be impossible to get here.
            cerr << "performCommands returned " << status << "!" << endl;
    }
    }
}

//plotLine Function Code

void FGplotHorizontalLine(int r, int c, int distance, char ch) //function for creating horizontal foreground line
{
    if (r <= getRows() && c+distance <= getCols() && r > 0 && c+distance > 0)
    {
        for( int k = 0; k <= distance; k++)
            setChar(r, c+k, ch);
        for( int k = 0; k >= distance; k--)
            setChar(r, c+k, ch);
    }
    else
        return;
}

void BGplotHorizontalLine(int r, int c, int distance, char ch) //function for creating a horizontal background line
{
    if (r <= getRows() && c+distance <= getCols() && r > 0 && c+distance > 0)
    {
        for( int k = 0; k <= distance; k++)
        {
            char x = getChar(r, c+k);
            if (x == ' ')
                setChar(r, c+k, ch);
        }
        for( int k = 0; k >= distance; k--)
        {
            char x = getChar(r, c+k);
            if (x == ' ')
                setChar(r, c+k, ch);
        }
    }
    else
        return;
}

void FGplotVerticalLine(int r, int c, int distance, char ch) //function for creating a vertical foreground line
{
    if (r+distance <= getRows() && c <= getCols() && r+distance > 0 && c > 0)
    {
        for( int k = 0; k <= distance; k++)
            setChar(r+k, c, ch);
        for( int k = 0; k >= distance; k--)
            setChar(r+k, c, ch);
    }
    else
        return;
}

void BGplotVerticalLine(int r, int c, int distance, char ch) //function for creating a vertical background line
{
    if (r+distance <= getRows() && c <= getCols() && r+distance > 0 && c > 0)
    {
        for( int k = 0; k <= distance; k++)
        {
            char x = getChar(r+k, c);
            if (x == ' ')
                setChar(r+k, c, ch);
        }
        for( int k = 0; k >= distance; k--)
        {
            char x = getChar(r+k, c);
            if (x == ' ')
                setChar(r+k, c, ch);
        }
    }
    else
        return;
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) //integrates four previous functions to give true/false output depending on whether the graphing input arguements can succeed (true) or not (false)
{
    if (dir == HORIZ)
    {
        if (r <= getRows() && c+distance <= getCols() && r > 0 && c+distance > 0)
        {
            if (fgbg == FG)
            {
                FGplotHorizontalLine(r, c, distance, plotChar);
                return true;
            }
            else if (fgbg == BG)
            {
                BGplotHorizontalLine(r, c, distance, plotChar);
                return true;
            }
            return false;
        }
        else
            return false;
    }
    else if (dir == VERT)
    {
        if (r+distance <= getRows() && c <= getCols() && r+distance > 0 && c > 0)
        {
            if (fgbg == FG)
            {
                FGplotVerticalLine(r, c, distance, plotChar);
                return true;
            }
            else if (fgbg == BG)
            {
                BGplotVerticalLine(r, c, distance, plotChar);
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

//performCommands Function Code

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int posCount = 0; //Counter for position WITHIN function
    int rowCurrent = 1;
    int colCurrent = 1;
    while (posCount != commandString.size())
    {
        if(isalpha(commandString[posCount])) //Checks if position is letter. If it is, checks which type of letter.
        {
            if(toupper(commandString[posCount]) == 'H') // CODE FOR 'H' CMD
                {
                    int OGPos = posCount;
                    posCount++;
                    string number;
                    if (! isdigit(commandString[posCount])) //Checks non-digit
                    {
                        if (commandString[posCount] == '-') // Checks Negative
                           {
                               number += commandString[posCount];
                               posCount++;
                           }
                        else
                        {
                            badPos = posCount;
                            return 1;
                        }
                    }
                    for(int k = 0; k < 2; k++) // Checks up to 2 digits after
                    {
                        if (isdigit(commandString[posCount]))
                        {
                            number += commandString[posCount];
                            posCount++;
                        }
                        else
                            break;
                    }
                    int move = stoi(number); // Converts String to Int & Plots
                    if((plotLine(rowCurrent, colCurrent, move, HORIZ, plotChar, mode))) //Checks if input can be done or not
                        {
                            colCurrent = colCurrent + move;
                            continue;
                        }
                    else
                        {
                            badPos = OGPos;
                            return 2;
                        }
                }
        
            if(toupper(commandString[posCount]) == 'V') // CODE FOR 'V' CMD
                {
                    int OGPos = posCount;
                    posCount++;
                    string number;
                    if (! isdigit(commandString[posCount])) //Checks non-digit
                    {
                        if (commandString[posCount] == '-') // Checks Negative
                           {
                               number += commandString[posCount];
                               posCount++;
                           }
                        else
                        {
                            badPos = posCount;
                            return 1;
                        }
                    }
                    for(int k = 0; k < 2; k++) // Checks up to 2 digits after
                    {
                        if (isdigit(commandString[posCount]))
                        {
                            number += commandString[posCount];
                            posCount++;
                        }
                        else
                            break;
                    }
                    int move = stoi(number); // Converts String to Int & Plots
                    if((plotLine(rowCurrent, colCurrent, move, VERT, plotChar, mode))) //Checks if input can be done or not
                        {
                            rowCurrent = rowCurrent + move;
                            continue;
                        }
                    else
                        {
                            badPos = OGPos;
                            return 2;
                        }
                }
                
            if(toupper(commandString[posCount]) == 'F') // CODE FOR 'F' CMD
                {
                    mode = FG;
                    posCount++;
                    if (isprint(commandString[posCount]))
                    {
                        plotChar = commandString[posCount];
                        posCount++;
                    }
                    else
                    {
                        badPos = posCount;
                        return 1;
                    }
                    continue;
                }
                
            if(toupper(commandString[posCount]) == 'B') // CODE FOR 'B' CMD
            {
                mode = BG;
                posCount++;
                if (isprint(commandString[posCount]))
                {
                    plotChar = commandString[posCount];
                    posCount++;
                }
                else
                {
                    badPos = posCount;
                    return 1;
                }
                continue;
            }
                
                
            if(toupper(commandString[posCount]) == 'C') // CODE FOR 'C' CMD
                {
                    clearGrid();
                    mode = FG;
                    plotChar = '*';
                    posCount++;
                    continue;
                }
            else // If letter is not H, V, C, B, or F, then output error
            {
                badPos = posCount;
                return 1;
            }
        }
        if(! isalpha(commandString[posCount])) // If not letter, output error
        {
            badPos = posCount;
            return 1;
        }
    }
    return 0;
}
