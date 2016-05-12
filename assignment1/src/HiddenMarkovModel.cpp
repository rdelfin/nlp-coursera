//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#include "assignment1/HiddenMarkovModel.hpp"

#include <iostream>
#include <iterator>


HiddenMarkovModel::HiddenMarkovModel(std::unordered_multimap<std::string, size_t>& textToWord,
                                     std::unordered_multimap<int, size_t>& tagToWord,
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

double trigamProb(Tag curr, Tag prev, Tag twoPrev){

}

double HiddenMarkovModel::emission(Tag tag, const std::string& word) {
    long tagCount = countTag(tag);
    long wordTagCount = countTagWord(tag, word);
    long wordCount = countWord(word);
    // Avoid division by zero.
    if(tagCount == 0) return 0;

    // In this case, make use of the RARE words

    if(wordCount < 5 && wordCount > 0) {
        std::cout << "Word count is less than 5 and not zero. This should not happen. Check word " << word << std::endl;
    }

    if(wordCount == 0) {
        return (double) countTagWord(tag, "_RARE_") / tagCount;
    }
    else
        return (double)wordTagCount / tagCount;
}

long HiddenMarkovModel::countWord(const std::string& word) {
    long count = 0;

    auto range = textToWord.equal_range(word);

    for(auto it = range.first; it != range.second; ++it) {
        count += words[it->second].count;
    }

    return count;
}

long HiddenMarkovModel::countTag(Tag tag) {
    long count = 0;


    tagToWord.count(tag);
    auto range = tagToWord.equal_range(tag);

    for(auto it = range.first; it != range.second; ++it) {
        count += words[it->second].count;
    }

    return count;
}

long HiddenMarkovModel::countTagWord(Tag tag, const std::string& word) {
    long count = 0;

    // Logic tells us each word will have less entries than the tags
    auto range = textToWord.equal_range(word);

    for (auto it = range.first; it != range.second; ++it)
        if(words[it->second].tag == tag)
            count += words[it->second].count;

    return count;
}


long countNgram(std::vector<Tag> tags) {
    for(auto it = ngrams.begin(); it != ngrams.end(); ++it) {
        if(it->terms.size() == tags.size()) {

            // Check if the current ngram is a match
            bool match = true;
            for(int i = 0; i < tags.size(); i++) {
                if(it->terms[i] != tags[i]) {
                    match = false;
                    break;
                }
            }

            // If so, return count
            if(match)
                return it->count;
        }
    }

    // Ngram was not found. Return 0
    return 0;
}


HiddenMarkovModel::~HiddenMarkovModel() {

}

