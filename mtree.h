#include <vector>
#include <cmath>
#include <cstdlib>
#include <functional>

#ifndef MTREE_H
#define MTREE_H

float EPSILON = 0.1;

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
//        std::cout << "create obj a " << featureObject << std::endl;
        containedNode = nullptr;
        coverRadius = 0.0;
        childRoot = nullptr;
    }

    explicit Object(DataType *featureObject) :
        featureObj(featureObject), distToParent(0.0), colour(WHITE){
//            std::cout << "create obj b " << featureObject << std::endl;
            containedNode = nullptr;
            coverRadius = 0.0;
            childRoot = nullptr;
    }

    ~Object() {
        if (this->childRoot != nullptr) {
            delete this->childRoot;
        }
    }

//    float distance(Object<DataType> *o1) {
//        return this->distanceFunction(this->featureObj, o1.featureObj);
//    }
//
//    float distance(DataType *d1) {
//        return this->distanceFunction(this->featureObj, d1);
//    }

    DataType *getFeatureObj(){
//        std::cout << "access obj " << this->featureObj << std::endl;
        return this->featureObj;
    }

    void setFeatureObject(DataType *obj) {
//        std::cout << "set obj " << obj << std::endl;
        this->featureObj = obj;
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

    float getDistanceToParent() {
        return this->distToParent;
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

    Colour getColour() {
        return this->colour;
    }

    void setColour(Colour c) {
        this->colour = c;
    }

};


template <typename DataType>
class RoutingObject : public Object<DataType> {
public:
    RoutingObject(DataType *featureObject, float covRad, float distToPar, Node<DataType> *chdRoot) :
            Object<DataType>(featureObject, distToPar)
    {
        this->setCoverRadius(covRad);
        this->setChildRoot(chdRoot);
    }

    ~RoutingObject() {
        if (this->getChildRoot() != nullptr) {
            delete this->getChildRoot();
        }
    }
};

// NODE TYPES

template <typename DataType>
class Node {
private:

    void removeObject(Object<DataType> *obj) {
        this->storedObjects->erase(std::remove(this->storedObjects->begin(),
                this->storedObjects->end(), obj), this->storedObjects->end());
        this->filledAmount = this->storedObjects->size();
    }

    void split(Object<DataType> *newObject) {
//        for (int i = 0; i < this->storedObjects->size(); i++){
//            std::cout<< storedObjects->at(i)->getFeatureObj()->at(0) << std::endl;
//        }
        Object<DataType> *parentObj = this->parent;
//        std::cout<< "split " << this << " parent object " << parentObj->getFeatureObj() << std::endl;
        std::vector<Object<DataType>* > *objectsList = this->storedObjects;
        objectsList->push_back(newObject);

        // selection of new pivot nodes to be added
        int rand1 = 0;
        int rand2 = 0;
        while (rand1 == rand2) {
            rand1 = std::rand() % (this->size + 1);
            rand2 = std::rand() % (this->size + 1);
        }
        Object<DataType> *o1 = this->storedObjects->at(rand1);
        Object<DataType> *o2 = this->storedObjects->at(rand2);

        // create routing objects for the new nodes
        RoutingObject<DataType> *ro1 = new RoutingObject<DataType>(o1->getFeatureObj(), 0.0, 0.0, nullptr);
        RoutingObject<DataType> *ro2 = new RoutingObject<DataType>(o2->getFeatureObj(), 0.0, 0.0, nullptr);

        // partitioning
        Node<DataType> *nd1, *nd2;
        if (this->isLeaf) {
            nd1 = new LeafNode<DataType>(ro1, this->size, this->distanceFunction);
            nd2 = new LeafNode<DataType>(ro2, this->size, this->distanceFunction);
        } else {
            nd1 = new RoutingNode<DataType>(ro1, this->size, this->distanceFunction);
            nd2 = new RoutingNode<DataType>(ro2, this->size, this->distanceFunction);
        }
        partition(nd1, nd2, o1, o2, ro1, ro2, objectsList);

        if (parentObj == nullptr) {
            this->storedObjects->clear();
            ro1->setChildRoot(nd1);
            nd1->parent = ro1;
            ro2->setChildRoot(nd2);
            nd2->parent = ro2;
            this->addObject(ro1);
            this->addObject(ro2);
            this->convertToRoutingNode();
//            std::cout << "a " << ro1->getFeatureObj() << " " << ro2->getFeatureObj() << std::endl;
        } else {
            // replace the parent for this node with that from ro1
//            this->colour = WHITE;
//            this->storedObjects = nd1->storedObjects;
//            this->filledAmount = 1;
//            this->parent->setFeatureObject(ro1->getFeatureObj());
//            this->parent->setCoverRadius(ro1->getCoverRadius());
//            this->parent->setDistanceToParent(ro1->getDistanceToParent());
//            this->parent->setChildRoot(nd1);
            ro1->setChildRoot(nd1);
            Node<DataType> *parentNode = parentObj->getContainedNode();
            parentNode->removeObject(parentObj);
            parentNode->addObject(ro1);
            // add ro2 to parent node
//            std::cout << "b " << this->parent->getFeatureObj() << " " << ro2->getFeatureObj() << std::endl;
            ro2->setChildRoot(nd2);
            if (parentNode->isFilled()) {
                parentNode->split(ro2);
            } else{
                parentNode->addObject(ro2);
            }
            // deallocate ro1 and nd1 stuff
//            ro1->setChildRoot(nullptr);
//            ro1->setFeatureObject(nullptr);
//            delete ro1;
            this->emptyNode();
            delete this;
        }

    }

    void printTreeHelper(int step) {
        std::cout << std::string(step, '\t') << "Node: " << this->parent->getFeatureObj() << ", DistToParent = "
                  << this->parent->getDistanceToParent() << std::endl;
        if (!this->isLeaf) {
            for (int i = 0; i < this->storedObjects->size(); i++) {
                this->storedObjects->at(i)->getContainedNode()->printTreeHelper(step + 1);
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

    float distance(Object<DataType> *o1, DataType *d2) {
        if (!o1 || !d2){
            return 0.0;
        } else {
            return this->distanceFunction(o1->getFeatureObj(), d2);
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
        if (this->storedObjects != nullptr) {
            for (int i = 0; i < this->storedObjects->size(); i++) {
                if (this->storedObjects->at(i) != nullptr) {
                    delete this->storedObjects->at(i);
                }
            }
        }
        delete this->storedObjects;
    }

    int range(DataType *object, float searchRadius) {
        int count = 0;
        float objToParent = this->distance(this->parent, object); // compute distance from object to parent of this node
        if (this->isLeaf) {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> *ro = this->storedObjects->at(i);
                if (ro->getColour() == WHITE) {
                    float d = std::abs(objToParent - ro->getDistanceToParent());
                    if (d <= searchRadius + EPSILON) {
                        float actualDist = this->distance(ro, object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius) {
                            count += 1;
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < this->filledAmount; i++) {
                Object<DataType> *ro = this->storedObjects->at(i);
                if (ro->getColour() == WHITE) {
                    float d = std::abs(objToParent - ro->getDistanceToParent());
                    if (d <= searchRadius + ro->getCoverRadius() + EPSILON) {
                        float actualDist = this->distance(ro, object);  // compute distance between object and ro.object
                        if (actualDist <= searchRadius + ro->getCoverRadius() + EPSILON) {
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
                Object<DataType> *ro = this->storedObjects->at(i);
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
                Object<DataType> *ro = this->storedObjects->at(i);
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

    void insert(Object<DataType> *newObject) {
//        std::cout<< "insert " << this << std::endl;
//        std::cout<< "size" << this->storedObjects->size() << std::endl;
        if(!(this->isLeaf)){
//            std::cout<< "not leaf"<< " ";
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
//                std::cout << "insert at a " << posCov << " " << this->storedObjects->size() << std::endl;
                this->storedObjects->at(posCov)->getChildRoot()->insert(newObject);
            }
                //No node cover our new object, use min distance
            else{
                //set new cover radius for the closest node
                this->storedObjects->at(pos)->setCoverRadius(min);
//                std::cout<< this->storedObjects->at(pos)->getChildRoot() << std::endl;
//                std::cout << "insert at b " << pos << " " << this->storedObjects->size() << std::endl;
                this->storedObjects->at(pos)->getChildRoot()->insert(newObject);
            }
        }
        else{
//            std::cout<< "leaf"<< std::endl;
            //check for available space
            if(this->storedObjects->size() < this->size){
//                std::cout << "insert at c " << this->storedObjects->size() << std::endl;
                this->addObject(newObject);
            }
            else{
//                std::cout << "split at d " << this->storedObjects->size() << std::endl;
                this->split(newObject);
            }
        }
    }

    void addObject(Object<DataType> *obj) {
        this->filledAmount = this->storedObjects->size();
        if (this->filledAmount < this->size) {
            this->filledAmount++;
            this->storedObjects->push_back(obj);
            obj->setContainedNode(this);
            obj->setDistanceToParent(this->distance(obj, this->parent));
        } else {
            throw std::runtime_error(std::string("Node is full"));
        }
    }

    void emptyNode() {
        this->storedObjects->clear();
        this->filledAmount = 0;
    }

    void convertToRoutingNode() {
        this->isLeaf = false;
    }

    void printTree() {
        this->printTreeHelper(0);
    }

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
        if (this->storedObjects != nullptr) {
            for (int i = 0; i < this->storedObjects->size(); i++) {
                if (this->storedObjects->at(i) != nullptr) {
                    delete this->storedObjects->at(i);
                }
            }
        }
        delete this->storedObjects;
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
            if (this->storedObjects != nullptr) {
                for (int i = 0; i < this->storedObjects->size(); i++) {
                    if (this->storedObjects->at(i) != nullptr) {
                        delete this->storedObjects->at(i);
                    }
                }
            }
            delete this->storedObjects;
        }

};

template <typename DataType>
void partition(Node<DataType> *nd1, Node<DataType> *nd2, Object<DataType> *o1, Object<DataType> *o2,
               Object<DataType> *ro1, Object<DataType> *ro2, std::vector<Object<DataType>* > *objects){
//    std::cout<< "partition " << nd1 << " " << nd2 << std::endl;
    float maxDist1 = 0.0;
    float maxDist2 = 0.0;
    int sz = objects->size();
    for (int i = 0; i < sz; i++) {
        Object<DataType> *obj = objects->at(i);
//        std::cout<< obj->getFeatureObj() << std::endl;
        float d1 = nd1->distance(obj, o1);
        float d2 = nd2->distance(obj, o2);
        if (d1 < d2) {
            nd1->addObject(obj);
            if (d1 > maxDist1) {
                maxDist1 = d1;
            }
        } else {
            nd2->addObject(obj);
            if (d2 > maxDist2) {
                maxDist2 = d2;
            }
        }
    }
    ro1->setCoverRadius(maxDist1);
    ro2->setCoverRadius(maxDist2);
}

#endif