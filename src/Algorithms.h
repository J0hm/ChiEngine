#ifndef CHIENGINE_ALGORITHMS_H
#define CHIENGINE_ALGORITHMS_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <regex>

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
};

#endif //CHIENGINE_ALGORITHMS_H
