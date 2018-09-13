#include "oscilloscope.h"

#include <QWidget>
#include <QtWidgets/QVBoxLayout>

Oscilloscope::Oscilloscope(QWidget *parent) :
    QWidget(parent),
    customPlot(new QCustomPlot)
{
    setupRealtimeDataDemo(customPlot);
    customPlot->replot();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(customPlot);
}

Oscilloscope::~Oscilloscope()
{

}

//画图初始化
void Oscilloscope::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
//#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  //QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
//#endif
  //demoName = "Real Time Data Demo";

  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setName("temp");
  //customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  //customPlot->graph(0)->setAntialiasedFill(false);
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(1)->setName("hui");
  //customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));


  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  //connect(&dataTimer, SIGNAL(popData()), this, SLOT(realtimeDataSlot()));
  connect(this,&Oscilloscope::popData,this,&Oscilloscope::realtimeDataSlot);

  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
  customPlot->legend->setVisible(true);
}

void Oscilloscope::getData(QVector <float> &data)
{
    for (int i =0; i<data.length();i++)
    {
        voltage = data[i];
        emit popData();
    }
}

void Oscilloscope::switchPuseEnabled(){
    pauseEnabled = !pauseEnabled;
}

void Oscilloscope::realtimeDataSlot()
{
    //key的单位是秒
    static double key=0;
    if(!pauseEnabled) key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
    //使用随机数产生两条曲线
    float value0 = voltage;
//    double value1 = qrand() % 80;
        if(!pauseEnabled)customPlot->graph(0)->addData(key, value0);//添加数据1到曲线1
//        customPlot->graph(1)->addData(key, value1);//添加数据2到曲线2
    //删除8秒之前的数据。这里的8要和下面设置横坐标宽度的8配合起来
    //才能起到想要的效果，可以调整这两个值，观察显示的效果。
    if(!pauseEnabled)customPlot->graph(0)->removeDataBefore(key-8);
//    customPlot->graph(1)->removeDataBefore(key-8);

      //自动设定graph(1)曲线y轴的范围，如果不设定，有可能看不到图像
//也可以用ui->customPlot->yAxis->setRange(up,low)手动设定y轴范围
    customPlot->graph(0)->rescaleValueAxis();
//    customPlot->graph(1)->rescaleValueAxis(true);

    //这里的8，是指横坐标时间宽度为8秒，如果想要横坐标显示更多的时间
    //就把8调整为比较大到值，比如要显示60秒，那就改成60。
    //这时removeDataBefore(key-8)中的8也要改成60，否则曲线显示不完整。
    customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);//设定x轴的范围
    customPlot->replot();
}
