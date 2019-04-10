#include "Container.h"
#include <chrono>
#include <iostream>
#include <random>


void test_hash();
int random(int lim);

std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());     // provide seed


//========================================================================//
int main() {

    test_hash();

    return 0;
}


//========================================================================//
int random(int lim) {
    std::uniform_int_distribution<int> uid{0,lim};   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no
}


//========================================================================//
void test_hash() {
    CHashContainer container;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        TElement elem(random(1000000));
        container.insert(elem);
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << duration << "ms\n";

    container.printData();
}
