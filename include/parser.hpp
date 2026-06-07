// parser.hpp
#pragma once

#include "expr.hpp"

#include <vector>
#include <string>

Expr parse(const std::vector<std::string>& tokens);