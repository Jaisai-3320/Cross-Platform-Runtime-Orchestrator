#include "file.h"
#include <fstream>
#include <sstream>
std::optional<std::string> ReadFile(const std::string& path){
std::ifstream f(path, std::ios::binary);
if(!f) return std::nullopt;
std::ostringstream ss; ss << f.rdbuf();
return ss.str();
}