#!/bin/bash

gcovr -e '/.*/src/ui/' -e '/.*/include/ui/' -e '/.*/tests/' -e '/.*/src/main.cpp' --html ./build/coverage.html 
librewolf ./build/coverage.html