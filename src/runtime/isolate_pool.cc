#include "isolate_pool.h"
#include <libplatform/libplatform.h>
#include <v8.h>


static void* AlignedAlloc(size_t length, size_t alignment) {
#ifdef _MSC_VER
return _aligned_malloc(length, alignment);
#else
void* ptr = nullptr; posix_memalign(&ptr, alignment, length); return ptr;
#endif
}
static void AlignedFree(void* data, size_t, void*) {
#ifdef _MSC_VER
_aligned_free(data);
#else
free(data);
#endif
}


class Allocator : public v8::ArrayBuffer::Allocator {
public:
void* Allocate(size_t length) override { return AlignedAlloc(length, 8); }
void* AllocateUninitialized(size_t length) override { return AlignedAlloc(length, 8); }
void Free(void* data, size_t length) override { AlignedFree(data, length, nullptr); }
};


IsolateWrapper::~IsolateWrapper() {
if (isolate) {
isolate->Dispose();
}
delete allocator;
}


std::unique_ptr<IsolateWrapper> IsolatePool::Create(const IsolateLimits& limits) {
auto* allocator = new Allocator();
v8::Isolate::CreateParams params;
params.array_buffer_allocator = allocator;
params.constraints.ConfigureDefaultsFromHeapSize(limits.max_heap_bytes / 2, limits.max_heap_bytes);
auto* isolate = v8::Isolate::New(params);
return std::make_unique<IsolateWrapper>(isolate, allocator);
}