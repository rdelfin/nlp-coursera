//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "assignment1/Data.hpp"

class DataParser {
public:
    DataParser(std::unordered_multimap<std::string, Word*>&,
               std::unordered_multimap<int, Word*>&,
               std::vector<Ngram>&,
               std::vector<Word>&);

    void parse(const std::string& fileName);
    void parse(std::istream&);



    ~DataParser();

private:
    std::unordered_multimap<std::string, Word*>& textToWord;
    std::unordered_multimap<int, Word*>& tagToWord;
    std::vector<Ngram>& ngrams;
    std::vector<Word>& words;
};
