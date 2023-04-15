#ifndef CHIENGINE_INPUTTHREAD_H
#define CHIENGINE_INPUTTHREAD_H

#include <thread>
#include <string>
#include <iostream>

// an InputThread class to check and get new lines from stdin
class InputThread {
public:
    // default constructor
    InputThread();

    // checks if new input is available (i.e. a new command was sent)
    inline bool isNewInputAvailable() { return newInputAvailable;}

    // gets the new input and returns it as a string
    inline std::string getNewInput() {
        if (newInputAvailable) {
            newInputAvailable = false;
            return input;
        } else {
            return "";
        }
    }


private:
    bool newInputAvailable = false;
    std::string input;

    // cin loop
    void inputLoop();
};

#endif //CHIENGINE_INPUTTHREAD_H
