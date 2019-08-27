#ifndef POINT_H
#define POINT_H
#include<cmath>
template<typename _Tp>
    class MyVec;

template<typename _Tp>
struct Point
{
    typedef _Tp value_type;
    value_type x;
    value_type y;
    Point(const value_type _x = 0,const value_type _y = 0):x(_x),y(_y){}
    //Point(const MyVec<_Tp> &rhs):x(rhs.x),y(rhs.y){}
    template<typename __Tp>
    friend Point<_Tp> operator * (const double l,const Point<__Tp> &r);

    //bool operator < (const Point<_Tp> & rhs)const;
    //bool operator == (const Point<_Tp> & rhs)const;
    //Point<_Tp> operator + (const Point<_Tp> & rhs)const;
    //Point<_Tp> operator - (const Point<_Tp> & rhs)const;
    //Point<_Tp>& operator -= (const Point<_Tp> & rhs);
};

template<typename _Tp>
class MyVec
{
public:
    typedef _Tp value_type;
//private:
    _Tp x,y;
public:
    MyVec(const value_type _x = 0,const value_type _y = 0):x(_x),y(_y){}
    ~MyVec(){}
    MyVec(const Point<_Tp> &_a, const Point<_Tp> &_b = Point<_Tp>()):x(_a.x-_b.x),y(_a.y-_b.y){}
    MyVec(const MyVec<_Tp> &_a, const MyVec<_Tp> &_b = MyVec<_Tp>()):x(_a.x-_b.x),y(_a.y-_b.y){}
    float DotProduct(const MyVec<_Tp> &rhs)const
    {
        return x*rhs.x + y*rhs.y;
    }

    float length()const
    {
        return sqrt((*this).DotProduct(*this));
    }
};

template<typename _Tp>
MyVec<_Tp> operator + (const MyVec<_Tp> & l, const MyVec<_Tp> & r)
{
    return MyVec<_Tp>(l.x+r.x, l.y+r.y);
}

template<typename _Tp>
Point<_Tp> operator + (const Point<_Tp> & l, const MyVec<_Tp> & r)
{
    return Point<_Tp>(l.x+r.x, l.y+r.y);
}

template<typename _Tp>
MyVec<_Tp> operator - (const Point<_Tp> & l, const Point<_Tp> & r)
{
    return MyVec<_Tp>(l,r);
}

template<typename _Tp>
MyVec<_Tp> operator - (const MyVec<_Tp> & l, const MyVec<_Tp> & r)
{
    return MyVec<_Tp>(l,r);
}

template<typename _Tp>
Point<_Tp> operator - (const Point<_Tp> & l, const MyVec<_Tp> & r)
{
    return MyVec<_Tp>(l.x-r.x, l.y-r.y);
}

template<typename _Tp>
Point<_Tp>& operator += (Point<_Tp> &l, const MyVec<_Tp> &r)
{
    l.x += r.x;
    l.y += r.y;
    return l;
}

template<typename _Tp>
MyVec<_Tp>& operator += (MyVec<_Tp> &l, const MyVec<_Tp> &r)
{
    l.x += r.x;
    l.y += r.y;
    return l;
}

template<typename _Tp>
MyVec<_Tp>& operator -= (Point<_Tp> & l, const Point<_Tp> & r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}

template<typename _Tp>
MyVec<_Tp>& operator - (MyVec<_Tp> & l, const MyVec<_Tp> & r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}

template<typename _Tp>
Point<_Tp>& operator - (Point<_Tp> & l, const MyVec<_Tp> & r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}

template<typename _Tp>
Point<_Tp> operator * (const float l, const Point<_Tp> &r)
{
    return Point<_Tp>(l*r.x, l*r.y);
}

template<typename _Tp>
MyVec<_Tp> operator * (const float l, const MyVec<_Tp> &r)
{
    return MyVec<_Tp>(l*r.x, l*r.y);
}

template<typename _Tp>
float operator * (const MyVec<_Tp> &l, const MyVec<_Tp> &r)
{
    return l.x*r.y - l.y*r.x;
}

template<typename _Tp>
Point<_Tp>& operator *= (Point<_Tp> &l, const MyVec<_Tp> &r)
{
    l.x *= r;
    l.y *= r;
    return l;
}

template<typename _Tp>
MyVec<_Tp>& operator *= (MyVec <_Tp> &l, const MyVec<_Tp> &r)
{
    l.x *= r;
    l.y *= r;
    return l;
}
#endif // POINT_H
