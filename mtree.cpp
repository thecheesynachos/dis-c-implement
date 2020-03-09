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
{
    this->isLeaf = false;
}

//LeafNode constructor
template <
    typename DataType,
    typename DistanceFunction
>
LeafNode<DataType, DistanceFunction>::LeafNode(Node<DataType, DistanceFunction> *parentNode, int sz):
Node<DataType, DistanceFunction>(parentNode, sz)
{
    this->isLeaf = true;
}

template <
        typename DataType,
        typename DistanceFunction
>
Object<DataType, DistanceFunction>::Object(DataType *featureObject, float distanceToParent) :
featureObj(featureObject), distToParent(distanceToParent), colour(WHITE)
{
    coverRadius = 0.0;
    childRoot = nullptr;
}

template <
        typename DataType,
        typename DistanceFunction
>
RoutingObject<DataType, DistanceFunction>::RoutingObject(DataType *featureObject, float covRad, float distToPar,
                                                         RoutingNode<DataType, DistanceFunction> chdRoot) :
Object<DataType, DistanceFunction>(featureObject, distToPar)
{
    this->coverRadius = covRad;
    this->distToParent = chdRoot;
}

// OTHER FUNCTIONS

template <
        typename DataType,
        typename DistanceFunction
>
void Node<DataType, DistanceFunction>::insert(DataType *newObject){

    if(! this->isLeaf){
        int minCov = INT_MAX;
        int posCov = -1;
        int min = INT_MAX;
        int pos = -1;
        for(int i = 0; i < filledAmount; i++){
            dist = DistanceFunction(newObject, this->storedObjects[i]);
            //find min distance in cover radius
            if(dist < this->storedObjects[i].coverRadius){
                minCov = dist < minCov ? dist:minCov;
                posCov = dist <= minCov ? i:posCov;
            }
            //find min distance
            min = dist < min ? dist:min;
            pos = dist <= min ? i:pos;
        }
        //if exist a radius that cover object
        if(posCov != -1){
            this->storedObjects[posCov].insert(newObject);
        }
        //No node cover our new object, use min distance
        else{
            //set new cover radius for the closest node
            this->storedObjects[pos].coverRadius = min;
            this.storedObjects[pos].insert(newObject);
        }
    }
    else{
        //check for available space
        if(this->filledAmount < this->size){
            this->filledAmount++;
            storedObjects[this->filledAmount] = newObject; 
        }
        else{
            //TODO: split
        }
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
//            Object<DataType, DistanceFunction> ro = this->storedObjects[i];
//            float objToParent = 0.0 // compute distance from object to parent of this node
//            float d = std::abs()
//        }
//    }
//}