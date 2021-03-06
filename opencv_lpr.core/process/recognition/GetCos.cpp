#include "GetCos.h"

double GetVectorCos(const std::vector<double>& v1, double* v2)
{
    unsigned long long v1_size = v1.size();
//        if (v1_size != v2.size())
//        {
//            return 0;
//        }

    double numerator = 0;
    double denominator_l = 0, denominator_r = 0;

    for (unsigned long long i = 0; i < v1_size; i++)
    {
        numerator += v1.at(i) * v2[i];
        denominator_l += v1.at(i) * v1.at(i);
        denominator_r += v2[i] * v2[i];
    }

    if (std::fabs(denominator_l) > 1e-23 && std::fabs(denominator_r) > 1e-23)
    {
        return numerator / (std::sqrt(denominator_l) * std::sqrt(denominator_r));
    }

    return 0;
}
