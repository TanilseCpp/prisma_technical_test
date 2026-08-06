#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <QString>
#include "datasample.h"

class CSVReader
{
public:
    CSVReader();

    std::vector<DataSample> readCSV(const QString& filePath);
};

#endif // CSVREADER_H
