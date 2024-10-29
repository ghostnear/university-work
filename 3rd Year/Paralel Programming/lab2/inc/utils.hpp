#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define pipe_t int
#define PIPE_IN 0
#define PIPE_OUT 1
#define PIPE_SIZE 2

#define PIPE_TERMINATOR -1
