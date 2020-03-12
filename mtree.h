#include <vector>
#include <cmath>
#include <cstdlib>

#ifndef MTREE_H
#define MTREE_H

enum Colour {
    BLACK = 0,
    GREY = 1,
    WHITE = 2,
};
template <typename DataType>
class Node;

template <typename DataType>
class RoutingNode;

template <typename DataType>
class LeafNode;

// OBJECTS

template <typename DataType>
class Object{
private:
    DataType *featureObj;
    float distToParent;
    Colour colour;
    float coverRadius;
    Node<DataType> *childRoot;
    Node<DataType> *containedNode;
    std::function<float (DataType, DataType)> distanceFunction;

public:
    Object(DataType *featureObject, float distanceToParent, float f(DataType, DataType)) :
        featureObj(featureObject), distToParent(distanceToParent), colour(WHITE), distanceFunction(f) {
        containedNode = nullptr;
        coverRadius = 0.0;
        childRoot = nullptr;
    }

    Object(DataType *featureObject, float f(DataType, DataType)) :
        featureObj(featureObject), distToParent(0.0), colour(WHITE), distanceFunction(f) {
            containedNode = nullptr;
            coverRadius = 0.0;
            childRoot = nullptr;
    }

    float distance(Object<DataType> o1) {
        return this->distanceFunction(this->featureObj, o1.featureObj);
    }

    float distance(DataType d1) {
        return this->distanceFunction(this->featureObj, d1);
    }

    Node<DataType> getChildRoot() {
        return this->childRoot;
    }

    Node<DataType> getContainedNode()  {
        return this->containedNode;
    }

    void setContainedNode(Node<DataType> nd) {
        this->containedNode = nd;
    }

    void setDistanceToParent(float dist) {
        this->distToParent = dist;
    }

    void setCoverRadius(float covRad) {
        this->coverRadius = covRad;
    }

    void replaceObjectWith(Object<DataType> newObj) {
        this->featureObj = newObj.featureObj;
        this->distToParent = newObj.distance(this->containedNode->parent);
        this->colour = WHITE;
        this->coverRadius = newObj.coverRadius;
        this->childRoot = newObj.childRoot;
        this->distanceFunction = newObj.distanceFunction;
    }

    void setColour(Colour c) {
        this->colour = c;
    }

};


template <typename DataType>
class RoutingObject : public Object<DataType> {
public:
    RoutingObject(DataType *featureObject, float covRad, float distToPar,
            float f(DataType, DataType), Node<DataType> chdRoot) :
            Object<DataType>(featureObject, distToPar, f)
    {
        this->coverRadius = covRad;
        this->childRoot = chdRoot;
    }
};

// NODE TYPES

template <typename DataType>
class Node {
private:
    void split(DataType *newObject) {
        Object<DataType> parentObj = this->parent;
        this->storedObjects.push_back(newObject);

        // selection of new pivot nodes to be added
        int rand1 = 0;
        int rand2 = 0;
        while (rand1 == rand2) {
            rand1 = std::rand() % (this->size + 1);
            rand2 = std::rand() % (this->size + 1);
        }
        Object<DataType> o1 = this->storedObjects.at(rand1);
        Object<DataType> o2 = this->storedObjects.at(rand2);

        // partition and redivide
        Node<DataType> nd1, nd2;
        if (this->isLeaf) {
            nd1 = LeafNode<DataType>(o1, this->size);
            nd2 = LeafNode<DataType>(o2, this->size);
            partition(nd1, nd2, o1, o2, this->storedObjects, this->size);
            this->convertToRoutingNode();
        } else {
            nd1 = RoutingNode<DataType>(o1, this->size);
            nd2 = RoutingNode<DataType>(o2, this->size);
            partition(nd1, nd2, o1, o2, this->storedObjects, this->size);
        }
        this->emptyNode();
        if (this->parent == nullptr) {
            this->addObject(o1);
            this->addObject(o2);
        } else {
            parentObj.replaceObjectWith(o1);
            if (this->parent->getContainedNode().isFilled()) {
                this->parent->getContainedNode().split(o2);
            } else {
                this->parent->getContainedNode().addObject(o2);
            }
        }
    }


public:
    Object<DataType> *parent;
    bool isLeaf;
    Colour colour;
    int size;
    int filledAmount;
    std::vector<Object<DataType> > storedObjects;

    bool isFilled() {
        return this->filledAmount >= this->size;
    }

    Node(Object<DataType> *parentObject, int sz) :
            parent(parentObject), colour(WHITE), size(sz), filledAmount(0)
    {
        this->storedObjects = std::vector<Object<DataType> >();
        this->storedObjects.reserve(sz+1);
    }

    int range(DataType *object, float searchRadius) {
        int count = 0;
        float objToParent = this->parent->distance(object); // compute distance from object to parent of this node
        if (this->isLeaf) {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> ro = this->storedObjects[i];
                if (ro.colour == WHITE) {
                    float d = std::abs(objToParent - ro.distToParent);
                    if (d <= searchRadius) {
                        float actualDist = ro.distance(object);  // compute distance between object and ro.object
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
                    float d = std::abs(objToParent - ro.distToParent);
                    if (d <= searchRadius + ro.coverRadius) {
                        float actualDist = ro.distance(object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius + ro.coverRadius) {
                            count += ro.getChildRoot()->range(object, searchRadius);
                        }
                    }
                }
            }
        }
        return count;
    }

    bool colourRange(Object<DataType> *object, float searchRadius) {
        bool noWhites = true;
        float objToParent = this->parent->distance(object); // compute distance from object to parent of this node
        if (this->isLeaf) {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> ro = this->storedObjects[i];
                if (ro.colour == WHITE) {
                    float d = std::abs(objToParent - ro.distToParent);
                    if (d <= searchRadius) {
                        float actualDist = ro.distance(object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius) {
                            ro.setColour(GREY);
                        } else {
                            noWhites = false;
                        }
                    } else {
                        noWhites = false;
                    }
                    if (noWhites) {
                        ro.setColour(GREY);
                    }
                }
            }
        } else {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> ro = this->storedObjects[i];
                if (ro.colour == WHITE) {
                    float d = std::abs(objToParent - ro.distToParent);
                    if (d <= searchRadius + ro.coverRadius) {
                        float actualDist = ro.distance(object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius + ro.coverRadius) {
                            bool noWhiteChild = ro.getChildRoot().colourHelper(object, searchRadius);
                            if (!noWhiteChild) {
                                noWhites = false;
                            }
                        } else {
                            noWhites = false;
                        }
                    } else {
                        noWhites = false;
                    }
                    if (noWhites) {
                        ro.setColour(GREY);
                    }
                }
            }
        }
        return noWhites;
    }

    void insert(DataType *newObject) {
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
            if(!this->isFilled()){
                this->addObject(newObject);
            }
            else{
                this->split(newObject);
            }
        }
    }

    void addObject(Object<DataType> obj) {
        if (this->filledAmount < this->size) {
            this->filledAmount++;
            this->storedObjects.push_back(obj);
            obj.setContainedNode(this);
            obj.setDistanceToParent(obj.distance(this->parent));
        } else {
            throw std::exception();
        }
    }

    void emptyNode() {
        this->storedObjects.empty();
        this->filledAmount = 0;
    }

    void convertToRoutingNode() {
        this->isLeaf = false;
    }

    void buildFromBulk(std::vector<DataType> objects);
};

template <typename DataType>
class RoutingNode : public Node<DataType> {
    public:
        RoutingNode(Object<DataType> *parentObject, int sz) :
                Node<DataType>(parentObject, sz)
        {
            this->isLeaf = false;
        }
};

template <typename DataType>
class LeafNode : public Node<DataType> {
    public:
       LeafNode(Object<DataType> *parentObject, int sz) :
               Node<DataType>(parentObject, sz)
       {
           this->isLeaf = true;
       }

       LeafNode(int sz) :
            Node<DataType>(NULL, sz)
       {
           this->isLeaf = true;
       }

};

template <typename DataType>
void partition(Node<DataType> nd1, Node<DataType> nd2, Object<DataType> o1, Object<DataType> o2,
               std::vector<Object<DataType> > objects, int sz){
    float maxDist1 = 0.0;
    float maxDist2 = 0.0;
    for (int i = 0; i < sz + 1; i++) {
        Object<DataType> obj = objects.at(i);
        float d1 = o1.distance(obj);
        float d2 = o2.distance(obj);
        if (d1 < d2) {
            nd1.addObject(obj);
            if (d1 > maxDist1) {
                maxDist1 = d1;
            }
        } else {
            nd2.addObject(obj);
            if (d2 > maxDist2) {
                maxDist2 = d2;
            }
        }
    }
    o1.setCoverRadius(maxDist1);
    o2.setCoverRadius(maxDist2);
}

#endif