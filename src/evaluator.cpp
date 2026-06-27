// evaluator.cpp
#include "evaluator.hpp"
#include "value.hpp"
#include "errors.hpp"
#include "callable.hpp"

#include <memory>
#include <string>
#include <vector>
#include <cstddef>

Value evaluate(
    const Expr& expression,
    const std::shared_ptr<Frame>& frame
) {
    if (const auto* number = std::get_if<double>(&expression.data)) {
        return Value {*number};
    }

    if (const auto* symbol = std::get_if<std::string>(&expression.data)) {
        return frame->lookup(*symbol);
    }

    const auto* list = std::get_if<Expr::List>(&expression.data);

    if (list == nullptr) {
        throw SchemeEvaluationError("Invalid expression");
    }

    if (list->empty()) {
        return Value { Nil {} };
    }

    const auto* op = std::get_if<std::string>(&(*list)[0].data);

    if (!op) {
        throw SchemeEvaluationError("Operator cannot be resolved");
    }
    
    const Value func_val = evaluate(Expr{*op}, frame);
    const auto* func = std::get_if<std::shared_ptr<Callable>>(&func_val.data);

    if (func == nullptr || *func == nullptr) {
        throw SchemeEvaluationError("Attempted to call a non-function (not callable)");
    }

    std::vector<Value> arguments;

    for (std::size_t i = 1; i < list->size(); i++) {
        arguments.push_back(evaluate((*list)[i], frame));
    }

    return (*func)->call(arguments);
}