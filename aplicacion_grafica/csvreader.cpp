#include "csvreader.h"
#include "temperaturecalculator.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

CSVReader::CSVReader() {}

std::vector<DataSample> CSVReader::readCSV(const QString& filePath)
{
    std::vector<DataSample> samples;

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "No se pudo abrir el archivo.";

        return samples;
    }

    QTextStream in(&file);

    in.readLine();

    while (!in.atEnd())
    {
        QString line = in.readLine();

        QStringList values = line.split(",");

        if(values.size() < 3)
            continue;

        DataSample sample;

        sample.time_s = values[0].toDouble();

        sample.bean_mv = values[1].toDouble();

        sample.air_mv = values[2].toDouble();

        sample.bean_temperature =
            TemperatureCalculator::bean_temperature(sample.bean_mv);

        sample.air_temperature =
            TemperatureCalculator::air_temperature(sample.air_mv);

        samples.push_back(sample);
    }

    file.close();

    return samples;
}
