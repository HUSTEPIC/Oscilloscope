#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QWidget>
#include "qcustomplot.h"
#include <QVector>
class Oscilloscope : public QWidget
{
    Q_OBJECT

public:
    explicit Oscilloscope(QWidget *parent = nullptr);
    ~Oscilloscope();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void getData(QVector<float> &data);
    void switchPuseEnabled();

signals:
    void popData();

private slots:
    //添加实时数据槽
    void realtimeDataSlot();

private:
    //定时器，周期调用realtimeDataSlot()槽，实现动态数据添加到曲线
    QTimer dataTimer;
    QCustomPlot *customPlot=nullptr;
    float voltage;
    bool pauseEnabled=false;
};

#endif // OSCILLOSCOPE_H
