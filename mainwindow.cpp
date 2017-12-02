#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui/QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <ostream>
// add new
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QTime>
#include <QTimer>
using namespace std;
using namespace cv;
QString filename;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "/home/binhln/Desktop",
                "All file(*.*);;JPG files (*.jpg*);; PNG File(*.png);; BMP File(*.bmp)"
                ) ;
//    QMessageBox::information(this, tr("File name"), filename);

    QPixmap pix(filename);
    ui->image->setPixmap(pix);
    ui->image->setScaledContents(true);
//    QQuickView *view = new QQuickView();
//    QWidget *container = QWidget::createWindowContainer(view, this);
//    container->setMinimumSize(300, 200);
//    container->setMaximumSize(300, 200);
//    view->setSource(QUrl("main.qml"));
//    QHBoxLayout* hbox = new QHBoxLayout(this);
//    ui->hbox->addWidget(container);


//    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
//    animation->setDuration(1000);
//    animation->setStartValue(QRect(0, 0, 100, 30));
//    animation->setEndValue(QRect(250, 250, 100, 30));

//    animation->start();
}
void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
void MainWindow::on_pushButton_2_clicked()
{
//    delay(1000);
    float rate = 0.8;
    String image = filename.toUtf8().constData();
    for (int i = 0; i < 50; i++)
    {
        rate = rate - 0.016;
        Mat mat = imread(image);
        int width = mat.size().width;
        int height = mat.size().height;
        Point center = Point(width/2, height/2);
        Point pt[4];
        pt[0] = Point(width/2, (1-rate)*height/2);
        pt[1] = Point((1+rate)*width/2 ,height/2);
        pt[2] = Point(width/2 ,(1+rate)*height/2);
        pt[3] = Point((1-rate)*width/2 ,height/2);
        fillConvexPoly(mat, pt, 4, Scalar(255,255,255));
        QPixmap pix(filename);
        cvtColor(mat, mat, CV_BGR2RGB);
        ui->gif->setPixmap(QPixmap::fromImage(QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888)));
        ui->gif->setScaledContents(true);
        cout << rate << endl;
        delay(40);
    }
//    Mat mat = imread(image);
//    int width = mat.size().width;
//    int height = mat.size().height;
//    Point center = Point(width/2, height/2);
//    Point pt[4];
//    pt[0] = Point(width/2, 0.2*height/2);
//    pt[1] = Point(1.8*width/2 ,height/2);
//    pt[2] = Point(width/2 ,1.8*height/2);
//    pt[3] = Point(0.2*width/2 ,height/2);
//    fillConvexPoly(mat, pt, 4, Scalar(255,255,255));
//    QPixmap pix(filename);
//    cvtColor(mat, mat, CV_BGR2RGB);
//    ui->gif->setPixmap(QPixmap::fromImage(QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888)));
//    ui->gif->setScaledContents(true);

}
