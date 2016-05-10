//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#include "assignment1/HiddenMarkovModel.hpp"

#include <iostream>
#include <iterator>


HiddenMarkovModel::HiddenMarkovModel(std::unordered_multimap<std::string, Word>& textToWord,
                                     std::unordered_multimap<int, Word>& tagToWord,
                                     std::vector<Ngram>& ngrams,
                                     std::vector<Word>& words)
                                    : textToWord(textToWord), tagToWord(tagToWord),
                                      ngrams(ngrams), words(words)
{

}


Tag HiddenMarkovModel::predict(const std::string &word) {
    double max = 0;
    Tag result = TAG_O;
    for(int i = TAG_O; i <= TAG_UNKNOWN; i++) {
        double pred = emission((Tag)i, word);
        if(pred > max) {
            max = pred;
            result = (Tag)i;
        }
    }

    return result;
}

double HiddenMarkovModel::emission(Tag tag, const std::string& word) {
    long tagCount = countTag(tag);

    // Avoid division by zero.
    if(tagCount == 0) return 0;

    return (double)countTagWord(tag, word) / tagCount;
}

long HiddenMarkovModel::countWord(const std::string& word) {
    long count = 0;

    auto range = textToWord.equal_range(word);

    for(auto it = range.first; it != range.second; ++it) {
        count += it->second.count;
    }

    return count;
}

long HiddenMarkovModel::countTag(Tag tag) {
    long count = 0;


    tagToWord.count(tag);
    auto range = tagToWord.equal_range(tag);

    for(auto it = range.first; it != range.second; ++it) {
        count += it->second.count;
    }

    return count;
}

long HiddenMarkovModel::countTagWord(Tag tag, const std::string& word) {
    long count = 0;

    // Logic tells us each word will have less entries than the tags
    auto range = textToWord.equal_range(word);

    for (auto it = range.first; it != range.second; ++it)
        if(it->second.tag == tag)
            count += it->second.count;

    return count;
}

HiddenMarkovModel::~HiddenMarkovModel() {

}