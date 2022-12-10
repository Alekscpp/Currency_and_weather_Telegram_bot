
#include"currency_and_weather.h"

//Функция получения json файла курса валют

std::string get_currency_json(std::string url_1, std::string url_2) {
    std::string json_curr;
    httplib::Client client(url_1);

    auto res = client.Get(url_2);
    if (res) {
        if (res->status == 200) {
            // В res->body лежит string с ответом сервера
            json_curr = res->body;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << "&!" << std::endl;
    }
    return json_curr;
}


//Функция обработки данных json для курса валют
std::string json_currency_parse(std::string json_curr, std::string currency_code) {
    std::string currency_value;

    nlohmann::json j = nlohmann::json::parse(json_curr);
    if (currency_code == "BTC") {
        for (auto& elem : j["response"]) {
            currency_value = to_string(elem["c"]) + u8" долл";
        }
        currency_value.erase(remove(currency_value.begin(), currency_value.end(), '\"'), currency_value.end());
    }
    if (currency_code == "USD") currency_value = to_str(1 / (double)(j.at("data").at("USD").at("value")), 2) + u8" руб";
    if (currency_code == "EUR") currency_value = to_str(1 / (double)(j.at("data").at("EUR").at("value")), 2) + u8" руб";
    if (currency_code == "UAH") currency_value = to_str(1 / (double)(j.at("data").at("UAH").at("value")), 2) + u8" руб";
    
    return currency_value;
}
