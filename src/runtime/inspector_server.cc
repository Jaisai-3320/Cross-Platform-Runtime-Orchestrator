#include "inspector_server.h"
#include "../util/logging.h"
#include <v8.h>
#include <libplatform/libplatform.h>
// NOTE: For brevity, this is a placeholder that pretends to expose inspector.
// In production, use v8_inspector, wire a WS server (e.g., uWebSockets) to forward CDP messages.


struct InspectorState { int port = 0; };
static std::unordered_map<v8::Isolate*, InspectorState> g_states;


int InspectorServer::Start(v8::Isolate* isolate, const std::string& name, int port_hint){
// Bind a dummy port to convey where to connect (replace with actual WebSocket inspector).
int port = port_hint ? port_hint : 9229; // pretend default
g_states[isolate] = InspectorState{port};
LogInfo("Inspector for '"+name+"' at ws://127.0.0.1:"+std::to_string(port)+" (placeholder)");
return port;
}


void InspectorServer::Stop(v8::Isolate* isolate){
g_states.erase(isolate);
}