#!/bin/bash

cmake -S . -B build &&
cmake --build build    \
      --config Release \
      --parallel "$(nproc)"
