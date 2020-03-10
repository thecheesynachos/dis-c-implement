#include <vector>

#ifndef MTREE_H
#define MTREE_H

enum Colour {
    BLACK = 0,
    GREY = 1,
    WHITE = 2,
};
template <
        typename DataType,
        typename DistanceFunction
>
class Node;

template <
        typename DataType,
        typename DistanceFunction
>
class RoutingNode;

// OBJECTS

template <
        typename DataType,
        typename DistanceFunction
>
class Object{
private:
    DataType *featureObj;
    float distToParent;
    Colour colour;
    float coverRadius;
    RoutingNode<DataType, DistanceFunction> *childRoot;
    Node<DataType, DistanceFunction> *containedNode;

public:
    Object(Node<DataType, DistanceFunction> containedNd, DataType *featureObject, float distanceToParent);
};


template <
        typename DataType,
        typename DistanceFunction
>
class RoutingObject : public Object<DataType, DistanceFunction> {
public:
    RoutingObject(Node<DataType, DistanceFunction> containedNd, DataType *featureObject, float covRad,
            float distToPar, RoutingNode<DataType, DistanceFunction> chdRoot);
};

// NODE TYPES

template <
    typename DataType,
    typename DistanceFunction
>
class Node {
private:
    void split(DataType *newObject);

public:
    Object<DataType, DistanceFunction> *parent;
    bool isLeaf;
    Colour colour;
    int size;
    int filledAmount;
    std::vector<Object<DataType, DistanceFunction> > storedObjects;

    bool isFilled();
    Node(Object<DataType, DistanceFunction> *parentObject, int sz);
    int range(DataType *object, float searchRadius);
    void insert(DataType *newObject);
};

template <
    typename DataType,
    typename DistanceFunction
    // typename Node
>
class RoutingNode : public Node<DataType, DistanceFunction> {
    public:
        RoutingNode(Object<DataType, DistanceFunction> *parentObject, int sz);
};

template <
    typename DataType,
    typename DistanceFunction
>
class LeafNode : public Node<DataType, DistanceFunction> {
    public:
        LeafNode(Object<DataType, DistanceFunction> *parentObject, int sz);
};

#endif