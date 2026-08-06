#ifndef DATASAMPLE_H
#define DATASAMPLE_H

struct DataSample
{
    double time_s;
    double bean_mv;
    double air_mv;

    double bean_temperature;
    double air_temperature;
};

#endif // DATASAMPLE_H
