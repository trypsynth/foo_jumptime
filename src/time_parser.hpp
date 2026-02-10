#pragma once
#include <string>
#include <optional>

std::optional<double> parse_time(const std::string& input);
std::string format_time(double seconds);
