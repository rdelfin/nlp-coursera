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

    std::vector<Tag> predict(const std::vector<std::string>& word);

    double emission(Tag, const std::string& word);
    // Computes p(curr|twoPrev,prev)
    double trigamProb(Tag curr, Tag twoPrev, Tag prev);

    ~HiddenMarkovModel();
private:
    std::unordered_multimap<std::string, size_t>& textToWord;
    std::unordered_multimap<int, size_t>& tagToWord;
    std::vector<Ngram>& ngrams;
    std::vector<Word>& words;

    long countWord(const std::string& word);
    long countTagWord(Tag, const std::string& word);
    long countTag(Tag);

    // Counts up all instances of trigram <tag1 tag2 tag3>
    long countNgram(const std::vector<Tag>& tags);
};
