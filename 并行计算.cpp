#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <windows.h>
#include <thread>
#include <algorithm>
#include <numeric>
template<typename Iterator,typename T>
T Parallel(Iterator begin, Iterator end) {
    auto length = std::distance(begin, end);
    if (!length) return T();
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const harware_threads = std::thread::hardware_concurrency();
	unsigned long const threads = harware_threads != 0 ? std::min<unsigned long>(harware_threads, max_threads) : max_threads;
	std::vector<T> results(threads);
	std::vector<std::thread> thread_pool(threads - 1);
	auto block_size = length / threads;
    Iterator block_start = begin;
    for (auto i = 0; i < threads - 1;++i) {
        Iterator block_end = block_start;
		std::advance(block_end, block_size);
        thread_pool[i] = std::thread([block_start, block_end,&results,i]() {
            results[i]=std::accumulate(block_start, block_end, T());
            });
        block_start= block_end;
    }
    results[threads-1]=std::accumulate(block_start,end, T());
    for (auto& entry : thread_pool) {
        if (entry.joinable()) {
            entry.join();
        }
    }

    // 【关键修复】将所有分块的结果汇总，并加上用户传入的初始值 init
    return std::accumulate(results.begin(), results.end(),T());
}