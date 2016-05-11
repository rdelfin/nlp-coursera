//
// Created by rdelfin on 5/8/16.
//

#pragma once



#include <unordered_map>
#include <string>

#include "assignment1/Data.hpp"

class HiddenMarkovModel {
public:
    HiddenMarkovModel(std::unordered_multimap<std::string, size_t>&,
                      std::unordered_multimap<int, size_t>&,
                      std::vector<Ngram>&, std::vector<Word>&);

    Tag predict(const std::string& word);

    double emission(Tag, const std::string& word);

    ~HiddenMarkovModel();
private:
    std::unordered_multimap<std::string, size_t>& textToWord;
    std::unordered_multimap<int, size_t>& tagToWord;
    std::vector<Ngram>& ngrams;
    std::vector<Word>& words;

    long countWord(const std::string& word);
    long countTagWord(Tag, const std::string& word);
    long countTag(Tag);
};
