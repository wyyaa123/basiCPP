#pragma once
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <spdlog/fmt/chrono.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#define INFO spdlog::level::info
#define DEBUG spdlog::level::debug
#define WARN spdlog::level::warn
#define ERROR spdlog::level::err
#define CRITICAL spdlog::level::critical

static std::vector<std::string> registered_loggers;

spdlog::logger get_root_logger(std::string logger_name,
                               spdlog::level::level_enum level = INFO,
                               bool use_file = false);
std::string get_current_datetime();
std::string fmtstring(const char* fmt, ...);

class TimeRecorder {
public:
    TimeRecorder() { start = std::chrono::high_resolution_clock::now(); }
    double get_time() { return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count(); }
    void reset() { start = std::chrono::high_resolution_clock::now(); }
private:
    std::chrono::high_resolution_clock::time_point start;
};
