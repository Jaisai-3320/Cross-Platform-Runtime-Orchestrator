#pragma once
#include <string>
#include <optional>


struct NodeExecResult {
bool ok{false};
std::string stdout_text;
std::string stderr_text;
std::string error_message;
};


class NodeBridge {
public:
static bool Available();
static NodeExecResult RunFile(const std::string& filename);
};