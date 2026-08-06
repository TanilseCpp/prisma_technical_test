#ifndef TEMPERATURECALCULATOR_H
#define TEMPERATURECALCULATOR_H

class TemperatureCalculator
{
public:
    TemperatureCalculator();

    static double bean_temperature(double bean_mv);

    static double air_temperature(double air_mv);
};

#endif // TEMPERATURECALCULATOR_H
