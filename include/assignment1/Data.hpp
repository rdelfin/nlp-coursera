//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#pragma once

#include <string>
#include <vector>

typedef enum {
    O,
    I_GENE,
    START,
    END
} Tag;

class Word {
public:
    int count;
    Tag tag;
    std::string name;
};

class Ngram {
public:
    std::vector<Tag> terms;
};