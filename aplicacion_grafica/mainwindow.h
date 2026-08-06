#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "datasample.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_boton_reinicio_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<DataSample> samples;
    QTimer *timer;
    int currentIndex;
    void updateData();
    QChart *chart;
    QChartView *chartView;
    QLineSeries *beanSeries;
    QLineSeries *airSeries;
    QValueAxis *axisX;
    QValueAxis *axisY;
    double lastPlottedTime;
};
#endif // MAINWINDOW_H
