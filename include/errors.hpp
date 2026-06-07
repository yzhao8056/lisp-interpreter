// errors.hpp
#pragma once

#include <stdexcept>
#include <string>

class SchemeSyntaxError : public std::runtime_error {
public:
    explicit SchemeSyntaxError(const std::string& message)
        : std::runtime_error(message) {}
};

class SchemeNameError : public std::runtime_error {
public:
    explicit SchemeNameError(const std::string& message)
        : std::runtime_error(message) {}
};

class SchemeEvaluationError : public std::runtime_error {
public:
    explicit SchemeEvaluationError(const std::string& message)
        : std::runtime_error(message) {}
};