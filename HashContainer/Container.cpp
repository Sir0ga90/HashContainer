#include"Container.h"


CContainer::CContainer()
{
    container = std::make_unique<TElement[]>(INIT_CAPACITY);
    current_capacity = INIT_CAPACITY;
}

void CContainer::insert(TElement& new_element) {
    auto hashVal = hash(new_element.key);

    if(current_capacity < hashVal.key)
    {
        current_capacity = hashVal.key;
        container = std::make_unique<TElement[]>(current_capacity);
    }

    container[hashVal.key] = new_element;
}

SHashWrapper CContainer::hash(const int& key) {
    SHashWrapper hash{};

    hash.key = 101 * ((key * 24) + 101 * ((key * 16) + 101 * (key * 8))) + key;

    return hash;
}
