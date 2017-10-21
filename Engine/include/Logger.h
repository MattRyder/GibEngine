#pragma once

#include <stdarg.h>
#include <spdlog/spdlog.h>

namespace GibEngine
{
    class Logger
    {
    public:
        static std::shared_ptr<spdlog::logger> Instance;
    };
}
