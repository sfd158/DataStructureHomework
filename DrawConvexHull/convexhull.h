#ifndef CONVEXHULL_H
#define CONVEXHULL_H

//凸包-Graham扫描
#include <algorithm>
#include <vector>
#include <cmath>
#include <point.h>

class ConvexHull
{
public:
    ConvexHull();
    ConvexHull(std::vector<Point<float> > & raw_point);
    ~ConvexHull();
public:
    void SetRawInput(std::vector<Point<float> > & raw_point);
private:
    static bool my_compare(const MyVec<float> &p1, const MyVec<float> &p2);
public:
    std::vector<Point<float> > graham_scan();
private:
    std::vector<Point<float> > p;
};
#endif // CONVEXHULL_H
