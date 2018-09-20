/**
	@filename oscilloscope.h
	@brief    oscilloscope module
	@author   tzaiyang
	Copyright (c) 2018 EPIC. All rights reserved.
*/

#ifndef OSCILLOSCOPE_H_
#define OSCILLOSCOPE_H_

#include <QWidget>
#include <QVector>
#include "qcustomplot.h"
class Oscilloscope : public QWidget {
    Q_OBJECT

 public:
    explicit Oscilloscope(QWidget *parent = nullptr);
    ~Oscilloscope();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void getData(const QVector<float> &data);
    void switchPuseEnabled();

 signals:
    void popData();

 private slots:
    void realtimeDataSlot();  // 添加实时数据槽

 private:
    // 定时器，周期调用realtimeDataSlot()槽，实现动态数据添加到曲线
    QTimer dataTimer;
    QCustomPlot *customPlot = nullptr;
    float voltage;
    bool pauseEnabled = false;
};

#endif  // OSCILLOSCOPE_H_
