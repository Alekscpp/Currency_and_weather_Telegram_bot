#include"currency_and_weather.h"

// ������� �������������� double � string
std::string to_str(double num, int n) {
    std::stringstream string_stream;
    string_stream << std::fixed << std::setprecision(n) << num;
    std::string str = string_stream.str();
    return str;
}

//  ������� ��������� �������� ������ � ������� json

std::string get_weather_json(std::string city) {
    std::string json_weather;
    std::string url = "/data/2.5/weather?q=" + city + "&appid=cc194035f2a6c43b10dd0d6b4ab0a0c3";

    
    httplib::Client client("http://api.openweathermap.org");
    
    auto res = client.Get(url);
   
    if (res) {
        
        if (res->status == 404) {
            return "-1";
        }
        if (res->status == 200) {
            
            json_weather = res->body;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }

    return json_weather;
}


//������� ��� �������� json �������� ������ � ������

std::string json_weather_parse(std::string weather_json, std::string city) {
    std::string result;
    nlohmann::json j = nlohmann::json::parse(weather_json);

      result = u8"������ � ������ " + city + "\n" +
        u8"����������� �������: " + to_str(j.at("main").at("temp") - 273.15, 1) + u8"�C\n" +
        u8"��������� ���:            " + to_str(j.at("main").at("feels_like") - 273.15, 1) + u8"�C\n" +
        u8"�������� �����:           " + to_str(j.at("wind").at("speed"), 1) + u8"�/c\n" +
        u8"���. ��������:             " + to_str(j.at("main").at("pressure") * 0.75, 0) + u8"�� ��.��.\n" +
        u8"���������:                    " + to_str(j.at("main").at("humidity"), 0) + "%\n";

    return result;
}
