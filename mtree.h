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
class Node {
private:
    split(DataType *newObject);

public:
    DataType *featureObj;
    float distToParent;
    Node *parent;
    bool isLeaf;
    Colour colour;
    
    Node(DataType *featureObj, Node *parent, float distToParent);
    std::vector<DataType> *range(DataType *object, float searchRadius);
    void insert(DataType *newObject);
};

template <
    typename DataType,
    typename DistanceFunction
>
class RoutingNode : public Node {
public:
    float coverRadius;

    RoutingNode(DataType *featureObj, float coverRadius, Node *parent, float distToParent);
};

template <
    typename DataType,
    typename DistanceFunction
>
class LeafNode : public Node {
public:
    LeafNode(DataType *featureObj, Node *parent, float distToParent);
};

#endif