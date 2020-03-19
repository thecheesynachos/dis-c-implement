#include <cmath>
#include <vector>
#include <iostream>

float euclideanDistance(std::vector<float> *dataA, std::vector<float> *dataB){
//    int i = 0;
//    float sumSq = 0;
//    for (std::vector<float>::iterator it = dataA->begin(); it != dataA->end(); ++it){
//        sumSq += pow((*it) - (*dataB)[i], 2);
//    }
//    return sqrt(sumSq);

    int s = dataA->size();
    if (s > 0) {
        float sumSq = 0.0;
        for (int i = 0; i < s; i++) {
            float x = dataA->at(i) - dataB->at(i);
//            std::cout<< dataA->at(i) << " hi " << dataB->at(i) << std::endl;
            sumSq += x * x;
        }
        return sqrt(sumSq);
    } else {
        throw std::runtime_error(std::string("Vector for distance has no values"));
    }
}