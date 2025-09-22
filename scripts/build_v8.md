# Building or Fetching V8 for Orchestrator

The Orchestrator runtime embeds V8, so you need headers + libraries for your platform.

## Option 1: Use Prebuilt V8 (recommended)
1. Download a prebuilt V8 package (many community builds exist, or build once on your machine).
2. Extract somewhere, e.g. `/opt/v8`.
3. Point CMake to it:
   ```bash
   cmake -S . -B build -DV8_ROOT=/opt/v8