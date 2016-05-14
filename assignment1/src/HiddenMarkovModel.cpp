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


std::vector<Tag> HiddenMarkovModel::predict(const std::vector<std::string> &sentence) {
    // These are the set of tags that each word can take on
    std::vector<Tag> Sstart = {TAG_START};
    std::vector<Tag> Sgeneral = {TAG_O, TAG_I_GENE};

    // This map is the dynamic programming table Pi(Pos, Prev, Curr)
    // This also inserts the basecase: Pi(0, *, *) = 1
    std::unordered_map<PiData, double, PiDataHash> pi;
    pi.insert({{-1, TAG_START, TAG_START}, 1});


    std::vector<Tag> result;

    for(int i = 0; i < sentence.size(); i++) {
        const std::vector<Tag>& Stwoprev = ((i - 2) < 0 ? Sstart : Sgeneral);
        const std::vector<Tag>& Sprev = ((i - 1) < 0 ? Sstart : Sgeneral);
        const std::vector<Tag>& Scurr = (i < 0 ? Sstart : Sgeneral);
        for(auto itprev = Sprev.begin(); itprev != Sprev.end(); ++itprev) {
            for(auto itcurr = Scurr.begin(); itcurr != Scurr.end(); ++itcurr) {
                // Calculate Pi(i,itprev, itcurr) = max w(Pi(i-1,w,itprev)*q(itcurr|w,itprev)*e(x_i|itcurr)
                result.push_back(getBestTag(pi, Stwoprev, i, *itprev, *itcurr, sentence[i]));
            }
        }
    }

    return result;
}

Tag HiddenMarkovModel::getBestTag(std::unordered_map<PiData, double, PiDataHash>& pi, const std::vector<Tag>& s, int loc, Tag prev, Tag curr, std::string word) {
    double max = 0;
    Tag maxTag = TAG_UNKNOWN;

    for(int i = 0; i < s.size(); i++) {
        double val = pi[{loc- 1, s[i], prev}] * trigramProb(curr, s[i], prev) * emission(curr, word);

        if(val >= max) {
            max = val;
            maxTag = s[i];
        }
    }

    pi.insert({{loc, prev, curr}, max});

    return maxTag;
}

double HiddenMarkovModel::trigramProb(Tag curr, Tag twoPrev, Tag prev) {
    long trigram = countNgram({twoPrev, prev, curr});
    long bigram = countNgram({twoPrev, prev});

    if(bigram == 0) return 0;

    return (double)trigram / bigram;
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


long HiddenMarkovModel::countNgram(const std::vector<Tag>& tags) {
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

