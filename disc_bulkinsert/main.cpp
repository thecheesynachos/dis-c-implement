#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include "disc.h"
#include "util.cpp"

int main(int argc, char** argv){
    std::ifstream infile(argv[1]);
    int dims = atoi(argv[2]);
    int count = atoi(argv[3]);
    int sz = atoi(argv[4]);
    float thr = atof(argv[5]);
    // Object<std::vector<float>> *x = &rootObj;
//    LeafNode<std::vector<float> > *mTree = new LeafNode<std::vector<float> >(8, &euclideanDistance);
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
//         for(int i=0;i<dims;i++){
//             std::cout << data->at(i) <<" ";
//         }
//         std::cout << data << std::endl;

        datapoints->push_back(data);
//        Object<std::vector<float> > *obj = new Object<std::vector<float> >(data);
//        mTree->insert(obj);
//        mTree->printTree();
    }

//    for (int i = 0; i < count; i++) {
//        std::cout << "range for obj " << i << " : " << mTree->range(datapoints->at(i), thr) << std::endl;
//    }
//    mTree->printTree();
//    delete mTree;

    // disc
    std::cout << std::endl << "DIS C METHOD" << std::endl;

    struct timeval startTime, endTime;
    long totalTime;

    gettimeofday(&startTime, NULL);
    DisC<std::vector<float> > *disC = new DisC<std::vector<float> >(datapoints, count, &euclideanDistance, sz);
    gettimeofday(&endTime, NULL);
    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L + (endTime.tv_usec - startTime.tv_usec);
    std::cout << "Time to build tree = " << (totalTime / 1000L) << " ms" << std::endl;

    gettimeofday(&startTime, NULL);
    std::vector<std::vector<float>* > *answer = disC->getCover(thr);
    gettimeofday(&endTime, NULL);
    totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L + (endTime.tv_usec - startTime.tv_usec);
    std::cout << "Time to run GreedySelect = " << (totalTime / 1000L) << " ms" << std::endl;

    std::cout << std::endl << "DIS C ANSWERS" << std::endl;
    for (int i = 0; i < answer->size(); i++) {
        for (int j = 0; j < dims; j++) {
            std::cout << answer->at(i)->at(j) << " ";
        }
        std::cout << std::endl;
    }

    delete answer;
    delete disC;
    for (int i = 0; i < count; i++) {
        delete (datapoints->at(i));
    }
    delete datapoints;
    return 0;
}