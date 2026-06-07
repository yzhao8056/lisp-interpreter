// main.cpp
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "builtins.hpp"

#include <iostream>
#include <string>

int main() {
    auto res = parse(tokenize("7 ;ignore \n 23324 haha"));
    return 0;
}