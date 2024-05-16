# collections_perf
Everyone already did this one, I wanted my own

Long string suffix results:

![image](https://github.com/interj/collections_perf/assets/7340707/50af4e70-2d9a-4b59-8593-7b8453a19365)

Short string suffix results:

![image](https://github.com/interj/collections_perf/assets/7340707/5913ef17-7451-4c7e-b97a-bf55dc6acb86)

Interestingly, taking advantage of Short String Optimization in C++ lowers the constant cost of hash calculation in `std::unordered_set`, but it impacts the performance of `std::vector` and `std::list` negatively.
