#pragma once
#include <string>


// Minimal TS->JS transpiler interface. Implementation uses a bundled esbuild-wasm or ts transpiler via embedded sources.
namespace ts {
// If the file has .ts extension, transpile; otherwise return input unchanged.
std::string TranspileIfNeeded(const std::string& filename, const std::string& source, std::string* out_sourcemap = nullptr);
}