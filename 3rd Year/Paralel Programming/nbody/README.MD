# N-Body simulation in Lua using multiple threads.

## Description:

This is a simulation of the n-body problem written in Lua using the Love2D framework for displaying the results in real time.

It has been based on what could be found on [Wikipedia](https://en.wikipedia.org/wiki/N-body_simulation).

Mass assimilation by collisions has __not__ been implemented.

It makes use of Love2D's love.thread with a shared context and love.channel for communicating non-static data.

## Benchmarks of average FPS:

This benchmark has been calculated after running the program for a few seconds with an uncapped framerate.

| Number of objects | 1 thread | 3 threads | 6 threads | 12 threads | 24 threads |
| :---------------: | :------: | :-------: | :-------: | :--------: | :--------: |
| 101               | 420fps   | 460fps    | 480fps    | 494fps     | 505fps     |
| 505               | 63fps    | 90fps     | 111fps    | 150fps     | 155fps     |
| 1001              | 20fps    | 30fps     | 40fps     | 52fps      | 66fps      |
| 1551              | 8fps     | 14fps     | 18fps     | 26fps      | 40fps      |
| 2002              | 5fps     | 8fps      | 16fps     | 19fps      | 20fps      |

I have tested both with and without the drawing of the actual circles on the screen, the results did not deviate significantly enough to be worth elaborating on.

The device I tested this on has 12 threads as noted after running nproc on Linux.

## How to run:

Install Love2D on your machine and type in a terminal while in the root of the project:

```
love .
```

## Notes:

[Guide for debugging Love2D and Lua](https://sheepolution.com/learn/book/bonus/vscode)