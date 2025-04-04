/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <algorithm>
#include "console.h"
#include "queue.h"
#include "simpio.h"
#include "vector"
#include "lexicon.h"
#include "set"
using namespace std;

//constant
const string FILENAME = "EnglishWords.dat";

//function prototypes
string getUserInput(string);
bool isValid(const string&);
string findLadder(string&, string&, Lexicon&);
void enqueueAllContinues(string& lastElement, Lexicon& allEnglishWords, set<string>& visitedWords,
    vector<string>& currentLadder, Queue<vector<string>>& allLadders);
string textToPrint(vector<string>& ladder);
bool wordNotAlreadyUsed(set<string>& ladder, string& word);

int main() {
    Lexicon allEnglishWords(FILENAME);
    while (true) {
        string startWord = getUserInput("Enter start word (RETURN to quit) : ");
        if (startWord.empty())break;
        string endWord = getUserInput("Enter destination word: ");
        cout << findLadder(startWord, endWord, allEnglishWords) << endl;
    }
    cout << "You exited Program" << endl;
    return 0;
}

/*
* Makes sure user inputs right string(only 26 letters)
* And our program is not case sensitive so we always
* turn it into lower case with transform function
*/
string getUserInput(string inputText) {
    while (true) {
        string text = getLine(inputText);
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        if (isValid(text)) {
            return text;
        }
        cout << "Enter valid word" << endl;
    }
}

/*
* Checks if string is valid, we pass it with reference
* to take care of memory but also make it static to prevent
* its modification
*/
bool isValid(const string& text) {
    for (char ch : text) {
        if (!isalpha(ch)) {
            return false;
        }
    }
    return true;
}

/*
* Main part of the program, which decides if start word can
* become endWord after proper modifications
*/
string findLadder(string& startWord, string& endWord, Lexicon& allEnglishWords) {
    Queue<vector<string>> allLadders;
    allLadders.enqueue(vector<string>({ startWord })); // we add first element(vector with only startword)
    set<string> visitedWords; // we will use set to make our code faster by avoiding dublicates
    visitedWords.insert(startWord); //we add first element(startword)
    while (!allLadders.isEmpty()) {
        vector<string> currentLadder = allLadders.dequeue();
        string lastElement = currentLadder[currentLadder.size() - 1];
        if (lastElement == endWord) {
            return textToPrint(currentLadder);
        }
        enqueueAllContinues(lastElement, allEnglishWords, visitedWords, currentLadder, allLadders);

    }
    return "No ladder found.";
}

string textToPrint(vector<string>& ladder) {
    string text = "Found ladder: ";
    for (string str : ladder) {
        text += str + " ";
    }
    return text;
}

/*
* This function generates all kinds of strings which differ by one,
* so we make change for every char in string respectively with 26
* different variants. We add it in queue if word is valid english word
*/
void enqueueAllContinues(string& lastElement, Lexicon& allEnglishWords, set<string>& visitedWords,
    vector<string>& currentLadder, Queue<vector<string>>& allLadders) {
    for (int i = 0; i < lastElement.length(); i++) {
        string nextWord = lastElement;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            nextWord[i] = ch;
            if (allEnglishWords.contains(nextWord) &&
                wordNotAlreadyUsed(visitedWords, nextWord)) {
                vector<string> newLadder = currentLadder;
                newLadder.push_back(nextWord);
                allLadders.enqueue(newLadder);
                visitedWords.insert(nextWord);
            }
        }
    }
}

/*
* Our program not to cycle and to function properly
* we need to check if word was not alredy used in vector
*/
bool wordNotAlreadyUsed(set<string>& visitedWords, string& word) {
    return visitedWords.find(word) == visitedWords.end();
}