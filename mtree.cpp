#include "mtree.h"

//Node constructure
template <
    typename DataType,
    typename DistanceFunction
>
Node<DataType, DistanceFunction>::Node(DataType *featureObj, Node *parent, float distToParent):
featureObj(featureObj), parent(parent), distToParent(distToParent)
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
RoutingNode<DataType, DistanceFunction>::RoutingNode(DataType *featureObj, float coverRadius, Node<DataType, DistanceFunction> *parent, float distToParent):
Node<DataType, DistanceFunction>(featureObj, parent, distToParent), coverRadius(coverRadius)
{}

//LeafNode constructure
template <
    typename DataType,
    typename DistanceFunction
>
LeafNode<DataType, DistanceFunction>::LeafNode(DataType *featureObj, Node<DataType, DistanceFunction> *parent, float distToParent):
Node<DataType, DistanceFunction>(featureObj, parent, distToParent)
{}