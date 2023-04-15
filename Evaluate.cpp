#include "Evaluate.h"
#include <torch/csrc/jit/serialization/import.h>

Evaluator::Evaluator(const std::string& netPath) {
    try {
        module = torch::jit::load(netPath);
    } catch (const c10::Error& e) {
        std::cerr << "Error loading model\n";
    }

    std::cout << "Model loaded successfully\n";

    torch::NoGradGuard no_grad; // ensures that autograd is off
    module.eval(); // turn off dropout and other training-time layers/functions
}

bool Evaluator::evaluate(std::vector<uint8_t> a, std::vector<uint8_t> b) {
    std::vector<torch::jit::IValue> inputs;
    inputs.emplace_back(torch::tensor(a));
    inputs.emplace_back(torch::tensor(b));

    at::Tensor output = module.forward(inputs).toTensor();

    if(torch::argmax(output).equal(torch::tensor(0))) {
        return true;
    } else {
        return false;
    }
}
