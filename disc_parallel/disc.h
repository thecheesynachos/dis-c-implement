#include "mtree.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/reducer_max.h>

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
                // int maxIdx = -1;
                // int maxCoverage = -1;
                //change to max_index_reduce
                //<maxCov, maxIdx>
                cilk::reducer<cilk::op_max_index<int, int>> best;
                cilk_for (int i = 0; i < this->dataCount; i++) {
                    if (!(isSelected.at(i))) {
                        int coverage = this->mTree->range(this->data->at(i), radius);
                        best->calc_max(i, coverage);
                    }
                }
                if (best->get_reference() > 0) {
                    isSelected.at(best->get_index_reference()) = true;
                    subsetCount++;
                    this->mTree->colourRange(this->data->at(best->get_index_reference()), radius);
                    selectedSubset->push_back(this->data->at(best->get_index_reference()));
//                    std::cout << maxIdx << " " << maxCoverage << std::endl;
                } else {
                    break;
                }
            }
            return selectedSubset;
        }

};