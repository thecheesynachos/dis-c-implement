#include "mtree.h"

//Node constructure
template <
    typename DataType,
    typename DistanceFunction
>
Node<DataType, DistanceFunction>::Node(DataType *fO, Node<DataType, DistanceFunction> *pr, float dTP):
featureObj(fO), parent(pr), distToParent(dTP)
{}

template <
    typename DataType,
    typename DistanceFunction
>
std::vector<DataType> Node<DataType, DistanceFunction>::range(DataType *object, float searchRadius){
    return NULL;
}
template <
    typename DataType,
    typename DistanceFunction
>
void Node<DataType, DistanceFunction>::insert(DataType *newObject){
    
    if(isLeaf){

    }
    else{

    }
}

//RoutingNde constructure
template <
    typename DataType,
    typename DistanceFunction
>
RoutingNode<DataType, DistanceFunction>::RoutingNode(DataType *fO, float cR, Node<DataType, DistanceFunction> *pr, float dTP):
Node<DataType, DistanceFunction>(fO, pr, dTP), coverRadius(cR)
{}

//LeafNode constructure
template <
    typename DataType,
    typename DistanceFunction
>
LeafNode<DataType, DistanceFunction>::LeafNode(DataType *fO, Node<DataType, DistanceFunction> *pr, float dTP):
Node<DataType, DistanceFunction>(fO, pr, dTP)
{}