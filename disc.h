#include "mtree.h"
#include <vector>

template <typename DataType>
class DisC {
    private:
        int dataCount;
        bool isWhiteTree;
        Node<DataType> mTree;
        void constructTree();
        std::vector<DataType> data;
        std::function<float (DataType, DataType)> distanceFunction;

    public:
        DisC(std::vector<DataType> inputData, int dataCount, std::function<float (DataType, DataType)> dFunc, int sz);
        std::vector<DataType> getCover(float radius);

};