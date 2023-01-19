#include <iostream>
#include <torch/csrc/jit/serialization/import.h>
#include "Engine.h"
#include "Evaluate.h"

int main() {
    Board board;
    torch::jit::script::Module module;
    std::vector<int> a;
    std::vector<int> b;

    for(int i = 0; i < 768; i++) {
        a.push_back(rand()%2);
        b.push_back(rand()%2);
    }


    std::cout << "len: " << a.size() << std::endl;

    try {
        module = torch::jit::load("C:\\Users\\johnk\\Documents\\Programming\\C++\\ChiEngine\\src\\engine\\net\\ccrl3000eval.p");
    } catch (const c10::Error &e) {
        std::cout << e.backtrace() << std::endl;
        std::cerr << "Error loading model\n";
    }

    std::cout << "Model loaded successfully\n";

    torch::NoGradGuard no_grad; // ensures that autograd is off
    module.eval(); // turn off dropout and other training-time layers/functions

    auto t_a = torch::tensor(a);
    auto t_b = torch::tensor(b);
    t_a = torch::unsqueeze(t_a, 0);
    t_b = torch::unsqueeze(t_b, 0);
    auto t_input = torch::cat({t_a, t_b}, 0);

    std::cout << "Shape:" << std::endl << torch::_shape_as_tensor(t_input) << std::endl;

    std::vector<torch::jit::IValue> inputs(0);
    inputs.push_back(t_input);

    try {
        module.forward({at::tensor(a), at::tensor(b)});
        //at::Tensor output = module.forward(inputs).toTensor();
        std::cout << "Evaluated output." << std::endl;

//        if (torch::argmax(output).equal(torch::tensor(0))) {
//            return true;
//        } else {
//            return false;
//        }
    } catch (const c10::Error &e) {
        std::cout << e.msg() << std::endl;
        std::cout << GetExceptionString(e) << std::endl;
        std::cout << e.backtrace() << std::endl;
        std::cerr << "Failed to evaluate output\n";
    }

    return 0;
}
