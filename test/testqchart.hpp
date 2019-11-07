#pragma once
#include<QtCharts>
using namespace QtCharts;
namespace Test {
    static void TestQChart(){
        QChartView* chart_view = new QChartView;

        QChart* chart = new QChart;
        chart_view->setRenderHint(QPainter::Antialiasing);
        chart_view->setChart(chart);
        chart_view->setFixedSize(800, 600);
        QCategoryAxis* x_axis = new QCategoryAxis;
        QValueAxis* y_axis = new QValueAxis;
        chart->addAxis(y_axis, Qt::AlignLeft);
        chart->addAxis(x_axis, Qt::AlignBottom);
        chart_view->show();

        QBarSeries* series = new QBarSeries;
        y_axis->setRange(0, 10000);
//        x_axis->setRange(0, 255);
        QRandomGenerator g;
        chart->addSeries(series);
        for(int i = 0; i <= 255; i++){
            x_axis->append(QString::number(i), g.generate()%10000);
            QBarSet* set = new QBarSet("");
            set->append(g.generate()%10000);
//            set.append(g.generate()%10000);
            series->append(set);
//            series->append(i, g.generate() % 10000);
        }
        chart->removeSeries(series);
        chart->addSeries(series);
    }
}
