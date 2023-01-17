#ifndef CHIENGINE_EVALUATE_H
#define CHIENGINE_EVALUATE_H

#include <torch/torch.h>

class Evaluator {
public:
    Evaluator(const std::string& netPath);

    // returns true if position a is better for white than position b,
    // and false if the opposite
    bool evaluate(std::vector<uint8_t> a, std::vector<uint8_t> b);

private:
    torch::jit::script::Module module;
};

#endif //CHIENGINE_EVALUATE_H
