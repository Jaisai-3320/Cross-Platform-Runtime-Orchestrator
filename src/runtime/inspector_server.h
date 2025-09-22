#pragma once
#include <memory>
#include <string>
#include <thread>
#include <functional>


namespace v8 { class Isolate; }


class InspectorServer {
public:
// Start a simple WebSocket server exposing the V8 Inspector on a port (0 = auto).
// Returns the actual bound port.
static int Start(v8::Isolate* isolate, const std::string& name, int port_hint = 0);
static void Stop(v8::Isolate* isolate);
};