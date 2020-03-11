#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);

    for(int i = 0; i < atoi(argv[3]); i++){
        std::vector<float> data(atoi(argv[2]),0);
        for(int i =0; i < atoi(argv[2]); i++){
            infile >> data[i];
        }
        //TODO: insert into tree
        for(int i=0;i<atoi(argv[2]);i++){
        std::cout<< data[i]<<std::endl;
    }
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