// builtins.hpp
#pragma once

#include <memory>

class Frame;

std::shared_ptr<Frame> make_initial_frame();