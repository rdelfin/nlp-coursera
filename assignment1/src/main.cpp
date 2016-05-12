//
// Created by Ricardo Delfin Garcia on 5/7/16.
//

#include <iostream>
#include <unordered_map>
#include <vector>

#include <assignment1/HiddenMarkovModel.hpp>
#include <fstream>
#include <assignment1/Tagger.hpp>

#include "assignment1/DataParser.hpp"
#include "assignment1/Data.hpp"

int main(int argc, char* argv[])
{
    std::unordered_multimap<std::string, size_t> textToWord;
    std::unordered_multimap<int, size_t> tagToWord;
    std::vector<Ngram> ngrams;
    std::vector<Word> words;

    std::ifstream devFile("data/gene.dev");
    std::ofstream resultFile("data/gene.dev.results");

    DataParser parser(textToWord, tagToWord, ngrams, words);
    HiddenMarkovModel hmm(textToWord, tagToWord, ngrams, words);
    Tagger tagger(hmm, devFile, resultFile);

    parser.parse("data/gene.train.count");
    parser.dump("data/datadump");
    tagger.tag();

    return 0;
}
