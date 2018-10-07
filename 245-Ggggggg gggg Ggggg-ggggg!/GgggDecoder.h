//
// Created by Nicolas Haenni on 05.10.18.
//

#ifndef INC_245_GGGGGGG_GGGG_GGGGG_GGGGG_GGGGDECODER_H
#define INC_245_GGGGGGG_GGGG_GGGGG_GGGGG_GGGGDECODER_H

#include <fstream>
#include <set>
#include <unordered_map>

class GgggDecoder {
private:
    std::ifstream                         file;
    std::string                           keyString;
    std::unordered_map<std::string, char> key;
    std::string                           input;
    std::string                           decoded;
    unsigned long                         longestValue;

public:
    GgggDecoder();
    explicit GgggDecoder(std::string path);
    void readFile();
    void readFile(std::string path);
    void decode(unsigned long start, unsigned int currentCheckLength = 1);
    void buildKey();
    std::string getKeyString();
    std::string getInput();
    std::string getDecodedInput();
};


#endif //INC_245_GGGGGGG_GGGG_GGGGG_GGGGG_GGGGDECODER_H
