#include <helpers/foobar2000+atl.h>
#include "time_parser.hpp"
#include <charconv>
#include <cmath>
#include <cstdio>

namespace {
std::optional<double> parse_number(const char* begin, const char* end) {
	if (begin == end) return std::nullopt;
	double value{0};
	auto result = std::from_chars(begin, end, value);
	if (result.ec != std::errc{} || result.ptr != end) return std::nullopt;
	if (value < 0) return std::nullopt;
	return value;
}

std::string trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos) return "";
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}
}

std::optional<double> parse_time(const std::string& input) {
	std::string s = trim(input);
	if (s.empty()) return std::nullopt;
	double parts[3];
	int count{0};
	const char* p = s.c_str();
	const char* end = p + s.size();
	while (p < end && count < 3) {
		const char* colon = p;
		while (colon < end && *colon != ':') ++colon;
		auto val = parse_number(p, colon);
		if (!val) return std::nullopt;
		parts[count++] = *val;
		p = (colon < end) ? colon + 1 : end;
	}
	if (p != end || count == 0) return std::nullopt;
	double result{0};
	switch (count) {
	case 1:
		result = parts[0];
		break;
	case 2:
		if (parts[1] >= 60) return std::nullopt;
		result = parts[0] * 60 + parts[1];
		break;
	case 3:
		if (parts[1] >= 60 || parts[2] >= 60) return std::nullopt;
		result = parts[0] * 3600 + parts[1] * 60 + parts[2];
		break;
	}
	return result;
}

std::string format_time(double seconds) {
	if (seconds < 0) seconds = 0;
	int total = static_cast<int>(std::floor(seconds));
	int ms = static_cast<int>(std::round((seconds - total) * 1000));
	if (ms >= 1000) { total++; ms = 0; }
	int h = total / 3600;
	int m = (total % 3600) / 60;
	int s = total % 60;
	char buf[32];
	if (ms > 0) {
		if (h > 0) snprintf(buf, sizeof(buf), "%d:%02d:%02d.%03d", h, m, s, ms);
		else snprintf(buf, sizeof(buf), "%d:%02d.%03d", m, s, ms);
	} else {
		if (h > 0) snprintf(buf, sizeof(buf), "%d:%02d:%02d", h, m, s);
		else snprintf(buf, sizeof(buf), "%d:%02d", m, s);
	}
	return buf;
}
