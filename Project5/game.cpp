//
//  main.cpp
//  Project 5
//
//  Created by Kai Perez on 11/4/22.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include "utilities.h"

using namespace std;

const char WORDFILENAME[] = "/Users/kaiperez/desktop/CS31/Project5/words.txt";


int matchGold (const char hiddenWord [], const char probeWord []){
    int counter = 0;
    if (strcmp(hiddenWord, probeWord) == 0)
        return 7;                           //they guessed the word correctly
    for (int k = 0; k < strlen(hiddenWord); k++){
        if (hiddenWord[k] == probeWord[k])      //matching letters add to gold
            counter++;
    }
    return counter;
}



int matchSilver (const char hiddenWord [], const char probeWord []){
    int counterAll = 0;
    int counterGold = 0;
    int hiddenWordRepeat = 0;
    int probeWordRepeat = 0;
    
    
    for (int k = 0; k < strlen(hiddenWord); k++){
        for (int i = 1; i < strlen(hiddenWord) - k ; i++){  //counts # of letter repeats hiddenword
            if (hiddenWord[k] == hiddenWord[k+i]){
                for (int j = 0; j < strlen(probeWord); j++){
                    if (hiddenWord[k] == probeWord[j]){
                        hiddenWordRepeat++;
                        break;
                    }
                }
                break;
            }
        }
        
        for (int i = 1; i < strlen(probeWord) - k ; i++){  //counts # of letter repeats probeword
            if (probeWord[k] == probeWord[k+i] ){
                probeWordRepeat++;
                break;
            }
        }
    }
    
    for (int k = 0; k < strlen(hiddenWord); k++){
        
        if (hiddenWord[k] == probeWord[k]){      //matching letters gold go to counter
            counterGold++;
        }
        for (int i = 0; i < strlen(probeWord); i++){
            if (hiddenWord[k] == probeWord[i]){ //matching letters any pos go to counter
                counterAll++;
                break;
                        }
                    }
                }
    
    if (hiddenWordRepeat > probeWordRepeat){   //if hiddenwordrepeatingletters > than subtract
        counterAll = counterAll - (hiddenWordRepeat - probeWordRepeat);
    }
    
    return (counterAll - counterGold);
    //matching letters all - matching letters same pos (gold)
}



void averageCalcs (int scores [], int nRound){
    cout.setf(ios::fixed);          //setting up to two decimal places
    cout.precision(2);
    
    double average = 0;
    
    for (int k = 0; k < nRound; k++){           //average calcs
        average += scores[k];
    }
    average = (average/nRound);

    
    int minValue = scores[0];
    int maxValue = scores[0];                   //max/min comparisons
    for (int k = 0; k < nRound; k++){
        if (minValue > scores[k]){
            minValue = scores[k];
        }
        if (maxValue < scores[k]){
            maxValue = scores[k];
        }
    }
    cout << "Average: " << average << ", minimum: " << minValue << ", maximum: "
         << maxValue << endl;
   
}


bool isValidWord(const char input[]){
    for (int k = 0; k < strlen(input); k++){ //if not lowercase/alpha return false
        if (input[k] != tolower(input[k]) || (isalpha(input[k]) == 0)){
            return false;
        }
    }
    if (strlen(input) < 4 || strlen(input) > 6){    //if too short/long return false
        return false;}
    
   
    
    return true;
}

bool isValidWordTwo(const char input[]){
    char allWords [9000][7];
    int matchCount = 0;
    int totalWords = getWords(allWords, 9000, WORDFILENAME);
    for(int k = 0; k < totalWords; k++){
        if (strcmp(input, allWords[k]) == 0){
            matchCount++;}
    }
    if (matchCount == 0){               //if no matches with word bank return false
        return false;}
    return true;
}


// reads out score statement in separate function to clean up code
void scoreStatement(const char hiddenWord [], const char probeWord []){
    cout << "Golds: " << matchGold(hiddenWord, probeWord) <<
            ", Silvers: " << matchSilver(hiddenWord, probeWord) << endl;
}




int playOneRound (const char words[][7], int nWords, int wordnum){
    char probeWord[1000];
    int counter = 0;

    //cerr << words[wordnum] << endl; // delete eventually
    
    if (nWords < 0){                //if nWords/wordnum out of range terminate code
        return -1;
    }
    if (wordnum < 0 || wordnum >= nWords){
        return -1;
    }
    
    do{ //get probe word while they haven't guessed the word
        
        cout << "Probe word: ";
        cin.getline(probeWord, 1000, '\n');
            
        if(isValidWord(probeWord) == false){        //for invalid input
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
        }                                           //for invalid input
        if(isValidWordTwo(probeWord) == false && isValidWord(probeWord) == true){
            cout << "I don't know that word." << endl;
            
        }
        
        // if valid input and they havent guessed the word output score statement
        if(isValidWordTwo(probeWord) == true && isValidWord(probeWord) == true){
            if (strcmp(words[wordnum], probeWord) != 0 && isValidWord(probeWord) == true)
                scoreStatement(words[wordnum], probeWord);
            counter++;}                                 //counts rounds needed to guess
    }while(strcmp(words[wordnum], probeWord) != 0);
    
    
    return counter;
   
}







int main(){
    
    char wordList[9000][7];
    int nRounds;
    int nWords;
    int scores[10000];

    
    //checks to make sure words are loaded in to game
    nWords = getWords(wordList, 9000, WORDFILENAME);
    if (nWords < 1){
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }

    
    cout << "How many rounds do you want to play? ";
    cin >> nRounds;
    cin.ignore(10000,'\n');
    if (nRounds < 0){                           //correct input check
        cout << "The number of rounds must be positive." << endl;
        return -1;}
    cout << endl;
    
    
   for (int k = 0; k < nRounds;k++){
       const int random = randInt(0, nWords -1);
       cout << "Round " << (k + 1) << endl;         //output statements w user inputs
       cout << "The hidden word is " << strlen(wordList[random]) << " letters long." << endl;
       
       scores[k] = playOneRound(wordList, nWords, random);
       
       if (scores[k] == -1)       //if wordnum/nWords out of range terminate program
           return -1;
       if (scores[k] == 1)
           cout << "You got it in 1 try." << endl;
       if (scores[k] > 1)
           cout << "You got it in " << scores[k] << " tries." << endl;
       
        averageCalcs(scores, k+1);
        cout << endl;
    }
}


