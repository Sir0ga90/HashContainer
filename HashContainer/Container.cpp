#include"Container.h"
#include <iostream>


SHashWrapper::SHashWrapper(THash new_hash) :
    hashVal(new_hash) {}


//========================================================================//
void CBucket::insert(const TElement& new_element) {
    elements.push_back(new_element);
}


//========================================================================//
CHashContainer::CHashContainer() {
    littleGapContainer.resize(INIT_SIZE);
}



uint32_t CHashContainer::elements_cntr = 0;

//========================================================================//
void CHashContainer::insert(const TElement& new_element) {
    const THash new_hash = hash1(new_element);

    if (isLittleGap(new_hash)) {

        ++elements_cntr;
    
        if (new_hash > littleGapContainer.size() ||
            littleGapContainer.size() / elements_cntr > FULLNESS_PROPORTION) {

            rebuildContainer(new_element);
        }

        littleGapContainer.at(new_hash).insert(new_element);    //add to bucket

    }
    else {
        bigGapContainer.insert(std::pair<THash, TElement>(new_hash, new_element));
    }
}

void CHashContainer::printData() {
    std::cout << "Little gap container: " << littleGapContainer.size() << " elems.\n";
    std::cout << "Big gap container: " << bigGapContainer.size() << " elems.\n";
}


bool CHashContainer::isLittleGap(const THash current_hash_val) const {
    const auto result = current_hash_val < littleGapContainer.size() * 2;

    return result;
}


THash CHashContainer::hash1(const TElement key) {
    const THash hash = 101 * ((key * 24) + 101 * ((key * 16) + 101 * (key * 8))) + key;

    return hash % littleGapContainer.size();
}

void CHashContainer::rebuildContainer(const TElement& new_element)
{
    //TODO: make implementation
}

//========================================================================//
