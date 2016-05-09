//
// Created by rdelfin on 5/8/16.
//

#pragma once



#include <unordered_map>
#include <string>

#include "assignment1/Data.hpp"

class HiddenMarkovModel {
public:
    double emission(Tag, const std::string& word);
private:
    std::unordered_multimap<std::string, Word*>& textToWord;
    std::unordered_multimap<int, Word*>& tagToWord;
    std::vector<Ngram>& ngrams;
    std::vector<Word>& words;

    long countTagWord(Tag, const std::string& word);
    long countTag(Tag);
};
