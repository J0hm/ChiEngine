#ifndef CHIENGINE_ALGORITHMS_H
#define CHIENGINE_ALGORITHMS_H
#include <vector>

class Algorithms {
public:
    static void split(std::vector<std::string> &list, std::string str, std::string d);

    static std::string bitBoardToString(int64 bb);

    static char asciiCharToLower(char in);
};

#endif //CHIENGINE_ALGORITHMS_H
