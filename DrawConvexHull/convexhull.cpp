#include<convexhull.h>

ConvexHull::ConvexHull()
{

}

ConvexHull::~ConvexHull()
{

}

ConvexHull::ConvexHull(std::vector<Point<float> > & raw_point)
{
    p = raw_point;
}

void ConvexHull::SetRawInput(std::vector<Point<float> > & raw_point)
{
    p = raw_point;
}

bool ConvexHull::my_compare(const MyVec<float> &p1, const MyVec<float> &p2)
{
    float temp = p1 * p2;
    static const float small = 1e-6;
    if(fabs(temp) < small)
    {
        return p1.DotProduct(p1) < p2.DotProduct(p2);
    }
    else
    {
        return temp > 0;
    }
}

std::vector<Point<float> > ConvexHull::graham_scan()
{
    std::vector<Point<float> > ch;
    int n = p.size();
    int top = 2;
    int index = 0;
    for (int i = 1; i < n; ++i)//选出Y坐标最小的点，若Y坐标相等，选择X坐标小的点
    {
        if (p[i].y < p[index].y || (p[i].y == p[index].y && p[i].x < p[index].x))
        {
            index = i;
        }
    }
    std::swap(p[0], p[index]);

    std::vector<MyVec<float> > vec;
    for(int i = 0; i < n; i++)
    {
        vec.push_back(p[i] - p[0]);
    }
    //按极角排序
    sort(++vec.begin(),vec.end(),my_compare);
    for(int i = 0; i < 3 && i < n; i++)
    {
        ch.push_back(Point<float>(0,0) + vec[i]);
    }

    for (int i = 3; i < n; ++i)
    {
        while (top > 0 && ((Point<float>(0,0) + vec[i]) - ch[top - 1]) * (ch[top] - ch[top - 1]) >= 0)
        {
            --top;
            ch.pop_back();
        }
        ch.push_back(Point<float>(0,0) + vec[i]);
        ++top;
    }
    for(size_t i = 0; i < ch.size(); i++)
    {
        ch[i] = ch[i] + MyVec<float>(p[0].x,p[0].y);
    }
    return ch;
}
