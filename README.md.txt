# Roaster Machine Monitoring Application

Desktop application developed with **Qt 6 (Widgets + Qt Charts)** and **C++17** to simulate the monitoring of a coffee roasting machine.

The application reads process data from a CSV file, converts the raw sensor values into temperatures, and displays both curves in real time while monitoring for alarm conditions.

---

# Features

- Read process data from a CSV file.
- Simulate machine data acquisition every **500 ms**.
- Convert sensor values (mV) to temperature using the provided equations.
- Plot **Bean Temperature** and **Air Temperature** in real time.
- Display a visual alarm when the bean temperature exceeds **215 °C**.
- Restart the monitoring process with a dedicated button.
- Plot data with a **1-second sampling rate**, while processing incoming samples every 500 ms.

---

# Temperature Conversion

Before plotting, the application converts the sensor values using the following equations:

```cpp
bean_temperature = 20.625 * ((bean_mv / 150.0) - 4.0) + 20.0;

air_temperature = 20.625 * ((air_mv / 150.0) - 4.0) + 20.0;
```

---

# Technologies

- C++17
- Qt 6
- Qt Widgets
- Qt Charts
- CMake

---

# Project Structure

```
.
├── main.cpp
├── MainWindow.h / MainWindow.cpp
├── CSVReader.h / CSVReader.cpp
├── DataSample.h
├── TemperatureCalculator.h / TemperatureCalculator.cpp
├── mainwindow.ui
├── CMakeLists.txt
└── roaster_generated.csv
```

---

# Compilation

## Prerequisites

- Qt 6.5 or newer
- CMake 3.19+
- C++17 compatible compiler

---

## Build

From the project directory:

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

Or simply open the project using **Qt Creator** and build it.

---

# Implementation Overview

## CSVReader

The `CSVReader` class is responsible for reading the CSV file containing the simulated roasting process data.

Each row is converted into a `DataSample` object containing:

- Timestamp
- Bean sensor value (mV)
- Air sensor value (mV)

---

## TemperatureCalculator

This class converts the raw sensor values into temperatures using the equations provided in the technical requirements.

Keeping this logic in a separate class improves readability and follows the Single Responsibility Principle.

---

## MainWindow

The `MainWindow` class manages the graphical interface and coordinates the application workflow.

Its responsibilities include:

- Loading the CSV data.
- Initializing the chart.
- Updating the graph every 500 ms using `QTimer`.
- Plotting data with a 1-second sampling rate.
- Detecting alarm conditions.
- Restarting the simulation.

---

## Real-Time Simulation

Instead of displaying all samples at once, the application simulates a real monitoring system.

Every 500 ms:

- A new sample is processed.
- Temperatures are calculated.
- Alarm conditions are evaluated.

Only one sample per second is plotted, matching the functional requirements.

---

## Alarm System

When the bean temperature exceeds **215 °C**, the application displays a visual alarm.

When the temperature returns below the threshold, the alarm returns to its normal state.

---

# Usage

1. Open the application.
2. Load the CSV file (or configure its path in the project).
3. The simulation starts automatically.
4. Observe both temperature curves.
5. Press **Restart** to begin the simulation again from the first sample.

---

# Screenshots

## Main Window

<img src="https://raw.githubusercontent.com/TanilseCpp/prisma_technical_test/refs/heads/main/ss.png">

---

# Future Improvements

- Load CSV files using a file selection dialog.
- Pause/Resume simulation.
- Export plotted data.
- Zoom and pan support.
- Dynamic chart scaling.
- Multiple alarm levels.
- Display current numerical sensor values.

---

# Author

Tanilse Cano