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
    RoutingNode<DataType> *childRoot;
    Node<DataType> *containedNode;

public:
    Object(Node<DataType> containedNd, DataType *featureObject, float distanceToParent);
};


template <typename DataType>
class RoutingObject : public Object<DataType> {
public:
    RoutingObject(Node<DataType> containedNd, DataType *featureObject, float covRad,
            float distToPar, RoutingNode<DataType> chdRoot);
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
    void insert(DataType *newObject);
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