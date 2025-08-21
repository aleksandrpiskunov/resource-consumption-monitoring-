Мониторинг потребления ресурсов (ГВС, ХВС, Электричество)
Уникальное Arduino-устройство для мониторинга водо- и электропотребления, автоматического сбора данных и отправки статистики в Telegram-бота.
Описание проекта
Данное устройство на базе Arduino считывает показания счетчиков ресурсов (ГВС, ХВС, электричество), записывает их на SD-карту, а также отправляет актуальные данные и статистику потребления в Telegram по расписанию и по запросу.
Принцип работы:
	•	Устройство подключается к счетчикам с импульсными выходами.
	•	Импульсы поступают на Arduino, которая считает расход.
	•	В программе хранится начальное значение счетчика, к нему прибавляются новые импульсы — так рассчитывается актуальное значение ресурса.
	•	Каждые час данные сохраняются на SD-карту и отправляются в Telegram-бот.
	•	По команде боту можно получить статистику за выбранный период.
Компоненты устройства
	1.	Плата Wemos D1 R2
	2.	Модуль SD-карты для Arduino
	3.	Модуль часов реального времени (RTC)
	4.	SD-карта
	5.	Макетная плата (breadboard)
	6.	Соединительные провода
Внешний вид устройства

<img width="459" height="297" alt="image" src="https://github.com/user-attachments/assets/fe76fe5b-a4d9-4026-a1cb-e5e8f5671958" />
<img width="374" height="284" alt="image" src="https://github.com/user-attachments/assets/ec82e151-0ae9-4967-bdea-22d5b57c0b7f" />


Пример интерфейса Telegram-бота

<img width="477" height="334" alt="image" src="https://github.com/user-attachments/assets/92f4914f-eecd-4379-934b-0c0b969880d0" />
<img width="468" height="328" alt="image" src="https://github.com/user-attachments/assets/bbb9398c-4b7b-4d0b-b54a-26cd0caf82bd" />

Пример формата сохранённых данных

<img width="468" height="336" alt="image" src="https://github.com/user-attachments/assets/2bcd7869-6bcd-4eb4-9441-a849eb6072d9" />


Визуализация и анализ
На основе данных, полученных от Telegram-бота, можно строить графики в Excel или аналогичных программах для анализа и визуализации потребления ресурсов.

<img width="367" height="352" alt="image" src="https://github.com/user-attachments/assets/67b35345-de67-4fc8-bb59-78d432df620f" />

<img width="362" height="293" alt="image" src="https://github.com/user-attachments/assets/f4c6a2de-7b11-43bb-9367-4d59d9634cc5" />




