#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>

struct LogContext {
  static LogContext& get() {
    static LogContext c;
    return c;
  }

  void logStr(std::string s) { stream << s << std::endl; }

 private:
  std::string file;
  std::ofstream stream;
  LogContext() {
    std::filesystem::path cwd = std::filesystem::current_path();
    auto text_file = cwd / "log.txt";
    file = text_file.string();
    stream = std::ofstream(text_file.string());
  }
  ~LogContext() { stream.close(); }
};

namespace std {
std::string to_string(const char* str) {
  return std::string(str);
}  // It pains me to do so
std::string to_string(const std::string& s) { return s; }
}  // namespace std

template <typename... Args>
void log(Args... args) {
  std::string final_str;
  (
      [&] {
        final_str += std::to_string(args);
        final_str += " ";
      }(),
      ...);
  if (final_str.size() > 0) {
    final_str.pop_back();  // Trim last char
  }
  LogContext::get().logStr(final_str);
}
