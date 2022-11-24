#ifndef CHIENGINE_ALGORITHMS_H
#define CHIENGINE_ALGORITHMS_H
#include <vector>
#include <iterator>
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

    static std::string bitBoardToString(int64 bb) {
        std::string res = "";
        std::stringstream ss;
        std::bitset<64>b(bb);
        std::string tmp = b.to_string();
        int count =0;
        for (int i =0; i < 8; i ++)
        {
            res += "\n";
            for (int j=0;j <8;j++)
            {
                res += tmp[count];
                count ++;
            }
        }

        return res;
    }

    static char asciiCharToLower(char in) {
        if (in <= 'Z' && in >= 'A')
            return in - ('Z' - 'z');
        return in;
    }
};

#endif //CHIENGINE_ALGORITHMS_H
