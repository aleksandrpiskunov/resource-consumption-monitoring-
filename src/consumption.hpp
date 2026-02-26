#pragma once

// Переменные для подсчёта расхода электроэнергии
extern float energyFraction; // Дробная часть кВт*ч
extern float energyIncrement; // Приращение за импульс
extern boolean lastPulseState; // Предыдущее состояние импульса
extern boolean currentPulseState; // Текущее состояние импульса
extern char pulseCount; // Счётчик импульсов
extern unsigned long energyTotal; // Основной счётчик кВт*ч
extern unsigned long lastMeterPoll; // Время последнего опроса
extern unsigned long lastDataSend; // Время последней отправки

// Константы для расчёта расхода
constexpr char PULSE_COUNT_TO_UPDATE = 32; // Количество импульсов для обновления расхода
constexpr float ENERGY_FRACTION_MAX = 1.0; // Максимальная дробная часть
constexpr float ENERGY_INCREMENT_DEFAULT = 0.01; // Приращение по умолчанию
constexpr float ENERGY_FRACTION_START = 0.15; // Стартовая дробная часть
constexpr unsigned long ENERGY_TOTAL_START = 22070; // Стартовое значение кВт*ч
constexpr unsigned long METER_POLL_PERIOD_MS = 40; // Период опроса счетчика
constexpr unsigned long DATA_SEND_INTERVAL_US = 30000000; // Интервал отправки данных

// Функция обновления расхода
void updateConsumption();
