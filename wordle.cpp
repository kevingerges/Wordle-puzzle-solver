// Definition of primary wordle function
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
// #include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findWords(const string& in, const string& floating, const set<string>& dict, set<string>& words);



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> wordsList;
    findWords(in, floating, dict, wordsList);
    return wordsList;
}

// Define any helper functions here

void findWords(const string& in, const string& floating, const set<string>& dict, set<string>& words)
{
    if (in.find("-") == string::npos) // Found complete word
    {
        if (dict.find(in) != dict.end())
        {
            words.insert(in);
        }
    }
    else // Need to fill in blanks
    {
        string newFloating = floating;
        if (!floating.empty())
        {
            char c = floating[0];
            newFloating = floating.substr(1);
            set<size_t> indices;
            for (size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] == '-')
                {
                    indices.insert(i);
                }
            }
            for (const auto& index : indices)
            {
                string newIn = in;
                newIn[index] = c;
                findWords(newIn, newFloating, dict, words);
            }
        }
        else // No floating letters left
        {
            for (char c = 'a'; c <= 'z'; ++c)
            {
                set<size_t> indices;
                for (size_t i = 0; i < in.size(); ++i)
                {
                    if (in[i] == '-')
                    {
                        indices.insert(i);
                    }
                }
                for (const auto& index : indices)
                {
                    string newIn = in;
                    newIn[index] = c;
                    findWords(newIn, "", dict, words);
                }
            }
        }
    }
}
