#include <vector>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <set>

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
//    std::function<float (DataType, DataType)> distanceFunction;

public:
    Object() {
        featureObj = nullptr;
        colour = WHITE;
        distToParent = 0.0;
        containedNode = nullptr;
        coverRadius = 0.0;
        childRoot = nullptr;
    }

    Object(DataType *featureObject, float distanceToParent) :
        featureObj(featureObject), distToParent(distanceToParent), colour(WHITE) {
        containedNode = nullptr;
        coverRadius = 0.0;
        childRoot = nullptr;
    }

    explicit Object(DataType *featureObject) :
        featureObj(featureObject), distToParent(0.0), colour(WHITE){
            containedNode = nullptr;
            coverRadius = 0.0;
            childRoot = nullptr;
    }

    ~Object() {
        delete this->childRoot;
    }

//    float distance(Object<DataType> *o1) {
//        return this->distanceFunction(this->featureObj, o1.featureObj);
//    }
//
//    float distance(DataType *d1) {
//        return this->distanceFunction(this->featureObj, d1);
//    }

    DataType *getFeatureObj(){
        return this->featureObj;
    }

    Node<DataType> *getChildRoot() {
        return this->childRoot;
    }

    void setChildRoot(Node<DataType> *rt) {
        this->childRoot = rt;
    }

    Node<DataType> *getContainedNode()  {
        return this->containedNode;
    }

    void setContainedNode(Node<DataType> *nd) {
        this->containedNode = nd;
    }

    void setDistanceToParent(float dist) {
        this->distToParent = dist;
    }

    float getCoverRadius() {
        return this->coverRadius;
    }

    void setCoverRadius(float covRad) {
        this->coverRadius = covRad;
    }

    void replaceObjectWith(Object<DataType> *newObj) {
        Node<DataType> *nodeAdded = this->getContainedNode();
        this->featureObj = newObj->featureObj;
        this->distToParent = nodeAdded->distance(nodeAdded->parent, newObj);
        this->colour = WHITE;
        this->coverRadius = newObj->coverRadius;
        this->childRoot = newObj->childRoot;
    }

    void setColour(Colour c) {
        this->colour = c;
    }

};


template <typename DataType>
class RoutingObject : public Object<DataType> {
public:
    RoutingObject(DataType *featureObject, float covRad, float distToPar,
            float (*f)(DataType, DataType), Node<DataType> *chdRoot) :
            Object<DataType>(featureObject, distToPar, f)
    {
        this->coverRadius = covRad;
        this->childRoot = chdRoot;
    }

    ~RoutingObject() {
        delete this->childRoot;
    }
};

// NODE TYPES

template <typename DataType>
class Node {
private:
    void split(Object<DataType> *newObject) {
//        std::cout<< "split";
//        for (int i = 0; i < this->storedObjects->size(); i++){
//            std::cout<< storedObjects->at(i)->getFeatureObj()->at(0) << std::endl;;
//        }
        Object<DataType> *parentObj = this->parent;
        this->storedObjects->push_back(newObject);

        // selection of new pivot nodes to be added
        int rand1 = 0;
        int rand2 = 0;
        while (rand1 == rand2) {
            rand1 = std::rand() % (this->size + 1);
            rand2 = std::rand() % (this->size + 1);
        }
        Object<DataType> *o1 = this->storedObjects->at(rand1);
        Object<DataType> *o2 = this->storedObjects->at(rand2);

        // partition and redivide
        if (this->isLeaf) {
            LeafNode<DataType> *nd1 = new LeafNode<DataType>(o1, this->size, this->distanceFunction);
            LeafNode<DataType> *nd2 = new LeafNode<DataType>(o2, this->size, this->distanceFunction);
            partition(nd1, nd2, o1, o2, this->storedObjects, this->size);
            o1->setChildRoot(nd1);
            o2->setChildRoot(nd2);
            this->convertToRoutingNode();
        } else {
            RoutingNode<DataType> *nd1 = new RoutingNode<DataType>(o1, this->size, this->distanceFunction);
            RoutingNode<DataType> *nd2 = new RoutingNode<DataType>(o2, this->size, this->distanceFunction);
            partition(nd1, nd2, o1, o2, this->storedObjects, this->size);
            o1->setChildRoot(nd1);
            o2->setChildRoot(nd2);
        }
        this->emptyNode();
        if (this->parent == nullptr) {
            this->addObject(o1);
            this->addObject(o2);
        } else {
            parentObj->replaceObjectWith(o1);
            if (this->parent->getContainedNode()->isFilled()) {
                this->parent->getContainedNode()->split(o2);
            } else {
                this->parent->getContainedNode()->addObject(o2);
            }
        }
    }


public:
    Object<DataType> *parent;
    bool isLeaf;
    Colour colour;
    int size;
    int filledAmount;
    std::vector<Object<DataType>* > *storedObjects;
    float (*distanceFunction)(DataType*, DataType*);

    bool isFilled() {
        return this->filledAmount >= this->size;
    }
    
    float distance(Object<DataType> *o1, Object<DataType> *o2) {
        if (!o1 || !o2){
            return 0.0;
        } else {
            return this->distanceFunction(o1->getFeatureObj(), o2->getFeatureObj());
        }
    }

    // float distance(Object<DataType> *o1, DataType *o2) {
    //     return this->distanceFunction(o1.getFeatureObj(), o2);
    // }

    Node(Object<DataType> *parentObject, int sz, float (*f)(DataType*, DataType*)) :
            parent(parentObject), colour(WHITE), size(sz), filledAmount(0), distanceFunction(f)
    {
        this->storedObjects = new std::vector<Object<DataType>* >();
        this->storedObjects->reserve(sz+1);
    }

    ~Node() {
        for (int i = 0; i < storedObjects->size(); i++) {
            delete storedObjects->at(i);
        }
    }

    int range(DataType *object, float searchRadius) {
        int count = 0;
        float objToParent = this->distance(this->parent, object); // compute distance from object to parent of this node
        if (this->isLeaf) {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> *ro = this->storedObjects[i];
                if (ro->colour == WHITE) {
                    float d = std::abs(objToParent - ro->distToParent);
                    if (d <= searchRadius) {
                        float actualDist = this->distance(ro, object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius) {
                            count += 1;
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> *ro = this->storedObjects[i];
                if (ro->colour == WHITE) {
                    float d = std::abs(objToParent - ro->distToParent);
                    if (d <= searchRadius + ro->coverRadius) {
                        float actualDist = this->distance(ro, object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius + ro->coverRadius) {
                            count += ro->getChildRoot()->range(object, searchRadius);
                        }
                    }
                }
            }
        }
        return count;
    }

    bool colourRange(Object<DataType> *object, float searchRadius) {
        bool noWhites = true;
        float objToParent = this->distance(this->parent, object); // compute distance from object to parent of this node
        if (this->isLeaf) {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> *ro = this->storedObjects[i];
                if (ro->colour == WHITE) {
                    float d = std::abs(objToParent - ro->distToParent);
                    if (d <= searchRadius) {
                        float actualDist = this->distance(ro, object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius) {
                            ro->setColour(GREY);
                        } else {
                            noWhites = false;
                        }
                    } else {
                        noWhites = false;
                    }
                    if (noWhites) {
                        ro->setColour(GREY);
                    }
                }
            }
        } else {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> *ro = this->storedObjects[i];
                if (ro->colour == WHITE) {
                    float d = std::abs(objToParent - ro->distToParent);
                    if (d <= searchRadius + ro->coverRadius) {
                        float actualDist = this->distance(ro, object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius + ro->coverRadius) {
                            bool noWhiteChild = ro->getChildRoot().colourHelper(object, searchRadius);
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
                        ro->setColour(GREY);
                    }
                }
            }
        }
        return noWhites;
    }
    void bulkInsert(std::vector<DataType*> *objects){
        //inserting object is less than object size
        if(objects->size() <= this->size){
            //create objects for leaf node
            this->isLeaf = true;
            //iterate add object to leaf node
            for (Datatype::iterator it = objects->begin(); it != objects->end(); ++it){
                this->addObject(new Object<DataType>(it));
            }
        }
        else{
            // std::vector<int> initial(this->size, 0);
            std::set<int, std::greater<int>> initial;
            //generate random index
            while(initial.size() != this->size){
                int rand =  std::rand() % (objects->size());
                if(!initial.contains(rand)){
                    initial.insert(rand);
                }
            }
            //create initial node
            for (int elm : initial){
                //add random picked elm as routingObj
                RoutingObject<DataType> toAdd = new RoutingObject<DataType>(objects[elm], 0.0, this->distanceFunction(this->parent->featureObj, objects[elm]), this->distanceFunction, nullptr);
                toAdd->setChildRoot(new Node(toAdd, this->size, this->distanceFunction));
                this->addObject(toAdd);
            }
            std::vector<std::vector<DataType*>*> partition = new std::vector<std::vector<DataType*>*>(this->size, nullptr);
            for(int i=0; i < this->size; i++){
                std::vector<DataType*> *subPar = new std::vector<DataType*>();
                partition[i] = subPar;
            }
            for (Datatype::iterator it = objects->begin(); it != objects->end(); ++it){
                float min = MAXFLOAT;
                int idx = -1;
                for(int i = 0; i < this->size; i++){
                    float dist = this -> distanceFunction(it, this->storedObjects[i]->featuredObject);
                    idx = dist < min ? i:idx;
                    min = dist < min ? dist:min;
                }
                partition[idx].add(it);
                    //insert to the nearest spot
                    //call recursively
            }
            //might be able to parallel here
            for (int i = 0; i < this->size; i++){
                this->storedObjects[i]->childRoot->bulkInsert(partition[i]);
                //free
                delete partition[i];
            }
            delete partition;
        }
    }
    void insert(Object<DataType> *newObject) {
//        std::cout<< "insert";
//        for (int i = 0; i < this->storedObjects->size(); i++){
//            std::cout<< storedObjects->at(i)->getFeatureObj() << std::endl;;
//        }
        if(!(this->isLeaf)){
            float minCov = MAXFLOAT;
            int posCov = -1;
            float min = MAXFLOAT;
            int pos = -1;
            for(int i = 0; i < filledAmount; i++){
                float dist = this->distance(newObject, this->storedObjects->at(i));  // distance function access
                //find min distance in cover radius
                if(dist < this->storedObjects->at(i)->getCoverRadius()){
                    minCov = dist < minCov ? dist:minCov;
                    posCov = dist <= minCov ? i:posCov;
                }
                //find min distance
                min = dist <= min ? dist:min;
                pos = dist <= min ? i:pos;
            }
            //if exist a radius that cover object
            if(posCov != -1){
                this->storedObjects->at(pos)->getChildRoot()->insert(newObject);
            }
                //No node cover our new object, use min distance
            else{
                //set new cover radius for the closest node
                this->storedObjects->at(pos)->setCoverRadius(min);
                this->storedObjects->at(pos)->getChildRoot()->insert(newObject);
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

    void addObject(Object<DataType> *obj) {
        if (this->filledAmount < this->size) {
            this->filledAmount++;
            this->storedObjects->push_back(obj);
            obj->setContainedNode(this);
            obj->setDistanceToParent(this->distance(obj, this->parent));
        } else {
            throw std::runtime_error(std::string("Node is full"));
        }
    }

    void addObject(Object<DataType> *obj, float d1, float d2) {
        this->addObject(obj);
    }

    void emptyNode() {
        this->storedObjects->empty();
        this->filledAmount = 0;
    }

    void convertToRoutingNode() {
        this->isLeaf = false;
    }

    // void buildFromBulk(std::vector<DataType> objects);
};

template <typename DataType>
class RoutingNode : public Node<DataType> {
    public:
        RoutingNode(Object<DataType> *parentObject, int sz, float (*f)(DataType*, DataType*)) :
                Node<DataType>(parentObject, sz, f)
        {
            this->isLeaf = false;
        }

    ~RoutingNode() {
        for (int i = 0; i < this->storedObjects->size(); i++) {
            delete this->storedObjects->at(i);
        }
    }
};

template <typename DataType>
class LeafNode : public Node<DataType> {
    public:
       LeafNode(Object<DataType> *parentObject, int sz, float (*f)(DataType*, DataType*)) :
               Node<DataType>(parentObject, sz, f)
       {
           this->isLeaf = true;
       }

       LeafNode(int sz, float (*f)(DataType*, DataType*)) :
            Node<DataType>(nullptr, sz, f)
       {
           this->isLeaf = true;
       }

        ~LeafNode() {
            for (int i = 0; i < this->storedObjects->size(); i++) {
                delete this->storedObjects->at(i);
            }
        }

};

template <typename DataType>
void partition(Node<DataType> *nd1, Node<DataType> *nd2, Object<DataType> *o1, Object<DataType> *o2,
               std::vector<Object<DataType>* > *objects, int sz){
//    std::cout<< "partition";
    float maxDist1 = 0.0;
    float maxDist2 = 0.0;
    for (int i = 0; i < sz + 1; i++) {
        Object<DataType> *obj = objects->at(i);
        float d1 = nd1->distance(obj, o1);
        float d2 = nd2->distance(obj, o2);
        if (d1 < d2) {
            nd1->addObject(obj, d1, d2);
            if (d1 > maxDist1) {
                maxDist1 = d1;
            }
        } else {
            nd2->addObject(obj, d1, d2);
            if (d2 > maxDist2) {
                maxDist2 = d2;
            }
        }
    }
    o1->setCoverRadius(maxDist1);
    o2->setCoverRadius(maxDist2);
}

#endif