#include "../core/view/node_graphics.hpp"
#include <QLineEdit>
#include <QFileDialog>
#include <QtCharts>
#include<vector>
using namespace QtCharts;
#pragma once
using namespace NoderGraphics;
class HistogramView : public QChartView{
public:
    HistogramView(){
        chart->addSeries(series);
        chart->setTitle("Histogram");
        chart->addAxis(axis_x, Qt::AlignBottom);
        chart->addAxis(axis_y, Qt::AlignLeft);
        this->setChart(chart);
        this->setFixedSize(400, 300);
        axis_x->setRange(0, 255);
    }

    void SetData(const std::vector<int>& data){
        series->clear();
        series->clear();
        int max = 0;
        for(int i = 0; i < data.size(); i++){
            series->append(i, data[i]);
            if(i == 0)max = data[i];
            else max = (max < data[i]? data[i] : max);
        }
        chart->removeSeries(series);
        chart->addSeries(series);
        axis_y->setRange(0, max);
    }
private:
    QLineSeries* series = new QLineSeries;
    QChart* chart = new QChart;
    QValueAxis* axis_x = new QValueAxis;
    QValueAxis* axis_y = new QValueAxis;
};

class HistogramProxy : public WidgetProxy{
    Q_OBJECT
public:

    HistogramProxy(){
        this->setWidget(chart_view);
        chart_view->setRenderHint(QPainter::Antialiasing);
    }
private:
    HistogramView* chart_view = new HistogramView();

};
