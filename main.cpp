#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "disc.h"
#include "mtree.h"

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);

    // LeafNode<std::vector<float> > mTree = LeafNode<std::vector<float> >(NULL, 5);
    LeafNode<std::vector<float> > mTree = LeafNode<std::vector<float> >(5);

    for(int i = 0; i < atoi(argv[3]); i++){
        std::vector<float> data = std::vector<float>(atoi(argv[2]),0);
        for(int i =0; i < atoi(argv[2]); i++){
            infile >> data[i];
        }
        for(int i=0;i<atoi(argv[2]);i++){
            std::cout<< data[i]<<" ";
        }
        std::cout<<std::endl;
//        mTree.insert(&data);
    }
    // std::vector<std::vector<float>> data;
    // std::string temp;

    // while (std::getline(infile, temp)){
    //     std::istringstream buffer(temp);
    //     std::vector<float> line((std::istream_iterator<float>(buffer)),
    //                             std::istream_iterator<float>());

    //     data.push_back(line);
    // }
    return 0;
}