#include "mtree.h"
#include <cmath>
#include <vector>

// CONSTRUCTORS

//Node constructor
template <typename DataType>
Node<DataType>::Node(Object<DataType> *parentObject, int sz):
parent(parentObject), colour(WHITE), size(sz), filledAmount(0)
{
    this->storedObjects = new std::vector<Object<DataType> >;
    this->storedObjects.reserve(sz+1);
}

//RoutingNode constructor
template <typename DataType>
RoutingNode<DataType>::RoutingNode(Object<DataType> *parentObject, int sz):
Node<DataType>(parentObject, sz)
{
    this->isLeaf = false;
}

//LeafNode constructor
template <typename DataType>
LeafNode<DataType>::LeafNode(Object<DataType> *parentObject, int sz):
Node<DataType>(parentObject, sz)
{
    this->isLeaf = true;
}

template <typename DataType>
Object<DataType>::Object(Node<DataType> containedNd, DataType *featureObject,
        float distanceToParent) :
featureObj(featureObject), distToParent(distanceToParent), colour(WHITE), containedNode(containedNd)
{
    coverRadius = 0.0;
    childRoot = nullptr;
}

template <typename DataType>
RoutingObject<DataType>::RoutingObject(Node<DataType> containedNd,
        DataType *featureObject, float covRad, float distToPar, RoutingNode<DataType> chdRoot) :
Object<DataType>(containedNd, featureObject, distToPar)
{
    this->coverRadius = covRad;
    this->childRoot = chdRoot;
}

// OTHER FUNCTIONS

template <typename DataType>
bool Node<DataType>::isFilled() {
    return this->filledAmount >= this->size;
}

template <typename DataType>
void Node<DataType>::insert(DataType *newObject){
    this->storedObjects.push_back(newObject);
    if(! this->isLeaf){
        float minCov = MAXFLOAT;
        int posCov = -1;
        float min = MAXFLOAT;
        int pos = -1;
        for(int i = 0; i < filledAmount; i++){
            float dist = 0.0;  // distance function access
            //find min distance in cover radius
            if(dist < this->storedObjects.at(i).coverRadius){
                minCov = dist < minCov ? dist:minCov;
                posCov = dist <= minCov ? i:posCov;
            }
            //find min distance
            min = dist <= min ? dist:min;
            pos = dist <= min ? i:pos;
        }
        //if exist a radius that cover object
        if(posCov != -1){
            this->storedObjects[posCov].insert(newObject);
        }
        //No node cover our new object, use min distance
        else{
            //set new cover radius for the closest node
            this->storedObjects.at(pos).coverRadius = min;
            this->storedObjects.at(pos).insert(newObject);
        }
    }
    else{
        //check for available space
        if(this->isFilled()){
            this->filledAmount++;
            this->storedObjects.push_back(newObject);
        }
        else{
            //TODO: split
        }
    }
}

template <typename DataType>
void Node<DataType>::split(DataType *newObject) {
    Object<DataType> parentObj = this->parent;
}

// Range queries
// Only returns the size of the ranges
// Also discards all nodes which are not white
template <typename DataType>
int Node<DataType>::range(DataType *object, float searchRadius) {
    int count = 0;
    if (this->isLeaf) {
        for (int i = 0; i < this->filledAmount; i++) {
            Object<DataType> ro = this->storedObjects[i];
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
            Object<DataType> ro = this->storedObjects[i];
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