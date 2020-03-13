#include <math.h>
#include <cmath>
#include <vector>

float euclideanDistance(std::vector<float> *dataA, std::vector<float> *dataB){
    int i = 0;
    float sumSq = 0;
    for (std::vector<float>::iterator it = dataA->begin(); it != dataA->end(); ++it){
        sumSq = pow((*it) - (*dataB)[i], 2);
    }
    return sqrt(sumSq);
}