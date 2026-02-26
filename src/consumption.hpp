#pragma once

extern float energyFraction;
extern float energyIncrement;
extern boolean lastPulseState;
extern boolean currentPulseState;
extern char pulseCount;
extern unsigned long energyTotal;
extern unsigned long lastMeterPoll;
extern unsigned long lastDataSend;

constexpr char PULSE_COUNT_TO_UPDATE = 32;
constexpr float ENERGY_FRACTION_MAX = 1.0;
constexpr float ENERGY_INCREMENT_DEFAULT = 0.01;
constexpr float ENERGY_FRACTION_START = 0.15;
constexpr unsigned long ENERGY_TOTAL_START = 22070;
constexpr unsigned long METER_POLL_PERIOD_MS = 40;
constexpr unsigned long DATA_SEND_INTERVAL_US = 30000000;

void update_consumption();
