#include <QApplication>
#include <myglwidget.h>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent), mFullScreen(false)
{
    showNormal();
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::set_points(const std::vector<Point<float> > &_points, const std::vector<Point<float> >  & _raw_points)
{
    static const float INF = 1e30;
    float min_x = INF,min_y = INF,max_x = -INF,max_y = -INF;
    for(size_t i = 0; i < _points.size(); i++)
    {
        if(_points[i].x < min_x)
            min_x = _points[i].x;
        if(_points[i].x > max_x)
            max_x = _points[i].x;
        if(_points[i].y < min_y)
            min_y = _points[i].y;
        if(_points[i].y > max_y)
            max_y = _points[i].y;
    }
    float m_size = std::max(max_x - min_x, max_y - min_y);
    points = _points;
    raw_points = _raw_points;
    raw_points_scal = _raw_points;
    if(m_size != 0)
    {
        for(size_t i = 0; i < points.size(); i++)
        {
            points[i].x = (points[i].x - min_x - 2.0f) * 4 / m_size;
            points[i].y = (points[i].y - min_y - 2.0f) * 4 / m_size;
        }

        for(size_t i = 0; i < raw_points_scal.size(); i++)
        {
            raw_points_scal[i].x = (raw_points_scal[i].x - min_x - 2.0f) * 4 / m_size;
            raw_points_scal[i].y = (raw_points_scal[i].y - min_y - 2.0f) * 4 / m_size;
        }
    }
}

void MyGLWidget::draw_point()
{
    static const float small_size = 4e-2;
    char buf[20];
    for(size_t i = 0; i < raw_points_scal.size(); i++)
    {
        glColor3f(1.0f,0.0f,0.0f);// 设置当前色为红色
        glBegin(GL_QUADS);	// 绘制正方形
            glVertex3f(raw_points_scal[i].x - small_size, raw_points_scal[i].y + small_size, 0.0f);	// 左上
            glVertex3f(raw_points_scal[i].x + small_size, raw_points_scal[i].y + small_size, 0.0f);	// 右上
            glVertex3f(raw_points_scal[i].x + small_size, raw_points_scal[i].y - small_size, 0.0f);	// Right_Down
            glVertex3f(raw_points_scal[i].x - small_size, raw_points_scal[i].y - small_size, 0.0f);	// Left_Downh
        glEnd(); // 正方形绘制结束
        glColor3f(1.0f,1.0f,1.0f);
        sprintf(buf,"(%.2f,%.2f)",raw_points[i].x,raw_points[i].y);
        renderText(raw_points_scal[i].x, raw_points_scal[i].y,0.0f, buf);
    }
}

void MyGLWidget::resizeGL(int width, int height)
{
    if (height == 0)
    { // 防止被零除
        height = 1; // 将高设为1
    }

    glViewport(0, 0, width, height); //重置当前的视口
    glMatrixMode(GL_PROJECTION);// 选择投影矩阵
    glLoadIdentity();// 重置投影矩阵
    //设置视口的大小
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵
    glLoadIdentity(); // 重置模型观察矩阵
}

void MyGLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH); // 启用阴影平滑
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // 蓝色背景.最后一个参数是Alpha值

    glClearDepth(1.0f);	// 设置深度缓存
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glDepthFunc(GL_LEQUAL);	// 所作深度测试的类型

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 告诉系统对透视进行修正
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除屏幕及深度缓存
    glLoadIdentity();	// 重置当前的模型观察矩阵

    glTranslatef(0.0f,0.0f,-6.0f);	// 左移 1.5 单位，并移入屏幕 6.0
    glColor3f(0.4f,1.0f,0.0f);
    glBegin(GL_POLYGON);
        for(size_t i = 0; i < points.size(); i++)
        {
            glVertex3f(points[i].x, points[i].y, 0.0f);
        }
    glEnd(); //绘制结束

    draw_point();
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_F2:
    {
        mFullScreen = !mFullScreen;
        if(mFullScreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        updateGL();
        break;
    }
    case Qt::Key_Escape:
    {
        qApp->exit();
        break;
    }
    }
}
