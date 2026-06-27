// builtins.cpp
#include "builtins.hpp"
#include "frame.hpp"
#include "errors.hpp"
#include "value.hpp"
#include "callable.hpp"

#include <memory>
#include <vector>
#include <string>

namespace {

double require_number(const Value& val) {
    const auto* number = std::get_if<double>(&val.data);

    if (number == nullptr) {
        throw SchemeEvaluationError("Expected a number");
    }

    return *number;
}

Value add(const std::vector<Value>& arguments) {
    double result = 0.0;

    for (const Value& argument : arguments) {
        result += require_number(argument);
    }

    return Value{result};
}

} // namespace

std::shared_ptr<Frame> make_initial_frame() {
    auto frame = std::make_shared<Frame>();

    frame->define("#t", Value{true});
    frame->define("#f", Value{false});

    frame->define("+", Value{std::make_shared<BuiltinFunction>(add)});
    // TODO add more builtins

    return frame;
}