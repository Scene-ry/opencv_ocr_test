#ifndef FEATUREVECTORHELPER_H
#define FEATUREVECTORHELPER_H

#include "../Common.h"
#include <vector>

class FeatureVectorHelper
{
public:
    FeatureVectorHelper(int, int);
    void AddFeatureVectors(const Mat&, std::vector<double>&);
    void AddSlopeVector(const Mat&, std::vector<double>&);
    void AddDepthVector(const Mat&, std::vector<double>&);
    void AddInflexionVector(const Mat&, std::vector<double>&);
    void AddInnerPixelsVector(const Mat&, std::vector<double>&);

    void AddSampleDepthVectorLeft(const Mat&, std::vector<double>&);
    void AddSampleDepthVectorRight(const Mat&, std::vector<double>&);
    void AddSampleDepthVectorUp(const Mat&, std::vector<double>&);
    void AddSampleDepthVectorDown(const Mat&, std::vector<double>&);

private:
    int height, width;
};

#endif // FEATUREVECTORHELPER_H
