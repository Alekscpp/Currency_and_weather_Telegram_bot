#pragma once

#include <stdio.h>
#include <tgbot/tgbot.h>
#include<nlohmann/json.hpp>
#include <iomanip>

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "httplib.h"


// ������� �������������� double � string
std::string to_str(double num, int n);
//������� ��������� json ����� ����� �����
std::string get_currency_json(std::string url_1, std::string url_2);
//������� ��������� ������ json ��� ����� �����
std::string json_currency_parse(std::string json_curr, std::string currenc);
//  ������� ��������� �������� ������ � ������� json
std::string get_weather_json(std::string city);
//������� ��� �������� json �������� ������ � ������
std::string json_weather_parse(std::string weather_json, std::string city);