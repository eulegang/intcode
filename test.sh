#!/bin/zsh

watchexec -c -w tests -w src 'cmake --build .build && ctest --test-dir .build --output-on-failure'
