#pragma once

#include <spdlog/spdlog.h>

namespace GibEngine
{
    class Logger
    {
    public:
        static std::shared_ptr<spdlog::logger> Instance;
    };
}
