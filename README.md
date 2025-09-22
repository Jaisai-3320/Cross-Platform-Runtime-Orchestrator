# Orchestrator


## Features
- V8 embedded per-tenant isolates (isolation & multi-tenancy)
- On-the-fly TypeScript transpile (naive implementation; swap with esbuild/ts)
- (Optional) Node.js embedding via `libnode`
- Chromium DevTools Protocol exposure via V8 Inspector (stubbed; wire WS server)
- Windows thread scheduling tweaks for parity with Linux/macOS


## Build
