#include "Container.h"


int main() {
    CContainer container;

    for(int i = 0; i < 10000000; ++i)
    {
        auto key = SHashWrapper{i};
        container.insert(key);
    }

    return 0;
}