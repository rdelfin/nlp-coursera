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
    DataParser(std::unordered_multimap<std::string, size_t>&,
               std::unordered_multimap<int, size_t>&,
               std::vector<Ngram>&,
               std::vector<Word>&);

    void parse(const std::string& fileName);
    void parse(std::istream&);

    void dump(const std::string& file);

    ~DataParser();

private:
    std::unordered_multimap<std::string, size_t>& textToWord;
    std::unordered_multimap<int, size_t>& tagToWord;
    std::vector<Ngram>& ngrams;
    std::vector<Word>& words;
};
