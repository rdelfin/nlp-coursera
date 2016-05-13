//
// Created by Ricardo Delfin Garcia on 5/10/16.
//

#include "assignment1/Tagger.hpp"

Tagger::Tagger(HiddenMarkovModel& hmm, std::istream& input_stream, std::ostream& output_stream)
        : hmm(hmm), input_stream(input_stream), output_stream(output_stream)
{

}

void Tagger::tag() {
    std::vector<std::string> sentence;
    std::string line;
    getline(input_stream, line);

    while(!input_stream.eof()) {
        if(line == "") {
            std::vector<Tag> tags = hmm.predict(sentence);

            for(int i = 0; i < tags.size(); i++) {
                output_stream << sentence[i] << stringTag(tags[i]) << std::endl;
            }

            output_stream << std::endl;
        }
        else
            sentence.push_back(line);

        getline(input_stream, line);
    }
}

Tagger::~Tagger() {

}

