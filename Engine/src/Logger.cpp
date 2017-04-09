#include "Logger.h"

std::shared_ptr<spdlog::logger> GibEngine::Logger::Instance = spdlog::stdout_color_st("GibEngine");