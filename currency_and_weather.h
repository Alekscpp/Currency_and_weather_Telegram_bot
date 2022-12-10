#pragma once

#include <stdio.h>
#include <tgbot/tgbot.h>
#include<nlohmann/json.hpp>
#include <iomanip>

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "httplib.h"


// Функция преобразования double в string
std::string to_str(double num, int n);
//Функция получения json файла курса валют
std::string get_currency_json(std::string url_1, std::string url_2);
//Функция обработки данных json для курса валют
std::string json_currency_parse(std::string json_curr, std::string currenc);
//  Функция получения прогноза погоды в формате json
std::string get_weather_json(std::string city);
//Функция для парсинга json прогноза погоды в строку
std::string json_weather_parse(std::string weather_json, std::string city);