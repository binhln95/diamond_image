#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui/QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <ostream>
#include <QTime>
#include <QTimer>
#include <QLineEdit>
#include <typeinfo>
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

    QPixmap pix(filename);
    ui->image->setPixmap(pix);
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
    QString QnumberFrame = ui->numberFrame->text();
    int numberFrame = QnumberFrame.toInt();
    cout << typeid(numberFrame).name() << endl;
    QString QSeconds = ui->seconds->text() ;
    float Seconds = QSeconds.toFloat();
    float rate = 0.9;
    String image = filename.toUtf8().constData();
    cout << Seconds/numberFrame << endl;
    for (int i = 0; i < numberFrame; i++)
    {
        rate = rate - 0.9/numberFrame;
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
        delay(Seconds*1000/numberFrame);
    }
}
