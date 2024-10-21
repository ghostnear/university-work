# Benchmarks

| CPU                               | Transactions / Thread | Granular lock | Time      |
| --------------------------------- | --------------------- | ------------- | --------- |
| Intel i7-12700H     @4.6GHz 12thr | 2000                  | true          | <1ms      |
| Intel i7-12700H  PS @2.3GHz 12thr | 2000                  | true          | <5ms      |
| Intel i7-12700H     @4.6GHz 12thr | 2000                  | false         | ~5ms      |
| Intel i7-12700H     @4.6GHz 12thr | 20000                 | true          | ~5ms      |
| Intel i7-13850HX PS @2.1GHz 28thr | 2000                  | true          | ~10ms     |
| Intel i7-12700H  PS @2.3GHz 12thr | 2000                  | false         | ~15ms     |
| Intel i7-13850HX PS @2.1GHz 28thr | 2000                  | false         | ~15ms     |
| Intel i7-12700H  PS @2.3GHz 12thr | 20000                 | true          | ~20ms     |
| Intel i7-12700H     @4.6GHz 12thr | 20000                 | false         | ~50ms     |
| Intel i7-13850HX PS @2.1GHz 28thr | 20000                 | true          | ~50ms     |
| Intel i7-12700H     @4.6GHz 12thr | 200000                | true          | ~60ms     |
| Intel i7-12700H  PS @2.3GHz 12thr | 20000                 | false         | ~150ms    |
| Intel i7-12700H  PS @2.3GHz 12thr | 200000                | true          | ~175ms    |
| Intel i7-13850HX PS @2.1GHz 28thr | 20000                 | false         | ~200ms    |
| Intel i7-13850HX PS @2.1GHz 28thr | 200000                | true          | ~375ms    |
| Intel i7-12700H     @4.6GHz 12thr | 200000                | false         | ~500ms    |
| Intel i7-12700H  PS @2.3GHz 12thr | 200000                | false         | ~1750ms   |
| Intel i7-13850HX PS @2.1GHz 28thr | 200000                | false         | ~3200ms   |


- PS in the CPU column comes from Power Saving mode.