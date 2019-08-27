#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <vector>
#include <point.h>
#include <GL/glu.h>
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = 0);

    ~MyGLWidget();
    void set_points(const std::vector<Point<float> > &_points, const std::vector<Point<float> > &_raw_points);
protected:

    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void draw_point();

private:
    std::vector<Point<float> > points, raw_points, raw_points_scal;
    bool mFullScreen;
};

#endif // MYGLWIDGET_H
