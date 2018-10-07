//
// Created by Nicolas Haenni on 05.10.18.
//

#include "GgggDecoder.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>

GgggDecoder::GgggDecoder() : longestValue() {}

GgggDecoder::GgggDecoder(std::string path) : longestValue(0) {
    this->file.open(path);
}

void GgggDecoder::readFile() {
    std::string line;
    int         c = 0;
    if (this->file.is_open()) {
        while (std::getline(this->file, line)) {
            if (c == 0) this->keyString = line;
            else this->input.append(line + "\n");
            c++;
        }
    }
    this->decoded = this->input;
    file.close();
}

void GgggDecoder::readFile(std::string path) {
    this->file.open(path);
    this->readFile();
}

std::string GgggDecoder::getKeyString() {
    return this->keyString;
}

std::string GgggDecoder::getInput() {
    return this->input;
}

std::string GgggDecoder::getDecodedInput() {
    return this->decoded;
}

void GgggDecoder::buildKey() {
    std::istringstream stream;
    char               x, key  = ' ';
    std::string        value;
    bool               isValue = false;

    if (this->keyString.at(this->keyString.size() - 1) != ' ') this->keyString.append(" ");
    stream.str(this->keyString);

    while (stream.get(x)) {
        // if currently reading key
        if (!isValue && x != ' ') {
            key = x;
        }
            // currently reading value
        else if (isValue && x != ' ') {
            value.push_back(x);
        }
            // if currently reading whitespace (signals end of key/value)
        else {
            // finished reading key, switch to value
            if (!isValue) {
                isValue = true;
            }
                // finished reading value, store data and reset variables
            else {
                if (this->longestValue < value.size()) this->longestValue = value.length();
                this->key.insert({{value, key}});

                key     = ' ';
                value   = "";
                isValue = false;
            }
        }
    }

    for (auto c : this->key) {
        std::cout << c.first << ": " << c.second << " (" << c.first.size() << ")" << std::endl;
    }
}

void GgggDecoder::decode(unsigned long start, unsigned int currentCheckLength) {
    std::unordered_map<std::string, char>::iterator search;
    std::string                                     current;

    if ((start + currentCheckLength)  >= this->decoded.size() - 1) return;

    current = this->decoded.substr(start, currentCheckLength);

    long count_g = std::count(current.begin(), current.end(), 'g');
    long count_G = std::count(current.begin(), current.end(), 'G');
    if (count_g + count_G != currentCheckLength) {
        this->decode(start + 1, 1);
        return;
    }

    search = this->key.find(current);

    if (search == this->key.end()) {
        this->decode(start, currentCheckLength + 1);
        return;
    }
    else {
        this->decoded.replace(start, currentCheckLength, std::string(1, search->second));
        this->decode(start + 1, 1);
        return;
    }
}


