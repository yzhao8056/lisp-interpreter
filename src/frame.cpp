// frame.cpp
#include "frame.hpp"
#include "errors.hpp"

#include <utility>

Frame::Frame(std::shared_ptr<Frame> parent)
    : parent_(std::move(parent)) {}

void Frame::define(const std::string& name, Value value) {
    mapping_[name] = std::move(value);
}

Value Frame::lookup(const std::string& name) const {
    const auto it = mapping_.find(name);

    if (it != mapping_.end()) {
        return it->second;
    }

    if (parent_ != nullptr) {
        return parent_->lookup(name);
    }

    throw SchemeNameError("Unknown name: " + name);
}

// Finds and mutates the value if exists.
void Frame::mutate(const std::string& name, Value value) {
    const auto it = mapping_.find(name);

    if (it != mapping_.end()) {
        it->second = std::move(value);
        return;
    }

    if (parent_ != nullptr) {
        parent_->mutate(name, value);
        return;
    }

    throw SchemeNameError("Unknown name: " + name);
}