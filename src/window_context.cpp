//
// Created by guozhenxiong on 2021-07-22.
//

#include "window_context.h"

#include "include/gpu/GrDirectContext.h"

namespace strg {

WindowContext::WindowContext(const DisplayParams &params)
        : display_params_(params)
{}

WindowContext::~WindowContext() = default;
} // namespace strg