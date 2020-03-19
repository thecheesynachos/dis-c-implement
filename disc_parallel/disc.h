#include "mtree.h"
#include <vector>

template <typename DataType>
class DisC {
    private:
        int dataCount;
        bool isWhiteTree;
        Node<DataType> *mTree;
        std::vector<DataType*> *data;
        float (*distanceFunction)(DataType*, DataType*);

        void constructTree() {
//            for (int i = 0; i < this->dataCount; i++) {
//                Object<DataType> *obj = new Object<DataType>(this->data->at(i));
//                this->mTree->insert(obj);
//            }
            this->mTree->bulkInsert(data);
        }

    public:
        DisC(std::vector<DataType*> *inputData, int n, float (*dFunc)(DataType*, DataType*), int sz) :
                dataCount(n), data(inputData), distanceFunction(dFunc) {
            this->mTree = new LeafNode<DataType>(sz, dFunc);
            this->constructTree();
        }

        ~DisC() {
            delete mTree;
        }

        std::vector<DataType*> *getCover(float radius) {
//            if (!this->isWhiteTree) {
//                this->mTree->decolour();
//            }

//            this->isWhiteTree = false;
            std::vector<bool> isSelected = std::vector<bool>();
            isSelected.reserve(this->dataCount);
            for (int i = 0; i < this->dataCount; i++) {
                isSelected.push_back(false);
            }
            std::vector<DataType*> *selectedSubset = new std::vector<DataType*>();
            int subsetCount = 0;
            while (this->mTree->colour == WHITE && subsetCount < this->dataCount) {
                int maxIdx = -1;
                int maxCoverage = -1;
                for (int i = 0; i < this->dataCount; i++) {
                    if (!(isSelected.at(i))) {
                        int coverage = this->mTree->range(this->data->at(i), radius);
                        if (coverage > maxCoverage) {
                            maxCoverage = coverage;
                            maxIdx = i;
                        }
                    }
                }
                if (maxCoverage > 0) {
                    isSelected.at(maxIdx) = true;
                    subsetCount++;
                    this->mTree->colourRange(this->data->at(maxIdx), radius);
                    selectedSubset->push_back(this->data->at(maxIdx));
//                    std::cout << maxIdx << " " << maxCoverage << std::endl;
                } else {
                    break;
                }
            }
            return selectedSubset;
        }

};