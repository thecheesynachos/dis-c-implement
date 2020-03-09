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
class RoutingNode;

template <
        typename DataType,
        typename DistanceFunction
>
class RoutingObject{
private:
    DataType *featureObj;
    float coverRadius;
    float distToParent;
    RoutingNode<DataType, DistanceFunction> *childRoot;
    Colour colour;

public:
    RoutingObject(DataType *featureObject, float covRad, float distToPar, RoutingNode<DataType, DistanceFunction> chdRoot);
};

template <
        typename DataType,
        typename DistanceFunction
>
class LeafObject{
    private:
        DataType *featureObj;
        float distToParent;
        Colour colour;

    public:
        LeafObject(DataType *featureObject, float distanceToParent);
};

template <
    typename DataType,
    typename DistanceFunction
>
class Node {
private:
    void split(DataType *newObject);

public:
    Node *parent;
    bool isLeaf;
    Colour colour;
    int size;
    int filledAmount;
    
    Node(Node<DataType, DistanceFunction> *parentNode, int sz);
    int range(DataType *object, float searchRadius);
    void insert(DataType *newObject);
};

template <
    typename DataType,
    typename DistanceFunction
    // typename Node
>
class RoutingNode : public Node<DataType, DistanceFunction> {
    private:
        RoutingObject<DataType, DistanceFunction> *storedRoutingObjects;

    public:
        RoutingNode(Node<DataType, DistanceFunction> *parentNode, int sz);
};

template <
    typename DataType,
    typename DistanceFunction
>
class LeafNode : public Node<DataType, DistanceFunction> {
    private:
        LeafObject<DataType, DistanceFunction> *storedLeafObjects;

    public:
        LeafNode(Node<DataType, DistanceFunction> *parentNode, int sz);
};

#endif