#include "Container.h"
#include <chrono>
#include <iostream>
#include <functional>

auto hash1 = [](const int key) -> TElement {
    TElement hash;
    hash.key = 101 * ((key * 24) + 101 * ((key * 16) + 101 * (key * 8))) + key;
    return hash;
};

auto hash2 = [](const int key) -> TElement {
    TElement hash;
    hash.key = ((key * 16) ^ key) * 0x45d9f3b;
    return hash;
};

auto hash3 = [](const int key) -> TElement {
    TElement hash;
    hash.key = key;
    return hash;
};

void test_hash(std::function<TElement(const int)> func);


int main() {

    test_hash(hash1);
    test_hash(hash2);
    test_hash(hash3);

    return 0;
}


void test_hash(std::function<TElement(const int)> func) {
    CHashContainer container;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000000; ++i) {
        const auto key = func(i);
        CHashNode new_node{key};
        container.insert(new_node);
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << duration << "us\n";
}
