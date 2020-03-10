#include "mtree.h"
#include <cmath>
#include <vector>

// CONSTRUCTORS

//Node constructor
template <
    typename DataType,
    typename DistanceFunction
>
Node<DataType, DistanceFunction>::Node(Object<DataType, DistanceFunction> *parentObject, int sz):
parent(parentObject), colour(WHITE), size(sz), filledAmount(0)
{
    this->storedObjects = new std::vector<Object<DataType, DistanceFunction> >;
    this->storedObjects.reserve(sz+1);
}

//RoutingNode constructor
template <
    typename DataType,
    typename DistanceFunction
>
RoutingNode<DataType, DistanceFunction>::RoutingNode(Object<DataType, DistanceFunction> *parentObject, int sz):
Node<DataType, DistanceFunction>(parentObject, sz)
{
    this->isLeaf = false;
}

//LeafNode constructor
template <
    typename DataType,
    typename DistanceFunction
>
LeafNode<DataType, DistanceFunction>::LeafNode(Object<DataType, DistanceFunction> *parentObject, int sz):
Node<DataType, DistanceFunction>(parentObject, sz)
{
    this->isLeaf = true;
}

template <
        typename DataType,
        typename DistanceFunction
>
Object<DataType, DistanceFunction>::Object(Node<DataType, DistanceFunction> containedNd, DataType *featureObject,
        float distanceToParent) :
featureObj(featureObject), distToParent(distanceToParent), colour(WHITE), containedNode(containedNd)
{
    coverRadius = 0.0;
    childRoot = nullptr;
}

template <
        typename DataType,
        typename DistanceFunction
>
RoutingObject<DataType, DistanceFunction>::RoutingObject(Node<DataType, DistanceFunction> containedNd,
        DataType *featureObject, float covRad, float distToPar, RoutingNode<DataType, DistanceFunction> chdRoot) :
Object<DataType, DistanceFunction>(containedNd, featureObject, distToPar)
{
    this->coverRadius = covRad;
    this->childRoot = chdRoot;
}

// OTHER FUNCTIONS

template <
        typename DataType,
        typename DistanceFunction
>
bool Node<DataType, DistanceFunction>::isFilled() {
    return this->filledAmount >= this->size;
}

template <
        typename DataType,
        typename DistanceFunction
>
void Node<DataType, DistanceFunction>::insert(DataType *newObject){
    this->storedObjects.push_back(newObject);
    if(isLeaf){

    }
    else{

    }
}
//
//template <
//        typename DataType,
//        typename DistanceFunction
//>
//void Node<DataType, DistanceFunction>::split(DataType *newObject) {
//    Object<DataType, DistanceFunction> parentObj = this->parent;
//}

// Range queries
// Only returns the size of the ranges
// Also discards all nodes which are not white
template <
        typename DataType,
        typename DistanceFunction
>
int Node<DataType, DistanceFunction>::range(DataType *object, float searchRadius) {
    int count = 0;
    if (this->isLeaf) {
        for (int i = 0; i < this->filledAmount; i++) {
            Object<DataType, DistanceFunction> ro = this->storedObjects[i];
            if (ro.colour == WHITE) {
                float objToParent = 0.0; // compute distance from object to parent of this node
                float d = std::abs(objToParent - ro.distToParent);
                if (d <= searchRadius) {
                    float actualDist = 0.0;  // compute distance between object and ro.object
                    if (actualDist <= searchRadius) {
                        count += 1;
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < this->filledAmount; i++) {
            Object<DataType, DistanceFunction> ro = this->storedObjects[i];
            if (ro.colour == WHITE) {
                float objToParent = 0.0; // compute distance from object to parent of this node
                float d = std::abs(objToParent - ro.distToParent);
                if (d <= searchRadius + ro.coverRadius) {
                    float actualDist = 0.0;  // compute distance between object and ro.object
                    if (actualDist <= searchRadius + ro.coverRadius) {
                        count += ro.childRoot->range(object, searchRadius);
                    }
                }
            }
        }
    }
    return count;
}