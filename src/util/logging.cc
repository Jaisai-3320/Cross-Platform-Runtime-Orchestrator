#include "logging.h"
#include <iostream>
void LogInfo(const std::string& s){ std::cout << "[INFO] " << s << "\n"; }
void LogError(const std::string& s){ std::cerr << "[ERROR] " << s << "\n"; }