//
// Created by Ricardo Delfin Garcia on 5/8/16.
//

#include "assignment1/DataParser.hpp"
#include "assignment1/Data.hpp"

#include <fstream>
#include <limits>


DataParser::DataParser(std::unordered_multimap<std::string, size_t>& textToWord,
                       std::unordered_multimap<int, size_t>& tagToWord,
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
    size_t rareCount = 0;

    // Insert rare words.
    Word rareO, rareGene;
    size_t rareOIndex, rareGeneIndex;
    rareO.name = rareGene.name = "_RARE_";
    rareO.count = rareGene.count = 0;
    rareO.tag = TAG_O;
    rareGene.tag = TAG_I_GENE;

    words.push_back(rareO);
    words.push_back(rareGene);

    rareOIndex = words.size() - 2;
    rareGeneIndex = words.size() - 1;

    // We need to insert these to the Tag-to-word map
    tagToWord.insert({rareO.tag, rareOIndex});
    tagToWord.insert({rareGene.tag, rareGeneIndex});

    // Also insert special, "_RARE_" map
    textToWord.insert({rareO.name, rareOIndex});
    textToWord.insert({rareGene.name, rareGeneIndex});


    while(!stream.eof()) {
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
            stream >> tag;
            std::getline(stream, name);

            // Left trim name (it always contains additional whitespace)
            size_t startpos = name.find_first_not_of(" \t");
            if(std::string::npos != startpos)
            {
                name = name.substr(startpos);
            }

            std::cout << "Adding word: [" << count << ", " << name << ", " << tag << "]" << std::endl;

            // Build up word
            Word word;
            word.name = name;
            word.count = count;
            word.tag = parseTag(tag);

            // Add to rare instead
            if(count < 5) {
                rareCount++;
                size_t idx = (word.tag == TAG_I_GENE ? rareGeneIndex : rareOIndex);
                words[idx].count += word.count;

                // This will map all rare words to the _RARE_ word
                textToWord.insert({word.name, idx});
            }

            // Push to vector and continue
            else {
                // Push to provided vector
                words.push_back(word);

                // Push pointers to appropriate hash-maps
                textToWord.insert({word.name, words.size() - 1});
                tagToWord.insert({(int)word.tag, words.size() - 1});
            }
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
            std::cerr << "Error! Line with incorrect format: " << std::endl << '\t' << buffer << std::endl;
        }
    }

    std::cout << "Total rare words: " << rareCount << std::endl;

}


void DataParser::dump(const std::string& file)
{
    std::ofstream streamWords(file + ".words");
    std::ofstream streamNgrams(file + ".ngrams");
    std::ofstream streamtextMap(file + ".map.text");
    std::ofstream streamtagMap(file + ".map.tag");

    for(int i = 0; i < words.size(); i++) {
        streamWords << words[i].name << "\t" <<
            stringTag(words[i].tag) << "\t" << words[i].count
            << std::endl;
    }

    for(int i = 0; i < ngrams.size(); i++) {
        streamNgrams << ngrams[i].count << "\t";
        for(int j = 0; j < ngrams[i].terms.size(); j++) {
            streamNgrams << stringTag(ngrams[i].terms[i]) << " ";
        }
        streamNgrams << std::endl;
    }

    for(auto it = textToWord.begin(); it != textToWord.end(); ++it) {
        Word word = words[it->second];
        streamtextMap << it->first << " to [" << word.name <<
            ", " << stringTag(word.tag) << "]" << std::endl;
    }

    for(auto it = tagToWord.begin(); it != tagToWord.end(); ++it) {
        Word word = words[it->second];
        streamtagMap << stringTag((Tag)it->first) << " to ["
            << word.name << ", " << stringTag(word.tag) << "]"
            << std::endl;
    }
}
DataParser::~DataParser() {

}
