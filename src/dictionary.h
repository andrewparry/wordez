#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <vector>
#include <memory>
#include <string>

// Distionary object contains all the logic to manage words
class Dictionary
{
public:
    Dictionary();     
    std::string SelectWord();                                      // Select the target word
    std::string GetTargetWord() { return _targetword; };    // Return the target word
    bool ValidWord(std::string word);                       // Validate the spelling on a turn against the vector of words
    std::vector<int> CompareWord(std::string word);         // Compare given word with the target word

private:
    void ReadWordFile(std::string path);                    // Readfile of words words into vector _words
    std::string Uppercase(std::string word);                // Convert word to uppercase, game runs in uppercase
    std::vector<std::string> _words;                        // Vector of words
    const int Wordlength = 5;                               // The maximum letters in a word
    std::string _targetword;                                // The targetword
};

#endif /* DICTIONARY_H */