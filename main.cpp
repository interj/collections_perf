#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <random>
#include <algorithm>
#include <set>
#include <string>
#include <list>

namespace ranges = std::ranges;

void test(int size)
{
    int const SIZE = size;
    size_t const ACCESSES = 1000000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution random(0, SIZE - 1);
    const std::string suffix = "s";
    
    std::vector<std::string> coherent;
    std::list<std::string> incoherent;
    std::set<std::string> incoherent_set;
    std::unordered_set<std::string> hash_set;
    
    for (int i = 0; i < SIZE; ++i) {
        auto value = std::to_string(i) + suffix;
        coherent.push_back(value);
        incoherent.push_back(value);
        incoherent_set.insert(value);
        hash_set.insert(value);
    }
    ranges::sort(coherent);

    std::vector<std::string> queries;
    for (size_t i = 0; i < ACCESSES; ++i) {
        auto value = std::to_string(random(gen)) + suffix;
        queries.push_back(value);
    }

    std::string retrieved;
    std::cout << SIZE;

    auto start = std::chrono::steady_clock::now();
    auto count_vec = 0;
    for (auto& query : queries) {
        if(auto res = ranges::find(coherent, query); res != coherent.cend())
        {
            retrieved = *res;
            count_vec++;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << ';' << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    auto count_binary = 0;
    for(auto& query: queries)
    {
        if(auto res = ranges::lower_bound(coherent, query); res != coherent.cend())
        {
            retrieved = *res;
            count_binary++;
        }
    }
    end = std::chrono::steady_clock::now();
    std::cout << ';' << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    auto count_hash = 0;
    for (auto& query : queries) {
        if(auto res = hash_set.find(query); res != hash_set.cend())
        {
            retrieved = *res;
            count_hash++;
        }
    }
    end = std::chrono::steady_clock::now();
    std::cout << ';' << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    auto count_set = 0;
    for (auto& query : queries) {
        if(auto res = incoherent_set.find(query); res != incoherent_set.cend())
        {
            retrieved = *res;
            count_set++;
        }
    }
    end = std::chrono::steady_clock::now();
    std::cout << ';' << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    auto count_list = 0;
    for (auto& query : queries) {
        if(auto res = ranges::find(incoherent, query); res != incoherent.cend())
        {
            retrieved = *res;
            count_list++;
        }
    }
    end = std::chrono::steady_clock::now();
    std::cout << ';' << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    volatile auto total = count_vec + count_binary + count_hash + count_list + count_set;

    std::cout << std::endl;
}

int main(int argc, char** argv) 
{
    std::cout << ";Continuous array;Binary search;Hash map;Tree;Linked list" << std::endl;
    for(int i = 1; i <= 500; ++i)
    {
        test(i);
    }
}
