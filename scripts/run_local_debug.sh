#!/usr/bin/env bash
set -euo pipefail

# Build first if not already
if [ ! -f build/orchestrator ]; then
  cmake -S . -B build -DV8_ROOT=${V8_ROOT:-/opt/v8}
  cmake --build build --config Release --parallel
fi

# Default tenant + example file
TENANT=${1:-tenantA}
FILE=${2:-examples/hello_ts/app.ts}

# Run orchestrator with inspector enabled (see runtime.cc InspectorServer::Start)
./build/orchestrator --run "$TENANT" "$FILE"