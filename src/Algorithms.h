#ifndef CHIENGINE_ALGORITHMS_H
#define CHIENGINE_ALGORITHMS_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <regex>
#include "Types.h"

class Algorithms {
public:
    static void split(std::vector<std::string> &list, std::string str, std::string d){
        // passing -1 as the submatch index parameter performs splitting
        std::regex re(d);
        std::sregex_token_iterator
                first{str.begin(), str.end(), re, -1},
                last;
        list = {first, last};
    };

    static void printBitBoard(int64 bb) {
        printf("\n");
        std::stringstream ss;
        std::bitset<64>b(bb);
        std::string tmp = b.to_string();
        int count =0;
        for (int i =0; i < 8; i ++)
        {
            printf("\n");
            for (int j=0;j <8;j++)
            {
                printf("%c ",tmp[count]);
                count ++;
            }
        }
    }
};

#endif //CHIENGINE_ALGORITHMS_H