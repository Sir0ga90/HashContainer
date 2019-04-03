#include"Container.h"


SHashWrapper::SHashWrapper(int new_key) :
    key(new_key) {}

//========================================================================//
CHashNode::CHashNode(const TElement& value) :
    value(value),
    nextNode(nullptr) {}

THashNodePtr CHashNode::getNextNode() const {
    return nextNode;
}

void CHashNode::setNextNode(THashNodePtr next_node) {
    nextNode = next_node;
}

int CHashNode::getKey() const {
    return value.key;
}


//========================================================================//
CHashContainer::CHashContainer() {
    container = std::make_unique<THashNodePtr[]>(INIT_CAPACITY);
}

void CHashContainer::insert(CHashNode& new_element) {
    THashNodePtr prev = nullptr;
    THashNodePtr entry = nullptr;

    while (entry != nullptr && entry->getKey() != new_element.getKey()) {
        prev = entry;
        entry = entry->getNextNode();
    }

    if (entry == nullptr) {
        entry = std::make_shared<CHashNode>(new_element);
        if (prev == nullptr) {
            // insert as first bucket
            container[0] = entry;
        }
        else {
            prev->setNextNode(entry);
        }
    }

}

