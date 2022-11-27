// WritingAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Program takes in a text file and outputs technical information about the writing. 
// This includes word count, average word length, sentence count, average sentence length, 
// longest word and longest sentence as well as top 10 most used words

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

// Helper
bool is_alpha(char c)
{
    if ((c > 64 && c < 91) || (c > 96 && c < 123))
    {
        return true;
    }

    return false;
}

// Primary function (make sure file is properly encoded)
void checkText(std::string filename)
{
    std::fstream file;
    file.open(filename, std::ios::in);

    std::string oneLine;
    int word_count = 0;
    int sentance_count = 0;
    int longest_word = 0;
    int longest_sentance = 0;
    int char_count = 0;
    std::string longest_word_as_string = "a";
    std::map<std::string, int> occMap; // count occurrences


    while (getline(file, oneLine))  // deal with data in string
    {
        std::string word_to_build = "";

        for (unsigned int i = 0; i < oneLine.length(); i++) // loop through string
        {
            if (is_alpha(oneLine[i]) == true) // build each word
            {
                word_to_build += oneLine[i];
            }

            if (oneLine[i] == ' ') // found word
            { 
                word_count++; 

                boost::algorithm::to_lower(word_to_build);
                
                if (word_to_build.size() >= longest_word_as_string.size()) // check for largest word
                {
                    longest_word_as_string = word_to_build; 
                }

                if (occMap.count(word_to_build) == 0) // add word to map
                {
                    occMap.insert(std::pair<std::string, int>(word_to_build, 1));
                }
                else if (occMap.count(word_to_build) != 0)
                {
                    occMap[word_to_build] += 1;
                }

                word_to_build = "";
            }

            if (oneLine[i] == '.' || oneLine[i] == '!' || oneLine[i] == '?') { sentance_count++; }
            if (oneLine[i] != ' ') { char_count++; }
        }

        if (oneLine.size() != 0)
        {
            word_count++;
        }
    }

    std::cout << "Word Count: " << word_count << std::endl;
    std::cout << "Char Count (no spaces): " << char_count << std::endl;
    std::cout << "Sentance Count: " << sentance_count << std::endl;
    std::cout << "Avg words per sentance (rounded): " << word_count / sentance_count << std::endl;
    std::cout << "Longest word was " << longest_word_as_string.size() << " chars long: " 
        << longest_word_as_string << std::endl;

    // get top n values from the map
    // ++++++++++++++++++ Credit hmjd on stackoverflow ++++++++++++++++++++++++
    // https://stackoverflow.com/questions/17963905/how-can-i-get-the-top-n-keys-of-stdmap-based-on-their-values

    std::vector<std::pair<std::string, int>> top_four(10);
    std::partial_sort_copy(occMap.begin(),
        occMap.end(),
        top_four.begin(),
        top_four.end(),
        [](std::pair<const std::string, int> const& l,
            std::pair<const std::string, int> const& r)
        {
            return l.second > r.second;
        });

    std::cout << "9 most common words:" << std::endl;

    int count = 1;
    for (auto const& p : top_four)
    {
        std::cout << count << ": [" << p.first << ", " << p.second << "]\n";
        count++;
    }

    // ++++++++++++++++++++++++++++ End Credit +++++++++++++++++++++++++++++++

    return;
}

int main()
{
    checkText("filename here");

    return 0;
}


