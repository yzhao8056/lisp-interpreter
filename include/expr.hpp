// expr.hpp
#pragma once

#include <string>
#include <vector>
#include <variant>

struct Expr {
    using List = std::vector<Expr>;

    std::variant<
        double, // numbers
        std::string, // symbols
        List // S-expressions
    > data;
};