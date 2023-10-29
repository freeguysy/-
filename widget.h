#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStringList>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void previousEvent();
    void nextEvent();
    void openImageEvent();

    void fandaEvent();  // 放大槽函数
    void suoxiaoEvent();  // 缩小槽函数

private:
    Ui::Widget *ui;
    void showImage();

    QLabel* imageLable;
    QPushButton* previous,*next,*openImage,*fangda,*suoxiao;
    QStringList imageList;
    int currentIndex;

    QTransform transform;  // 用于图片控制
    QImage image;  // 图片对象
    QString picture_path;


};
#endif // WIDGET_H
