#pragma once

#include <memory>
#include <unordered_map>


using THash = uint32_t;


//========================================================================//
struct SHashWrapper {
    SHashWrapper() = default;
    SHashWrapper(THash new_hash);
    THash hashVal;
};


//========================================================================//
using TElement = uint32_t; //for testing of container just key value is enough


//========================================================================//
class CBucket
{
public:
    CBucket() = default;
    ~CBucket() = default;

    void insert(const TElement& new_element);

private:
    std::vector<TElement> elements;
    //TODO: add max size of bucket
};


//========================================================================//
class CHashContainer
{
public:
    CHashContainer();

    using TContainerLittleGap = std::vector<CBucket>;
    using TContainerBigGap = std::unordered_map<THash, CBucket>;

    void insert(const TElement& new_element);
    void printData();

private:
    bool isLittleGap(const THash current_hash_val) const;
    THash hash1(const TElement key);
    void rebuild();
    bool isShouldBeDoubled();

    TContainerLittleGap littleGapContainer;
    TContainerBigGap bigGapContainer;

    static constexpr uint32_t INIT_SIZE = 3;
    static constexpr float FULLNESS_PROPORTION = 0.618033;
    static uint32_t elements_cntr;
};
