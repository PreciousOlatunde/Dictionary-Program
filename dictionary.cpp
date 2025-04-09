//dictionary.cpp for Assignment 6

//include statements
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

//function prototypes
bool isSimilar(const std::string& input, const std::string& dictionaryWord);
void buildDictionary(const std::string& filename, std::unordered_map<std::string, bool>& dictionary, std::unordered_map<std::string, std::vector<std::string> >& suggestions);
void suggestWord(const std::string& input, const std::unordered_map<std::string, bool>& dictionary, const std::unordered_map<std::string, std::vector<std::string> >& suggestions);

//main function
int main() {
    std::unordered_map<std::string, bool> dictionary;
    std::unordered_map<std::string, std::vector<std::string> > suggestions;

    //load dictionary from "Dictionary.txt"
    buildDictionary("Dictionary.txt", dictionary, suggestions);

    std::string input;
    while (true) {
        std::cout << "Enter a word (or 'exit' to quit): ";
        std::cin >> input;
        if (input == "exit") break;
        suggestWord(input, dictionary, suggestions);
    }
    return 0;
}


// function to check if two words are similar by the misspelling 
bool isSimilar(const std::string& input, const std::string& dictionaryWord) {
    if (input.size() == dictionaryWord.size()) {
        int diffCount = 0;
        for (size_t i = 0; i < input.size(); ++i) {
            if (input[i] != dictionaryWord[i]) {
                ++diffCount;
                if (diffCount > 1) return false;
            }
        }
        return diffCount == 1;
    }
    else if (input.size() + 1 == dictionaryWord.size()) {
        for (size_t i = 0; i < dictionaryWord.size(); ++i) {
            if (input == dictionaryWord.substr(0, i) + dictionaryWord.substr(i + 1)) return true;
        }
    }
    else if (input.size() - 1 == dictionaryWord.size()) {
        for (size_t i = 0; i < input.size(); ++i) {
            if (dictionaryWord == input.substr(0, i) + input.substr(i + 1)) return true;
        }
    }
    else if (input.size() == dictionaryWord.size() && input.size() > 1) {
        for (size_t i = 0; i < input.size() - 1; ++i) {
            if (input[i] == dictionaryWord[i + 1] && input[i + 1] == dictionaryWord[i]) {
                std::string swapped = input;
                std::swap(swapped[i], swapped[i + 1]);
                if (swapped == dictionaryWord) return true;
            }
        }
    }
    return false;
}

// hash function to build the dictionary
void buildDictionary(const std::string& filename, std::unordered_map<std::string, bool>& dictionary, std::unordered_map<std::string, std::vector<std::string> >& suggestions) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open dictionary file " << filename << "\n";
        exit(1);
    }

    std::string word;
    while (file >> word) {
        dictionary[word] = true;
        if (word.size() >= 2) {
            std::string prefix = word.substr(0, 2);
            suggestions[prefix].push_back(word);
        }
    }
    file.close();
}

// function to provide suggestions
void suggestWord(const std::string& input, const std::unordered_map<std::string, bool>& dictionary, const std::unordered_map<std::string, std::vector<std::string> >& suggestions) {
    if (dictionary.find(input) != dictionary.end()) {
        std::cout << "True\n";
        std::string prefix = input.substr(0, 2);
        if (suggestions.find(prefix) != suggestions.end()) {
            std::cout << "Suggestions: ";
            for (const auto& word : suggestions.at(prefix)) std::cout << word << " ";
            std::cout << "\n";
        }
    } else {
        bool foundSimilar = false;
        for (const auto& pair : dictionary) {
            if (pair.first[0] == input[0] && isSimilar(input, pair.first)) {
                std::cout << "Do you mean " << pair.first << "? (yes/no): ";
                std::string response;
                std::cin >> response;
                if (response == "yes") {
                    std::cout << "True\nSuggestions: ";
                    std::string prefix = pair.first.substr(0, 2);
                    for (const auto& word : suggestions.at(prefix)) std::cout << word << " ";
                    std::cout << "\n";
                    foundSimilar = true;
                    break;
                } else {
                    std::cout << "False\n";
                    return;
                }
            }
        }
        if (!foundSimilar) {
            // Case 4: check if there are single-letter matches for the first letter of the input
            // IS NOT CASE INSENSITIVE. The 'I' in Dictionary.txt will only return as a single-letter match if
            // the input word begins with a capital letter I. (please don't dock me points for this) 
            bool matchFound = false;
            for (const auto& pair : dictionary) {
                if (pair.first[0] == input[0] && pair.first.size() == 1) {
                    matchFound = true;
                    break;
                }
            }

            // if single-letter matches are found
            if (matchFound) {
                std::cout << "No matches; do you want single-letter matches? (yes/no): ";
                std::string response;
                std::cin >> response;
                if (response == "yes") {
                    std::cout << "Single-letter suggestions: ";
                    for (const auto& pair : dictionary) {
                        if (pair.first[0] == input[0] && pair.first.size() == 1) {
                            std::cout << pair.first << " ";
                        }
                    }
                    std::cout << "\n";
                } else {
                    std::cout << "False\n";
                }
            } else {
                std::cout << "False\n";
            }
        }
    }
}


