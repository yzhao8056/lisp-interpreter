// callable.hpp
#pragma once

#include <functional>
#include <memory>
#include <string>

#include "expr.hpp"
#include "value.hpp"
#include "frame.hpp"

class Callable {
public:
    virtual ~Callable() = default;

    virtual Value call(const std::vector<Value>& arguments) = 0;
};

class BuiltinFunction : public Callable {
public:
    using Implementation = std::function<Value(const std::vector<Value>&)>;

    explicit BuiltinFunction(Implementation implementation);

    Value call(const std::vector<Value>& arguments) override;

private:
    Implementation implementation_;
};

class UserFunction : public Callable {
public:
    UserFunction(
        std::vector<std::string> parameters,
        Expr body,
        std::shared_ptr<Frame> enclosing_frame
    );

    Value call(const std::vector<Value>& arguments) override;

private:
    std::vector<std::string> parameters_;
    Expr body_;
    std::shared_ptr<Frame> enclosing_frame_;
};