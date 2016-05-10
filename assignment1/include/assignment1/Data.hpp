//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#pragma once

#include <string>
#include <vector>

typedef enum {
    TAG_O,
    TAG_I_GENE,
    TAG_START,
    TAG_STOP,
    TAG_UNKNOWN
} Tag;

class Word {
public:
    Word() : count(0), tag(TAG_O), name("") { }
    int count;
    Tag tag;
    std::string name;
};

class Ngram {
public:
    Ngram() : count(0), terms() { }
    std::vector<Tag> terms;
    int count;
};

static Tag parseTag(const std::string& str) {
    if(str == "O") return TAG_O;
    if(str == "I-GENE") return TAG_I_GENE;
    if(str == "*") return TAG_START;
    if(str == "STOP") return TAG_STOP;

    return TAG_UNKNOWN;
}

static std::string stringTag(Tag tag) {
    switch (tag) {
        case TAG_O: return "O";
        case TAG_I_GENE: return "I-GENE";
        case TAG_START: return "*";
        case TAG_STOP: return "STOP";
    }

    return "";
}