#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("图片查看器");
    setFixedSize(400,600);

    imageLable = new QLabel;
    previous = new QPushButton("上一张",this);
    next = new QPushButton("下一张",this);
    fangda = new QPushButton("放大图片",this);
    suoxiao = new QPushButton("缩小图片",this);
    openImage = new QPushButton("选择图片",this);
    currentIndex = 0;

    previous->setFixedHeight(50);
    next->setFixedHeight(50);
    openImage->setFixedHeight(50);
    fangda->setFixedHeight(50);
    suoxiao->setFixedHeight(50);


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(imageLable);
    layout->addWidget(previous);
    layout->addWidget(next);
    layout->addWidget(openImage);
    layout->addWidget(fangda);  // 添加放大按钮
    layout->addWidget(suoxiao);  // 添加缩小按钮

    setLayout(layout);

    previous->setVisible(false);
    next->setVisible(false);

    connect(previous,&QPushButton::clicked,this,&Widget::previousEvent);
    connect(next,&QPushButton::clicked,this,&Widget::nextEvent);
    connect(openImage,&QPushButton::clicked,this,&Widget::openImageEvent);

    connect(fangda,&QPushButton::clicked,this,&Widget::fandaEvent); // 绑定放大槽函数
    connect(suoxiao,&QPushButton::clicked,this,&Widget::suoxiaoEvent); // 绑定缩小槽函数

}

Widget::~Widget()
{
    delete ui;
}

void Widget::previousEvent()
{
    if(currentIndex==0)
        currentIndex = imageList.length()-1;
    else
        currentIndex--;

    showImage();
}

void Widget::nextEvent()
{
    currentIndex = (++currentIndex)%imageList.length();
    showImage();
}

void Widget::openImageEvent()
{
    imageList = QFileDialog::getOpenFileNames(this,"Open File",QDir::currentPath(),"图片文件 (*.jpg);;图像文件 (*.png)");

    if(imageList.isEmpty()) return;

    showImage();

    previous->setVisible(true);
    next->setVisible(true);
}


// 放大图片
void Widget::fandaEvent()
{
    //等比例放大
    transform.scale(1.25, 1.25);
    image.load(imageList[currentIndex]);
    //使用transformed对image进行变换操作
    image = image.transformed(transform);
    imageLable->setPixmap(QPixmap::fromImage(image));
}

// 缩小图片
void Widget::suoxiaoEvent()
{
    transform.scale(0.8, 0.8);
    image.load(imageList[currentIndex]);
    image = image.transformed(transform);
    imageLable->setPixmap(QPixmap::fromImage(image));
}

void Widget::showImage()
{
    int width = imageLable->width();
    int height = imageLable->height();
    QImage img(imageList[currentIndex]);
    //scaled函数用于对图像进行缩放操作，KeepAspectRatio表示缩放图像时保持宽高比
    img = img.scaled(width, height, Qt::KeepAspectRatio);
    //setPixmap()函数将指定的图像作为控件的背景图像进行显示。如果控件的大小与图像的大小不一致，图像会被自动缩放以适应控件的大小。
    imageLable->setPixmap(QPixmap::fromImage(img));
}
