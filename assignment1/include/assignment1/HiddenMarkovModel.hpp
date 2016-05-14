//
// Created by rdelfin on 5/8/16.
//

#pragma once



#include <unordered_map>
#include <string>

#include "assignment1/Data.hpp"

class PiData {
public:
    int loc;
    Tag prev;
    Tag curr;

    bool operator==(const PiData& data) const {
        return loc == data.loc && prev == data.prev && curr == data.curr;
    }
};

// Pidata hash function
class PiDataHash {
public:
    size_t operator()(const PiData& data) const
    {
        /* your code here, e.g. "return hash<int>()(x.value);" */
        return (data.loc + (size_t)data.prev + (size_t)data.curr)*2654435761 % 1<<16;
    }
};


class HiddenMarkovModel {
public:
    HiddenMarkovModel(std::unordered_multimap<std::string, size_t>&,
                      std::unordered_multimap<int, size_t>&,
                      std::vector<Ngram>&, std::vector<Word>&);

    std::vector<Tag> predict(const std::vector<std::string>& word);

    double emission(Tag, const std::string& word);
    // Computes p(curr|twoPrev,prev)
    double trigramProb(Tag curr, Tag twoPrev, Tag prev);

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


    Tag getBestTag(std::unordered_map<PiData, double, PiDataHash>& pi, const std::vector<Tag>& s, int loc, Tag prev, Tag curr, std::string word);
};

