#include "Evaluate.h"
#include <torch/script.h>


Evaluator::Evaluator(const std::string &netPath) {
    try {
        module = torch::jit::load(netPath);
    } catch (const c10::Error &e) {
        std::cout << e.backtrace() << std::endl;
        std::cerr << "Error loading model\n";
    }

    std::cout << "Model loaded successfully\n";

    torch::NoGradGuard no_grad; // ensures that autograd is off
    module.eval(); // turn off dropout and other training-time layers/functions
}

bool Evaluator::evaluate(std::vector<int> a, std::vector<int> b) {
    auto t_a = torch::tensor(a);
    auto t_b = torch::tensor(b);
    t_a = torch::unsqueeze(t_a, 0);
    t_b = torch::unsqueeze(t_b, 0);
    auto t_input = torch::cat({t_a, t_b}, 0);

    std::cout << "Shape:" << std::endl << torch::_shape_as_tensor(t_input) << std::endl;

    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(t_input);

    try {
        module.forward(inputs);
        //at::Tensor output = module.forward(inputs).toTensor();
        std::cout << "Evaluated output." << std::endl;

//        if (torch::argmax(output).equal(torch::tensor(0))) {
//            return true;
//        } else {
//            return false;
//        }
    } catch (const c10::Error &e) {
        std::cout << e.backtrace() << std::endl;
        std::cerr << "Failed to evaluate output\n";
    }
    return false;
}
