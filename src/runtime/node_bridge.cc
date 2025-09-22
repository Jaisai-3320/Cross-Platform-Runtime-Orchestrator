#include "node_bridge.h"
#ifdef ORCH_WITH_NODE
#include <node.h>
#include <uv.h>
#endif


bool NodeBridge::Available(){
#ifdef ORCH_WITH_NODE
return true;
#else
return false;
#endif
}


NodeExecResult NodeBridge::RunFile(const std::string& filename){
NodeExecResult r; r.ok=false;
#ifndef ORCH_WITH_NODE
r.error_message = "Node embedding not enabled";
return r;
#else
// Minimal Node embedding: run a single JS/TS entry via Node's main-like path.
const char* argvv[] = { "orchestrator-node", filename.c_str() };
int argc = 2; const int exit_code = node::Start(argc, const_cast<char**>(argvv));
r.ok = (exit_code == 0);
if (!r.ok) r.error_message = "Node exited with code "+std::to_string(exit_code);
return r;
#endif
}