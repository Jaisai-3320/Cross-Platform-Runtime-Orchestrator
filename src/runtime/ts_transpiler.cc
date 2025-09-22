#include "ts_transpiler.h"
#include <string>


// For simplicity here, we do a naive strip of type annotations and export type-only constructs.
// In production, integrate esbuild/ts transpiler via embedded JS engine or pre-bundled binary.
namespace ts {
static bool ends_with(const std::string& s, const std::string& suf){
if (s.size() < suf.size()) return false; return std::equal(s.end()-suf.size(), s.end(), suf.begin());
}
std::string TranspileIfNeeded(const std::string& filename, const std::string& source, std::string*) {
if (!ends_with(filename, ".ts")) return source;
std::string out; out.reserve(source.size());
bool in_angle = false; // very naive <T> removal in function signatures
for (size_t i=0;i<source.size();++i){
char c = source[i];
// strip ": type" in var/param (extremely minimalistic; replace this in real use)
if (c == ':' ) {
// skip until , ) ; = { } => or newline
while (i < source.size() && source[i] != ',' && source[i] != ')' && source[i] != ';' && source[i] != '=' && source[i] != '{' && source[i] != '}' && source[i] != '\n') i++;
out.push_back(' ');
if (i<source.size()) out.push_back(source[i]);
continue;
}
if (c=='<' && i+1<source.size() && isalpha(source[i+1])) { in_angle=true; continue; }
if (in_angle && c=='>') { in_angle=false; continue; }
if (!in_angle) out.push_back(c);
}
return out;
}
}