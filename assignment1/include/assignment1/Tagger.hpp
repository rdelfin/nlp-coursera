//
// Created by Ricardo Delfin Garcia on 5/10/16.
//

#pragma once

#include <iostream>

#include <assignment1/HiddenMarkovModel.hpp>

class Tagger {
public:
    Tagger(HiddenMarkovModel&, std::istream&, std::ostream&);

    void tag();

    ~Tagger();
private:
    HiddenMarkovModel& hmm;
    std::istream& input_stream;
    std::ostream& output_stream;
};

