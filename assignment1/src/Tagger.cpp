//
// Created by Ricardo Delfin Garcia on 5/10/16.
//

#include "assignment1/Tagger.hpp"

Tagger::Tagger(HiddenMarkovModel& hmm, std::istream& input_stream, std::ostream& output_stream)
        : hmm(hmm), input_stream(input_stream), output_stream(output_stream)
{

}

void Tagger::tag() {
    std::string line;
    getline(input_stream, line);

    while(!input_stream.eof()) {
        if(line != "") {
            Tag tag = hmm.predict(line);
            output_stream << line << " " << stringTag(tag);
        }

        output_stream << std::endl;
        getline(input_stream, line);
    }
}

Tagger::~Tagger() {

}