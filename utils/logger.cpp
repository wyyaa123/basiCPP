#include "logger.h"

std::string get_current_datetime() {
    auto now = std::chrono::system_clock::now();
    return fmt::format("{:%Y-%m-%d_%H:%M:%S}", 
                       fmt::localtime(std::chrono::system_clock::to_time_t(now)));
}

std::string fmtstring(const char* fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return std::string(buffer);
}

spdlog::logger get_root_logger(std::string logger_name, spdlog::level::level_enum level, bool use_file) {
    if (std::find(registered_loggers.begin(), registered_loggers.end(), logger_name) != registered_loggers.end()) {
        throw std::runtime_error("Logger with name " + logger_name + " already exists");
    }

    spdlog::logger logger = spdlog::logger(logger_name, {});
    
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(level);
    console_sink->set_pattern("%Y-%m-%d %H:%M:%S [%n] [%^%l%$]:%v");

    std::shared_ptr<spdlog::sinks::sink> file_sink = nullptr;
    if (use_file) {
        std::string log_file = get_current_datetime();
        log_file = "logs/" + logger_name + "_" + log_file + ".log";
        file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file, true);
        file_sink->set_level(spdlog::level::trace);
        logger.sinks() = {console_sink, file_sink};
    } else {
        logger.sinks() = {console_sink};
    }

    logger.set_level(spdlog::level::debug);
    logger.info("Logger initialized");
    registered_loggers.push_back(logger_name);

    return logger;
}
