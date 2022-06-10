#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <string>
#include <algorithm>
#include <assert.h>

#include "dictionary.h"

//TODO Add consts and & to function calls
Dictionary::Dictionary()
{
    // TODO parametetize
    ReadWordFile("../words.txt");
    _targetword = SelectWord();
    // TODO drive based on command line parameter
    std::cout << "Target word: " << _targetword << std::endl;
}

// Read file of words into the _words vector
void Dictionary::ReadWordFile(std::string path)
{
    std::ifstream wordfile(path);
    assert(wordfile.is_open());
    if (wordfile.is_open())
    {
        std::string word;
        while (std::getline(wordfile, word))
        {
            // Reject words not meeting the wordlength
            if (word.length() == Wordlength)
                _words.emplace_back(Uppercase(word));
        }
        wordfile.close();
    }
}

//Generate random word from the vector of words
std::string Dictionary::SelectWord()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> distrib(0, _words.size() - 1);
    return _words[distrib(gen)];
}

// Return the word in uppercase
std::string Dictionary::Uppercase(std::string word)
{
    std::transform(word.begin(), word.end(), word.begin(), ::toupper);
    return word;
}

// Check the word exists in our vector of words, effectively spell check
bool Dictionary::ValidWord(std::string word)
{
    // I find this method easier to understand than std::find_if when using a vector of pointers.
    for (auto &w : _words)
    {
        if (w == word)
            return true;
    }
    return false;
}

// Evaluate the completed word from the turn to the _target word
// Return a vector of ints, one for each letter in the word
// 0 = letter was not in the target word
// 1 = letter was in the target word but not in the correct location
// 2 = The letter was in the correct position
// The algorthm will account only once for each letter
std::vector<int> Dictionary::CompareWord(std::string word)
{
    std::string answer = _targetword;

    // Populate the result with all zero's assume no letters are correct
    std::vector<int> result = {0, 0, 0, 0, 0};

    // First cycle through the word and answer to eliminate any letters in the correct location
    for (int i = 0; i < Wordlength; i++)
    {
        if (word[i] == answer[i])
        {
            result[i] = 2;
            word[i] = '-';          // Use a - char as a replacement in word
            answer[i] = '+';        // Use a + char as a different char for a replacement in answer
        }
    }

    // Second cycle through word to find remaining characters in answer but in the wrong place
    for (int i = 0; i < Wordlength; i++)
    {
        for (int j = 0; j < Wordlength; j++)
        {
            if (word[i] == answer[j])
            {
                result[i] = 1;
                answer[j] = '+';  
                break;
            }
        }
    }
    return result;
}
