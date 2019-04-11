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

        if (new_hash > littleGapContainer.size() || isShouldBeDoubled()) {

            rebuild();
        }

        littleGapContainer.at(new_hash).insert(new_element);    //add to bucket

    }
    else {
        auto found_bucket = bigGapContainer.find(new_hash);

        if (found_bucket != bigGapContainer.end()) {
            found_bucket->second.insert(new_element);
        }
        else {
            CBucket new_bucket;
            new_bucket.insert(new_element);
            bigGapContainer.insert(std::pair<THash, CBucket>(new_hash, new_bucket));
        }
    }
}

void CHashContainer::printData() {
    std::cout << "Present elements count: " << elements_cntr << " elems.\n" <<
        "Little gap container: " << littleGapContainer.size() << " elems.\n" <<
        "Big gap container: " << bigGapContainer.size() << " elems.\n";
}


bool CHashContainer::isLittleGap(const THash current_hash_val) const {
    const auto result = current_hash_val < littleGapContainer.size() * 2;
    return result;
}


THash CHashContainer::hash1(const TElement key) {
    const THash hash = 101 * ((key * 24) + 101 * ((key * 16) + 101 * (key * 8))) + key;

    return hash % littleGapContainer.size();
}

void CHashContainer::rebuild() {
    littleGapContainer.resize(littleGapContainer.size() * 2);

    for (auto& bucket : bigGapContainer) {
        if (bucket.first < littleGapContainer.size()) {
            littleGapContainer[bucket.first] = bucket.second;
        }
        bigGapContainer.erase(bucket.first);
    }

}

bool CHashContainer::isShouldBeDoubled() {
    bool result = static_cast<float>(elements_cntr) / littleGapContainer.size() > FULLNESS_PROPORTION;
    return result;
}

//========================================================================//
