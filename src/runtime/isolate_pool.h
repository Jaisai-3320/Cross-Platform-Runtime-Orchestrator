#pragma once
#include <v8.h>
#include <functional>
#include <string>
#include <memory>


struct IsolateLimits {
size_t max_heap_bytes{64 * 1024 * 1024};
};

class IsolateWrapper {
public:
IsolateWrapper(v8::Isolate* iso, v8::ArrayBuffer::Allocator* alloc)
: isolate(iso), allocator(alloc) {}
~IsolateWrapper();

v8::Isolate* isolate;
v8::ArrayBuffer::Allocator* allocator;
};

using IsolateFactory = std::function<std::unique_ptr<IsolateWrapper>(const IsolateLimits&)>;

class IsolatePool {
public:
static std::unique_ptr<IsolateWrapper> Create(const IsolateLimits& limits);
};