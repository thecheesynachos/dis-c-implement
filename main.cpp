#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "disc.h"
#include "mtree.h"
#include "util.cpp"

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    int dims = atoi(argv[2]);
    int count = atoi(argv[3]);
    // Object<std::vector<float>> *x = &rootObj;
    LeafNode<std::vector<float> > mTree = LeafNode<std::vector<float> >(3, &euclideanDistance);
    std::vector<std::vector<float>* > *datapoints = new std::vector<std::vector<float>* >();
    datapoints->reserve(count);

    for(int i = 0; i < count; i++){
        std::vector<float> *data = new std::vector<float>();
        data->reserve(dims);
        float j;
        for(int i =0; i < dims; i++){
            infile >> j;
            data->push_back(j);
        }
         for(int i=0;i<dims;i++){
             std::cout << data->at(i) <<" ";
         }
         std::cout<<std::endl;

        datapoints->push_back(data);
        Object<std::vector<float> > *obj = new Object<std::vector<float> >(data);
        mTree.insert(obj);
    }
    // std::vector<std::vector<float>> data;
    // std::string temp;

    // while (std::getline(infile, temp)){
    //     std::istringstream buffer(temp);
    //     std::vector<float> line((std::istream_iterator<float>(buffer)),
    //                             std::istream_iterator<float>());

    //     data.push_back(line);
    // }
    delete &mTree;
    for (int i = 0; i < count; i++) {
        delete &(datapoints->at(i));
    }
    delete datapoints;
    return 0;
}