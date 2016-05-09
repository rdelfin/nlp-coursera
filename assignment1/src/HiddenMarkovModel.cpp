//
// Created by rdelfin on 5/8/16.
//

#include "assignment1/HiddenMarkovModel.hpp"



double HiddenMarkovModel::emission(Tag tag, const std::string& word) {
    long tagCount = countTag(tag);

    // Avoid division by zero.
    if(tagCount == 0) return 0;

    return (double)countTagWord(tag, word) / tagCount;
}

long HiddenMarkovModel::countTag(Tag tag) {
    return tagToWord.count(tag);
}

long HiddenMarkovModel::countTagWord(Tag tag, const std::string &word) {
    long count = 0;

    // Logic tells us each word will have less entries than the tags
    auto range = textToWord.equal_range(word);

    for (auto it = range.first; it != range.second; ++it)
        if(it->second->tag == tag)
            count++;

    return count;
}