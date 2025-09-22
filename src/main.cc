#include "runtime/runtime.h"
#include "runtime/node_bridge.h"
#include "util/logging.h"
#include <iostream>


int main(int argc, char** argv){
Runtime::InitPlatform();


Runtime rt;
TenantConfig a{ .id = "tenantA", .max_heap_bytes = 64*1024*1024, .enable_inspector=true, .inspector_port=0 };
TenantConfig b{ .id = "tenantB", .max_heap_bytes = 64*1024*1024, .enable_inspector=true, .inspector_port=0 };
rt.StartTenant(a);
rt.StartTenant(b);


if (argc >= 3 && std::string(argv[1])=="--run"){
std::string tenant = argv[2];
std::string file = (argc>=4)? argv[3] : "examples/hello_ts/app.ts";


// If Node bridge is available and user wants Node semantics
if (argc>=5 && std::string(argv[4])=="--node" && NodeBridge::Available()){
auto r = NodeBridge::RunFile(file);
if (!r.ok) { LogError(r.error_message); return 1; }
std::cout << r.stdout_text << std::endl; return 0;
}


auto res = rt.ExecuteFile(tenant, file);
if (!res.ok){ LogError(res.error_message); return 1; }
if (!res.stdout_text.empty()) std::cout << res.stdout_text << std::endl;
return 0;
}


std::cout << "Usage: orchestrator --run <tenantId> <file.ts|js> [--node]\n";
return 0;
}