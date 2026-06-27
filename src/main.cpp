// main.cpp
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "builtins.hpp"
#include "errors.hpp"
#include "frame.hpp"

#include <iostream>
#include <string>

int main() {
    auto frame = make_initial_frame();

    std::cout << "Mini Scheme Interpreter\n";
    std::cout << "Type 'quit' to exit.\n";

    std::string line;

    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line == "quit" || line == "exit") {
            break;
        }

        if (line.empty()) {
            continue;
        }

        try {
            const auto tokens = tokenize(line);
            const Expr expression = parse(tokens);
            const Value result = evaluate(expression, frame);

            
            std::cout << "Evaluated successfully\n";
        } catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
        }
    }

    return 0;
}