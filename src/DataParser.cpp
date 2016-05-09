//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#include "assignment1/DataParser.hpp"

#include <fstream>
#include <limits>


DataParser::DataParser(std::unordered_multimap<std::string, Word *>& textToWord,
                       std::unordered_multimap<Tag, Word *>& tagToWord,
                       std::vector<Ngram>& ngrams, std::vector<Word>& words)
                    : textToWord(textToWord), tagToWord(tagToWord),
                      ngrams(ngrams), words(words)
{

}


void DataParser::parse(const std::string &fileName) {
    std::ifstream fileStream(fileName);
    parse(fileStream);
}

void DataParser::parse(std::istream& stream) {
    words.clear();
    ngrams.clear();

    // First number always denotes count. The second is type.
    // aka: WORDTAG, 1-GRAM, 2-GRAM or 3-GRAM
    int count;
    std::string type;

    stream >> count >> type;

    // This is a word count. Format is:
    // COUNT "WORDTAG" TAG WORD
    if(type == "WORDTAG") {
        std::string tag, name;

        // Pull in tag and word
        stream >> name;
        stream >> tag;

        // Build up word
        Word word;
        word.name = name;
        word.count = count;
        word.tag = parseTag(tag);

        // Push to provided vector
        words.push_back(word);

        // Push pointers to appropriate hash-maps
        textToWord.insert({word.name, &words[words.size() - 1]});
        tagToWord.insert({word.tag, &words[words.size() - 1]});

    }

    // This is an n-gram. Format is:
    // COUNT DIGIT"-GRAM" {TAG list...}
    else if(type == "1-GRAM" || type == "2-GRAM" || type == "3-GRAM") {
        int numGrams = (type == "1-GRAM" ? 1 : (type == "2-GRAM" ? 2 : 3));

        Ngram ngram;

        // Convert every tag and add to ngram
        for(int i = 0; i < numGrams; i++) {
            std::string tag;
            stream >> tag;
            ngram.terms.push_back(parseTag(tag));
        }

        ngram.count = count;

        ngrams.push_back(ngram);
    }

    else {
        // lolwut
        char buffer[256];
        stream.getline(buffer, 256);
        std::cerr << "Error! Line in incorrect format: " << std::endl << '\t' << buffer << std::endl;
    }

}

DataParser::~DataParser() {

}
