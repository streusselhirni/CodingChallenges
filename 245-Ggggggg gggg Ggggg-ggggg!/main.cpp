#include <iostream>
#include <string>
#include "./GgggDecoder.h"

int main() {

    GgggDecoder Decoder;
    Decoder.readFile("CodedTexts/input3.txt");

    std::cout << "Building key" << std::endl;
    Decoder.buildKey();

    std::cout << "Decode message" << std::endl;
//    Decoder.decodeSameLength();
    Decoder.decode(0);

    std::cout << Decoder.getDecodedInput() << std::endl;


    return 0;
}