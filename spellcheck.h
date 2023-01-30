#pragma once
#include "HashTable.h"
#include <algorithm>
#include <vector>

using std::sort;
using std::vector;

// function prototypes
vector<string> extraLetter(const HashTable& dict, string word);
vector<string> transposition(const HashTable& dict, string word);
vector<string> missingSpace(const HashTable& dict, string word);
vector<string> missingLetter(const HashTable& dict, string word);
vector<string> incorrectLetter(const HashTable& dict, string word);

// helper function prototype for transposition function
void swap(string& word, int i, int j);

// returns all strings than can be found in dict by removing one letter from the string parameter
vector<string> extraLetter(const HashTable& dict, string word)
{
	vector<string> correctWords;

	// the word is in the dict already insert it into the correctwords vector and return it
	if(dict.find(word) == true){
		correctWords.push_back(word);
		return correctWords;
	}else{
		// for every letter in the word try removing that letter to find a correctword
		for(int i = 0; i < word.size(); i++){
			string correctWord = word;
			// removes 1 letter from the word that letter being the ith letter 
			correctWord.erase(i, 1);

			// checks to see if the correctWord has already been added to the vector of correctWords
			vector<string>::iterator it = find(correctWords.begin(), correctWords.end(), correctWord);
			// if not in the vector of correctwords and in the dict than insert
			// the correctword into correctwords
			if(it == correctWords.end() && dict.find(correctWord)){
				correctWords.push_back(correctWord);
			}
		}
	}

	// sorts the vector before returning it
	sort(correctWords.begin(), correctWords.end());

	return correctWords;
}

// helper swap function: swaps the chars at two parts of the string
void swap(string& word, int i, int j)
{
	char temp = word.at(i);
	word.at(i) = word.at(j);
	word.at(j) = temp;
}

// returns all strings than can be found in dict by swapping two adjecent letters from the string parameter
vector<string> transposition(const HashTable& dict, string word)
{
	vector<string> correctWords;

	// the word is in the dict already insert it into the correctwords vector and return it
	if(dict.find(word) == true){
		correctWords.push_back(word);
		return correctWords;
	}else{
		// at every position except the last of the string swap it with the char to its right
		for(int i = 0; i < word.size() - 1; i++){
			string correctWord = word;
			// swaps the current letter to the letter to its right
			swap(correctWord, i, i+1);

			// checks to see if the correctWord has already been added to the vector of correctWords
			vector<string>::iterator it = find(correctWords.begin(), correctWords.end(), correctWord);
			// if not in the vector of correctwords and in the dict than insert
			// the correctword into correctwords
			if(it == correctWords.end() && dict.find(correctWord)){
				correctWords.push_back(correctWord);
			}
		}
	}

	// sorts the vector before returning it
	sort(correctWords.begin(), correctWords.end());

	return correctWords;
}

// returns all strings than can be found in dict by adding one space into the string parameter
// and both substring seperated by the space are in the dict
vector<string> missingSpace(const HashTable& dict, string word)
{
	vector<string> correctWords;

	// the word is in the dict already insert it into the correctwords vector and return it
	if(dict.find(word) == true){
		correctWords.push_back(word);
		return correctWords;
	}else{
		// for every position in the word try inserting a space
		for(int i = 0; i < word.size(); i++){
			string correctWord = word;
			// inserts a space at the current position
			correctWord.insert(i, " ");

			// using the index of the space as a divider seperate the string into 2 substrings
			string part1 = correctWord.substr(0, i);
			string part2 = correctWord.substr(i+1);

			// checks if both substrings of the correctword is in the dict
			if(dict.find(part1) && dict.find(part2)){
				// if not in the vector of correctwords then inserts it into the vector
				vector<string>::iterator it = find(correctWords.begin(), correctWords.end(), correctWord);
				if(it == correctWords.end()){
					correctWords.push_back(correctWord);
				}
			}
		}
	}

	// sorts the vector before returning it
	sort(correctWords.begin(), correctWords.end());

	return correctWords;
}

// returns all strings than can be found in dict by adding one letter to the string parameter
vector<string> missingLetter(const HashTable& dict, string word)
{
	vector<string> correctWords;

	// the word is in the dict already insert it into the correctwords vector and return it
	if(dict.find(word) == true){
		correctWords.push_back(word);
		return correctWords;
	}else{
		string character = "a";
		// for all characters in the alphabet try inserting into the word
		for(int letter = 0; letter < 26; letter++){
			// finds a position to insert the character into the string at for every possible position
			for(int i = 0; i < word.size() + 1; i++){
				string correctWord = word;

				// inserts the character into the string at the current position
				correctWord.insert(i, character);

				// checks to see if the correctWord has already been added to the vector of correctWords
				vector<string>::iterator it = find(correctWords.begin(), correctWords.end(), correctWord);
				// if not in the vector of correctwords and in the dict than insert
				// the correctword into correctwords
				if(it == correctWords.end() && dict.find(correctWord)){
					correctWords.push_back(correctWord);
				}			
			}
			// increments the chracter i.e a->b b->c etc.
			character.at(0) += 1;
		}
	}

	// sorts the vector before returning it
	sort(correctWords.begin(), correctWords.end());

	return correctWords;
}

// returns all strings than can be found in dict by changing one letter from the string parameter
vector<string> incorrectLetter(const HashTable& dict, string word)
{
	vector<string> correctWords;

	// the word is in the dict already insert it into the correctwords vector and return it
	if(dict.find(word) == true){
		correctWords.push_back(word);
		return correctWords;
	}else{
		// goes through every letter in the word
		for(int i = 0; i < word.size(); i++){
			string character = "a";
			// for ever letter in the word replace and check it with every possible letter
			for(int letter = 0; letter < 26; letter++){
				string correctWord = word;
				// replaces the letter in the string at i with the character
				correctWord.replace(i, 1, character);

				// checks to see if the correctWord has already been added to the vector of correctWords
				vector<string>::iterator it = find(correctWords.begin(), correctWords.end(), correctWord);
				// if not in the vector of correctwords and in the dict than insert
				// the correctword into correctwords
				if(it == correctWords.end() && dict.find(correctWord)){
					correctWords.push_back(correctWord);
				}
				
				// increments the chracter i.e a->b b->c etc.
				character.at(0) += 1;	
			}
		}
	}

	// sorts the vector before returning it
	sort(correctWords.begin(), correctWords.end());

	return correctWords;
}