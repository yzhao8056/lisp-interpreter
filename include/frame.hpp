// frame.hpp
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "value.hpp"

class Frame {
public:
    explicit Frame(std::shared_ptr<Frame> parent = nullptr);
    void define(const std::string& name, Value value);
    Value lookup(const std::string& name) const;
    void mutate(const std::string& name, Value value);

private:
    std::shared_ptr<Frame> parent_;
    std::unordered_map<std::string, Value> mapping_;
};