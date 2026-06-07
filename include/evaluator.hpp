// evaluator.hpp
#pragma once

#include "frame.hpp"
#include "expr.hpp"
#include "value.hpp"

#include <memory>

Value evaluate(
    const Expr& expression,
    const std::shared_ptr<Frame>& frame
);

