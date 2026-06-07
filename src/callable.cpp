// callable.cpp
#include "callable.hpp"
#include "errors.hpp"
#include "frame.hpp"
#include "evaluator.hpp"

#include <utility>
#include <vector>
#include <cstddef>
#include <string>

BuiltinFunction::BuiltinFunction(BuiltinFunction::Implementation implementation)
    : implementation_(std::move(implementation)) {}

Value BuiltinFunction::call(const std::vector<Value>& arguments) {
    return implementation_(arguments);
}

UserFunction::UserFunction(
    std::vector<std::string> parameters,
    Expr body,
    std::shared_ptr<Frame> enclosing_frame
) : parameters_(std::move(parameters)),
    body_(std::move(body)),
    enclosing_frame_(std::move(enclosing_frame)) {}

Value UserFunction::call(const std::vector<Value>& arguments) {
    if (arguments.size() != parameters_.size()) {
        throw SchemeEvaluationError("Number of arguments do not match");
    }

    std::shared_ptr<Frame> call_frame = std::make_shared<Frame>(enclosing_frame_);

    for (std::size_t i = 0; i < arguments.size(); i++) {
        call_frame->define(parameters_[i], arguments[i]);
    }

    return evaluate(body_, call_frame);
}