#include <QtWidgets>

const int LENGTH_ROAD = 600;
const int COUNT_CARS = 3;

class Road 
{
public:
    Road(double newLength, int newWidth);
    double Length;
    int Width;
};

Road::Road(double newLength, int newWidth)
{
    Length = newLength;
    Width = newWidth;
}

class Car 
{
public:
    Car(int newP, double newV, Road* ptrRoad);
    Road* _road;
    double X;
    int P;
    double V;
    
    void move();
};

Car::Car(int newP, double newV, Road* ptrRoad)
{
    _road = ptrRoad;
    X = 0;
    P = newP;
    V = newV;
}

void Car::move()
{
    X += V;
    if (X > _road->Length) 
    {
        X = 0;
    }
}

class MainWindow : public QMainWindow 
{
public:
    MainWindow(Car* ptrCars[]);
    void updateCars();
    
private:
    void paintEvent(QPaintEvent*);
    Car** _cars;
    int timerInterval;
    QTimer* timer;
};

MainWindow::MainWindow(Car* ptrCars[])
{
    _cars = ptrCars;
    resize(LENGTH_ROAD, 500);
    setWindowTitle("Racing Labels v10.1");
    
    timer = new QTimer(this);
    timer->setInterval(200);
    timer->start();
    
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCars);
}

void MainWindow::updateCars()
{
    for (int i = 0; i < COUNT_CARS; i++)
    {
        _cars[i]->move();
    }
    
    update();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPen redPen4(Qt::black, 2, Qt::SolidLine);
    painter.setPen(redPen4);
    
    QBrush redBrush(Qt::red, Qt::SolidPattern);
    painter.setBrush(redBrush);
    painter.drawEllipse(_cars[0]->X, 100, 120, 80);
    
    QBrush yellowBrush(Qt::yellow, Qt::SolidPattern);
    painter.setBrush(yellowBrush);
    painter.drawEllipse(_cars[1]->X, 300, 120, 80);
    
    QBrush greenBrush(Qt::blue, Qt::SolidPattern);
    painter.setBrush(greenBrush);
    painter.drawEllipse(_cars[2]->X, 200, 120, 80);
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Road road(LENGTH_ROAD, 3);
    
    Car* cars[COUNT_CARS];
    for (int i = 0; i < COUNT_CARS; i++)
    {
        cars[i] = new Car(i, 2 * (i + 1), &road);
    }
    
    MainWindow mainWin(cars);
    mainWin.show();
    
    return app.exec();
}
