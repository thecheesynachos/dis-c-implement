#include <vector>

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
    Object(DataType *featureObject, float distanceToParent, float f(DataType, DataType));
    Object(DataType *featureObject, float f(DataType, DataType));
    float distance(Object<DataType> o1);
    float distance(DataType d1);
    Node<DataType> getChildRoot();
    Node<DataType> getContainedNode();
    void setContainedNode(Node<DataType> nd);
    void setDistanceToParent(float dist);
    void setCoverRadius(float covRad);
    void replaceObjectWith(Object<DataType> newObj);
    void setColour(Colour c);
};


template <typename DataType>
class RoutingObject : public Object<DataType> {
public:
    RoutingObject(DataType *featureObject, float covRad, float distToPar,
            float f(DataType, DataType), Node<DataType> chdRoot);
};

// NODE TYPES

template <typename DataType>
class Node {
private:
    void split(DataType *newObject);

public:
    Object<DataType> *parent;
    bool isLeaf;
    Colour colour;
    int size;
    int filledAmount;
    std::vector<Object<DataType> > storedObjects;

    bool isFilled();
    Node(Object<DataType> *parentObject, int sz);
    int range(DataType *object, float searchRadius);
    bool colourRange(Object<DataType> *object, float searchRadius);
    void insert(DataType *newObject);
    void addObject(Object<DataType> obj);
    void emptyNode();
    void convertToRoutingNode();
};

template <typename DataType>
class RoutingNode : public Node<DataType> {
    public:
        RoutingNode(Object<DataType> *parentObject, int sz);
};

template <typename DataType>
class LeafNode : public Node<DataType> {
    public:
        LeafNode(Object<DataType> *parentObject, int sz);
};

#endif