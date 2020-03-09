#include "mtree.h"
#include <cmath>

// CONSTRUCTORS

//Node constructor
template <
    typename DataType,
    typename DistanceFunction
>
Node<DataType, DistanceFunction>::Node(Node<DataType, DistanceFunction> *parentNode, int sz):
parent(parentNode), colour(WHITE), size(sz), filledAmount(0)
{
    this->storedObjects = new Object<DataType, DistanceFunction>[sz];
}

//RoutingNode constructor
template <
    typename DataType,
    typename DistanceFunction
>
RoutingNode<DataType, DistanceFunction>::RoutingNode(Node<DataType, DistanceFunction> *parentNode, int sz):
Node<DataType, DistanceFunction>(parentNode, sz)
{}

//LeafNode constructor
template <
    typename DataType,
    typename DistanceFunction
>
LeafNode<DataType, DistanceFunction>::LeafNode(Node<DataType, DistanceFunction> *parentNode, int sz):
Node<DataType, DistanceFunction>(parentNode, sz)
{}

template <
        typename DataType,
        typename DistanceFunction
>
Object<DataType, DistanceFunction>::Object(DataType *featureObject, float distanceToParent) :
featureObj(featureObject), distToParent(distanceToParent), colour(WHITE)
{}

template <
        typename DataType,
        typename DistanceFunction
>
RoutingObject<DataType, DistanceFunction>::RoutingObject(DataType *featureObject, float covRad, float distToPar,
                                                         RoutingNode<DataType, DistanceFunction> chdRoot) :
Object<DataType, DistanceFunction>(featureObject, distToPar), coverRadius(covRad), childRoot(chdRoot)
{}

// OTHER FUNCTIONS

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

// Range queries
// Only returns the size of the ranges
//template <
//        typename DataType,
//        typename DistanceFunction
//>
//int Node<DataType, DistanceFunction>::range(DataType *object, float searchRadius) {
//    if (this->isLeaf) {
//
//    } else {
//        int count = 0;
//        for (int i = 0; i < this->filledAmount; i++) {
//            RoutingObject<DataType, DistanceFunction> ro = this.
//            float objToParent = 0.0 // compute distance from object to parent of this node
//            float d = std::abs()
//        }
//    }
//}