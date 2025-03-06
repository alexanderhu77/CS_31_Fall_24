#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>
#include "utilities.h"
using namespace std;

const int MAXWORDS = 8000;


const char WORDFILENAME[] = "C:/CS31/Project_5/Project_5/smallwords.txt";


int runOneRound(const char words[][7], int nWords, int wordnum) {
    int stars = 0;
    int planets = 0;


    if (nWords < 1 || wordnum < 0 || wordnum >= nWords) {
        return -1;
    }
    char secret[7]; // word to be guessed
    strcpy(secret, words[wordnum]);



    int tries = 0;
    // keep running below until user guesses word correctly
    while (true) {
        
        tries++;
        char trial[102];
        cout << "Trial word: ";
        cin.getline(trial, 102);
        

        if (strlen(trial) < 4 || strlen(trial) > 6) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            tries--;
            continue;
            
        }

        // checks the c string to make sure that all letters are lowercase and are part of the alphabet
        bool validWord = true;
        for (int i = 0; i < strlen(trial); i++) {
            if (!isalpha(trial[i]) || !islower(trial[i])) {
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                validWord = false;
                
                break;
                
            }
        }

        if (!validWord) {
            tries--;
            continue;

        }

        // makes sure that the word that is being guessed exists and is valid
        validWord = false;
        for (int i = 0; i < nWords; i++) {
            if (strcmp(words[i], trial) == 0) {
                validWord = true;
                break;
            }
        }

        if (!validWord) {
            cout << "I don't know that word." << endl;
            tries--;
            continue;
        }

        // two arrays used to track elemnets that have been matched
        bool secretAvailable[7] = { }; 
        bool trialAvailable[7] = { }; // not stictly necessary to write out all the false because initialized to 0 (false) anayway

        for (int i = 0; i < strlen(secret); i++) {
            if (trial[i] == secret[i]) {
                stars++;
                secretAvailable[i] = true;
                trialAvailable[i] = true;
            }
        }

        // code below only checks the unused letters in trial (not stars) and scans the secret word for matching letters, marking which ones have been taken to remove duplicate planets
        for (int i = 0; i < strlen(trial); i++) { //changed to trial from secret
            if (!trialAvailable[i]) { 
                for (int j = 0; j < strlen(secret); j++) {
                    if (!secretAvailable[j] && trial[i] == secret[j]) {
                        planets++;
                        secretAvailable[j] = true; // note which chars have been matched
                        break;               
                    }
                }
            }
        }
        if (stars == strlen(secret)) {
            break;
        }
        
        cout << "Stars: " << stars << ", Planets: " << planets << endl;
        

        stars = 0;
        planets = 0;
        
       
    }

    return tries;
    

}


int main() {
    char wordList[MAXWORDS][MAXWORDLEN + 1];
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); // this varaible is the actual number of words in the array

    // double needed for average division later
    double totalTries = 0;

    
    int minTries = 2147483647;  // largest int that can be stored in c++ 
    int maxTries = 0;

    if (nWords < 1){
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }

    int numRounds;
    cout << "How many rounds do you want to play? ";
    cin >> numRounds;
    cin.ignore(1000, '\n');

    if (numRounds <= 0) {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }

    for (int round = 1; round <= numRounds; round++) {
        cout << endl << "Round " << round << endl;
        int wordnum = randInt(0, nWords - 1);
        
        cout << "The secret word is " << strlen(wordList[wordnum]) << " letters long." << endl;
        int tries = runOneRound(wordList, nWords, wordnum);

        // terminate program if the runOneRound function spits out an error
        if (tries == -1){
            return 0;
        }


        // update min, max, and average (computed later)
        totalTries += tries;
        if (tries < minTries)
        {
            minTries = tries;
        }
        if (tries > maxTries)
        {
            maxTries = tries;
        }
        if (tries != 1) {
            cout << "You got it in " << tries << " tries." << endl;
            
        }
        else {
            cout << "You got it in 1 try." << endl;
            
        }
        
        cout << "Average: " << fixed << setprecision(2) << totalTries / round << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
    }
}



