#include <QApplication>
#include <myglwidget.h>
#include <convexhull.h>
#include <vector>
void read_file(const char * filename, std::vector<Point<float> > &vec)
{
    float x,y;
    freopen(filename, "r", stdin);
    vec.clear();
    while(scanf("%f%f",&x,&y) == 2)
    {
        vec.push_back(Point<float>(x,y));
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGLWidget w;

    std::vector<Point<float> > raw_points;
    read_file("/home/song/Qt/Lesson02/in.txt", raw_points);
    ConvexHull convex;
    convex.SetRawInput(raw_points);
    w.set_points(convex.graham_scan(), raw_points);
    w.show();

    return a.exec();
}
