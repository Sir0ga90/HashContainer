#pragma once

#include <memory>



//========================================================================//
struct SHashWrapper {
    SHashWrapper() = default;
    SHashWrapper(int new_key);
    int key;
};


class CHashNode;
using TElement = SHashWrapper;
using THashNodePtr = std::shared_ptr<CHashNode>;
//========================================================================//
class CHashNode
{
public:
    CHashNode(const TElement& value);
    ~CHashNode() = default;

    THashNodePtr getNextNode() const;
    void setNextNode(THashNodePtr next_node);
    int getKey() const;

private:
    TElement value;
    THashNodePtr nextNode;
};

using TContainer = std::unique_ptr<THashNodePtr[]>;

//========================================================================//
class CHashContainer {
public:
    CHashContainer();
    ~CHashContainer() = default;

    void insert(CHashNode& new_element);

private:
    static constexpr int INIT_CAPACITY = 30;
    TContainer container;
};