#pragma once

#include <vector>
#include <memory>

//========================================================================//
struct SHashWrapper {
    int key;
};

using TElement = SHashWrapper;
using TContainer = std::unique_ptr<TElement[]>;

//========================================================================//
class CContainer {
public:
    CContainer();
    ~CContainer() = default;

    void insert(TElement& new_element);

private:
    static constexpr int INIT_CAPACITY = 30;
    SHashWrapper hash(const int& key);
    TContainer container;
    int current_capacity;
};