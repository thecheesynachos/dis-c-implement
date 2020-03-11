#include "disc.h"
#include <vector>


template <typename DataType>
DisC<DataType>::DisC(std::vector<DataType> inputData, int n, std::function<float (DataType, DataType)> dFunc, int sz) :
dataCount(n), data(inputData), distanceFunction(dFunc) {
    this->mTree = LeafNode<DataType>(nullptr, sz);
    this->constructTree();
}

template <typename DataType>
void DisC<DataType>::constructTree() {
    for (int i = 0; i < this->dataCount; i++) {
        this->mTree.addObject(Object<DataType>(this->data[i], this->distanceFunction));
    }
}

template <typename DataType>
std::vector<DataType> DisC<DataType>::getCover(float radius) {
    if (!this->isWhiteTree) {
        this->mTree.decolour();
    }

    this->isWhiteTree = false;
    std::vector<bool> isSelected = std::vector<bool>();
    isSelected.reserve(this->dataCount);
    int subsetCount = 0;
    while (this->mTree.colour == WHITE) {
        int maxIdx = -1;
        int maxCoverage = -1;
        for (int i = 0; i < this->dataCount; i++) {
            if (!isSelected[i]) {
                int coverage = this->mTree.range(this->data[i], radius);
                if (coverage > maxCoverage) {
                    maxCoverage = coverage;
                    maxIdx = i;
                }
            }
        }
        isSelected[maxIdx] = true;
        subsetCount++;
        this->mTree.colourRange(this->data[maxIdx], radius);
    }
    std::vector<DataType> selectedSubset = std::vector<DataType>();
    selectedSubset.reserve(subsetCount);
    int k = 0;
    for (int i = 0; i < this->dataCount; i++) {
        if (isSelected[i]) {
            selectedSubset[k] = data[i];
            k++;
        }
    }
    return selectedSubset;
}
