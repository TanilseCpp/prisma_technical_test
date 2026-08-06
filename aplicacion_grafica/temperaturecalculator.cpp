#include "temperaturecalculator.h"

double TemperatureCalculator::bean_temperature(double bean_mv)
{
    return 20.625 * ((bean_mv / 150.0) - 4.0) + 20.0;
}

double TemperatureCalculator::air_temperature(double air_mv)
{
    return 20.625 * ((air_mv / 150.0) - 4.0) + 20.0;
}