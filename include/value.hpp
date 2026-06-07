// values.hpp
#pragma once

#include <memory>
#include <string>
#include <variant>

class Callable;
struct Pair;

struct Nil {};

struct Value {
    using Data = std::variant<
        Nil,
        double,
        std::string,
        bool,
        std::shared_ptr<Pair>,
        std::shared_ptr<Callable>
    >;

    Data data;
};

struct Pair {
    Value car;
    Value cdr;
};