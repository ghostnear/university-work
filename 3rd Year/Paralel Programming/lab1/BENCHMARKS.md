# Benchmarks

| CPU                               | Transactions / Thread | Granular lock | Time      |
| --------------------------------- | --------------------- | ------------- | --------- |
| Intel i7-13850HX PS @2.1GHz 28thr | 2000                  | true          | <10ms     |
| Intel i7-13850HX PS @2.1GHz 28thr | 2000                  | false         | ~15ms     |
| Intel i7-13850HX PS @2.1GHz 28thr | 20000                 | true          | ~50ms     |
| Intel i7-13850HX PS @2.1GHz 28thr | 20000                 | false         | ~200ms    |
| Intel i7-13850HX PS @2.1GHz 28thr | 200000                | true          | ~375ms    |
| Intel i7-13850HX PS @2.1GHz 28thr | 200000                | false         | ~3200ms   |


- PS in the CPU column comes from Power Saving mode.