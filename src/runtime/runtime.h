#pragma once
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <optional>


namespace v8 { class Isolate; class Platform; }


struct TenantConfig {
std::string id; // tenant/app id
size_t max_heap_bytes{64 * 1024 * 1024};
int max_cpu_ms{1000}; // per task budget
bool enable_inspector{true};
int inspector_port{0}; // 0 = auto
};


struct ExecutionResult {
bool ok{false};
std::string stdout_text;
std::string stderr_text;
std::string error_message;
};


class Runtime {
public:
static void InitPlatform();
static void DisposePlatform();

Runtime();
~Runtime();

bool StartTenant(const TenantConfig& cfg);
void StopTenant(const std::string& id);

// Execute a file (TS or JS). TS is transpiled on the fly.
ExecutionResult ExecuteFile(const std::string& tenant_id, const std::string& path);

// Execute a string (useful for REPL/devtools).
ExecutionResult ExecuteCode(const std::string& tenant_id, const std::string& code, const std::string& filename = "<eval>");

private:
struct Tenant;
std::unordered_map<std::string, std::unique_ptr<Tenant>> tenants_;
};