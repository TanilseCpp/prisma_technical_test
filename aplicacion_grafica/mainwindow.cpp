#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include <QTimer>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CSVReader reader;

    //Lineas
    beanSeries = new QLineSeries();
    airSeries = new QLineSeries();
    beanSeries->setColor(QColor(139, 69, 19));
    airSeries->setColor(Qt::blue);
    beanSeries->setName("Bean Temperature");
    airSeries->setName("Air Temperature");

    //Creo el cuadro y las curvas
    chart = new QChart();
    chart->addSeries(beanSeries);
    chart->addSeries(airSeries);

    //Creo los ejes y los defino
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    axisX->setTitleText("Tiempo (s)");
    axisX->setRange(0,20);
    axisY->setTitleText("Temperatura");
    axisY->setRange(150,250);

    //Se agregan los ejes al cuadro
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    //Conecta las curvas con los ejes
    beanSeries->attachAxis(axisX);
    beanSeries->attachAxis(axisY);
    airSeries->attachAxis(axisX);
    airSeries->attachAxis(axisY);

    //Se crea la grafica
    chartView = new QChartView(chart);

    //Antialiasing
    chartView->setRenderHint(QPainter::Antialiasing);

    //Se coloca la graica dentro del cuadro
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_chart);
    layout->addWidget(chartView);

    timer = new QTimer(this);
    currentIndex = 0;
    lastPlottedTime = -1.0;
    connect(timer, &QTimer::timeout, this, &MainWindow::updateData);
    timer->start(500);

    samples = reader.readCSV("C:/Users/tanil/OneDrive/Desktop/Tanilse/qt/prueba_dos/roaster_generated.csv");

    qDebug() << "Cantidad de muestras:" << samples.size();

    for(const auto& sample : samples)
    {
        qDebug()
        << sample.time_s
        << sample.bean_mv
        << sample.bean_temperature
        << sample.air_mv
        << sample.air_temperature;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData()
{
    if(currentIndex >= samples.size())
    {
        timer->stop();

        qDebug() << "Fin del archivo.";

        return;
    }

    DataSample sample = samples[currentIndex];

    //Alarma
    if(sample.bean_temperature > 215)
    {
        ui->alarma->setText("Temperatura alta");

        ui->cuadro_alarma->setStyleSheet(
            "background-color:red;"
            "color:white;");
    }
    else
    {
        ui->alarma->setText("Temperatura normal");

        ui->cuadro_alarma->setStyleSheet(
            "background-color:green;"
            "color:white;");
    }

    //Agrego los puntos
    if(sample.time_s - lastPlottedTime >= 1.0)
    {
        beanSeries->append(
            sample.time_s,
            sample.bean_temperature);

        airSeries->append(
            sample.time_s,
            sample.air_temperature);

        axisX->setRange(0, sample.time_s + 5);

        lastPlottedTime = sample.time_s;
    }

    currentIndex++;

    qDebug()

        << "Tiempo:" << sample.time_s

        << "Bean:" << sample.bean_mv

        << "Bean Temp:" << sample.bean_temperature

        << "Air:" << sample.air_mv

        << "Air Temp:" << sample.air_temperature;

}

void MainWindow::on_boton_reinicio_clicked() {
    beanSeries->clear();
    airSeries->clear();

    currentIndex = 0;

    axisX->setRange(0,20);

    timer->start(500);

    lastPlottedTime = -1.0;
}