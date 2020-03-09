#include "mtree.h"

//Node constructor
template <
    typename DataType,
    typename DistanceFunction
>
Node<DataType, DistanceFunction>::Node(Node<DataType, DistanceFunction> *parentNode, int sz);
parent(parentNode), colour(WHITE), size(sz), filledAmount(0)
{}

template <
    typename DataType,
    typename DistanceFunction
>
int Node<DataType, DistanceFunction>::range(DataType *object, float searchRadius){
    if (this->isLeaf) {

    }
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
RoutingNode<DataType, DistanceFunction>::RoutingNode(Node<DataType, DistanceFunction> *parentNode, int sz):
Node<DataType, DistanceFunction>(parentNode, sz)
{
    this->storedRoutingObjects = new RoutingObject<DataType, DistanceFunction>[this->size];
}

//LeafNode constructure
template <
    typename DataType,
    typename DistanceFunction
>
LeafNode<DataType, DistanceFunction>::LeafNode(Node<DataType, DistanceFunction> *parentNode, int sz):
Node<DataType, DistanceFunction>(parentNode, sz)
{
    this->storedLeafObjects = new LeafObject<DataType, DistanceFunction>[this->size];
}

template <
        typename DataType,
        typename DistanceFunction
>
RoutingObject<DataType, DistanceFunction>::RoutingObject(DataType *featureObject, float covRad, float distToPar, RoutingNode<DataType, DistanceFunction> chdRoot):
featureObj(featureObject), coverRadius(covRad), distToParent(distToPar), childRoot(chdRoot), colour(white)
{}

template <
        typename DataType,
        typename DistanceFunction
>
LeafObject<DataType, DistanceFunction>::LeafObject(DataType *featureObject, float distanceToParent):
featureObj(featureObject), distToParent(distanceToParent), colour(WHITE)
{}