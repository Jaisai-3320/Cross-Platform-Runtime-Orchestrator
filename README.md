# Cross-Platform Runtime Orchestrator  
*(C++ | V8 | Node.js | Chromium DevTools Protocol)*

## Overview
The **Cross-Platform Runtime Orchestrator** is a lightweight runtime designed to execute TypeScript/JavaScript workloads in a **multi-tenant, cross-platform environment**. It embeds the **V8 engine** directly inside a C++ host application and optionally links against **Node.js** to provide a hybrid runtime model.  

The system provides:
- **Process-level isolation via V8 Isolates** → each tenant/app runs in its own memory sandbox with configurable heap limits.  
- **Multi-tenant scheduling** → hundreds of apps can run concurrently without degradation.  
- **Chromium DevTools Protocol integration** → interactive debugging via Chrome DevTools.  
- **Cross-platform parity** → identical behavior on **Windows, Linux, and macOS**, with platform-specific optimizations (Win32 API for thread scheduling).  

---

## Architecture

### 1. Core Runtime (C++ Host)
- **Tenant Management**: Each tenant has a unique ID and dedicated V8 isolate with custom heap constraints.  
- **Execution Interface**: Supports running `.ts` or `.js` files directly. TypeScript is transpiled on-the-fly (naive implementation; swappable with `esbuild` or `tsc`).  
- **Result Encapsulation**: Execution results are captured (stdout, stderr, error messages) for reliable programmatic handling.

### 2. Isolation & Resource Limits
- Each **Isolate** enforces memory quotas (`max_heap_bytes`).  
- CPU budgets can be enforced using watchdog timers or V8’s `TerminateExecution()` API.  
- This prevents a single runaway tenant from impacting others.  

### 3. Node.js Bridge (Optional)
- If `libnode` is linked, tenants can be executed in a **full Node.js environment**, enabling access to Node core modules (fs, http, streams).  
- Runtime selects execution mode (`pure V8` vs `Node.js bridge`) per invocation.  
- This hybrid approach allows “serverless-like” multi-tenant execution with Node compatibility.

### 4. Debugging (DevTools Protocol)
- Integrated with **V8 Inspector**.  
- Each tenant optionally exposes a **WebSocket endpoint** compatible with Chrome DevTools (`chrome://inspect`).  
- Developers can step through code, profile performance, and inspect heap snapshots in real time.  

### 5. Cross-Platform Threading
- Uses **Win32 APIs** on Windows to set thread names, boost priority, and control CPU affinity.  
- Ensures **execution parity** with Linux/macOS schedulers, avoiding performance skews across environments.  

---

## Workflow

``` mermaid
flowchart TD
    A[Host Orchestrator] --> B[Tenant Manager]
    B -->|Creates| C[V8 Isolate]
    B -->|Creates optional| D[Node.js Context]
    C --> E[TypeScript Transpiler]
    E --> F[Execution Engine]
    D --> F
    F --> G[Result Capture]
    F --> H[DevTools Inspector]

