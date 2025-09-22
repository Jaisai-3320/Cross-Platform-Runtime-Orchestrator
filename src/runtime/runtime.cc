#include "runtime.h"
if (cfg.enable_inspector) {
t->inspector_port = InspectorServer::Start(t->iso->isolate, cfg.id, cfg.inspector_port);
}


tenants_[cfg.id] = std::move(t);
LogInfo("Tenant started: "+cfg.id);
return true;
}


void Runtime::StopTenant(const std::string& id){
auto it = tenants_.find(id);
if (it==tenants_.end()) return;
if (it->second->inspector_port) InspectorServer::Stop(it->second->iso->isolate);
tenants_.erase(it);
LogInfo("Tenant stopped: "+id);
}


static ExecutionResult RunInIsolate(v8::Isolate* isolate, const std::string& code, const std::string& filename){
ExecutionResult res;
v8::Isolate::Scope iso_scope(isolate);
v8::HandleScope handle_scope(isolate);
auto context = v8::Context::New(isolate);
v8::Context::Scope ctx_scope(context);


v8::TryCatch try_catch(isolate);
auto source = v8::String::NewFromUtf8(isolate, code.c_str()).ToLocalChecked();
auto name = v8::String::NewFromUtf8(isolate, filename.c_str()).ToLocalChecked();
v8::ScriptOrigin origin(name);
v8::Local<v8::Script> script;
if (!v8::Script::Compile(context, source, &origin).ToLocal(&script)){
v8::String::Utf8Value err(isolate, try_catch.Exception());
res.error_message = *err ? *err : "compile error";
return res;
}
v8::Local<v8::Value> result;
if (!script->Run(context).ToLocal(&result)){
v8::String::Utf8Value err(isolate, try_catch.Exception());
res.error_message = *err ? *err : "runtime error";
return res;
}
if (!result->IsUndefined()){
v8::String::Utf8Value out(isolate, result);
res.stdout_text = *out ? *out : "";
}
res.ok = true;
return res;
}


ExecutionResult Runtime::ExecuteFile(const std::string& tenant_id, const std::string& path){
auto it = tenants_.find(tenant_id);
if (it==tenants_.end()) return {false, {}, {}, "tenant not found"};
auto buf = ReadFile(path);
if (!buf) return {false, {}, {}, "file not found"};
std::string transpiled = ts::TranspileIfNeeded(path, *buf);
return RunInIsolate(it->second->iso->isolate, transpiled, path);
}


ExecutionResult Runtime::ExecuteCode(const std::string& tenant_id, const std::string& code, const std::string& filename){
auto it = tenants_.find(tenant_id);
if (it==tenants_.end()) return {false, {}, {}, "tenant not found"};
return RunInIsolate(it->second->iso->isolate, code, filename);
}