#pragma once
#define ORCH_PLATFORM "macos"
#elif defined(__linux__)
#define ORCH_PLATFORM "linux"
#else
#define ORCH_PLATFORM "unknown"
#endif


// Feature flags
#ifdef ORCH_WITH_NODE
#define ORCH_FEATURE_NODE 1
#else
#define ORCH_FEATURE_NODE 0
#endif


#define ORCH_STRINGIFY2(x) #x
#define ORCH_STRINGIFY(x) ORCH_STRINGIFY2(x)


#define ORCH_SEMVER \
ORCH_STRINGIFY(ORCH_VERSION_MAJOR) "." \
ORCH_STRINGIFY(ORCH_VERSION_MINOR) "." \
ORCH_STRINGIFY(ORCH_VERSION_PATCH)


namespace orchestrator::version {
inline constexpr int major_v = ORCH_VERSION_MAJOR;
inline constexpr int minor_v = ORCH_VERSION_MINOR;
inline constexpr int patch_v = ORCH_VERSION_PATCH;
inline constexpr std::string_view semver = ORCH_SEMVER;
inline constexpr std::string_view git_sha = ORCH_GIT_SHA;
inline constexpr std::string_view build_type = ORCH_BUILD_TYPE;
inline constexpr std::string_view platform = ORCH_PLATFORM;
inline constexpr bool with_node = (ORCH_FEATURE_NODE == 1);
inline constexpr std::string_view build_timestamp = ORCH_BUILD_TIMESTAMP;


// Returns a short human-readable line, e.g.:
// Orchestrator 0.1.0 (Release, linux, node:on, git abc1234, 2025-09-23 12:00:00)
inline std::string describe() {
std::string s;
s += "Orchestrator "; s += std::string(semver);
s += " ("; s += std::string(build_type); s += ", "; s += std::string(platform); s += ", ";
s += std::string("node:"); s += with_node ? "on" : "off"; s += ", ";
s += "git "; s += std::string(git_sha); s += ", ";
s += std::string(build_timestamp); s += ")";
return s;
}


// Returns machine-readable JSON with core metadata.
inline std::string json() {
std::string j = "{";
j += "\"version\":\""; j += std::string(semver); j += "\",";
j += "\"git\":\""; j += std::string(git_sha); j += "\",";
j += "\"buildType\":\""; j += std::string(build_type); j += "\",";
j += "\"platform\":\""; j += std::string(platform); j += "\",";
j += "\"withNode\":"; j += with_node ? "true" : "false"; j += ",";
j += "\"timestamp\":\""; j += std::string(build_timestamp); j += "\"";
j += "}";
return j;
}
}