#include"currency_and_weather.h"

int main() {
    // Адреса api-запросов для получения курса валют
    std::string url_curr_1{ "https://api.currencyapi.com" };
    std::string url_curr_2{ "/v3/latest?apikey=2CeMIE9VtXvQEYLDPMseN6gVamX9O86o3fEJgTgP&currencies=EUR%2CUSD%2CUAH&base_currency=RUB" };
    std::string url_btc_1{ "https://fcsapi.com" };
    std::string url_btc_2{ "/api-v3/crypto/latest?id=78&access_key=01mxu8JpH6U3PSzZDvuF" };

    // Создание кнопок главного меню
    TgBot::InlineKeyboardMarkup::Ptr main_menu(new  TgBot::InlineKeyboardMarkup);
    std::vector< TgBot::InlineKeyboardButton::Ptr> buttons_main;
    TgBot::InlineKeyboardButton::Ptr weather_btn(new TgBot::InlineKeyboardButton),
        currency_btn(new TgBot::InlineKeyboardButton);

    weather_btn->text = u8"Погода";
    weather_btn->callbackData = "weather";
    currency_btn->text = u8"Курсы валют";
    currency_btn->callbackData = "currency";

    buttons_main.push_back(weather_btn);
    buttons_main.push_back(currency_btn);

    main_menu->inlineKeyboard.push_back(buttons_main);

    //Создание кнопок меню курса валют
    TgBot::InlineKeyboardMarkup::Ptr currency_menu(new  TgBot::InlineKeyboardMarkup);
    std::vector< TgBot::InlineKeyboardButton::Ptr> buttons_currency;
    TgBot::InlineKeyboardButton::Ptr usd_btn(new TgBot::InlineKeyboardButton),
        eur_btn(new TgBot::InlineKeyboardButton),
        uah_btn(new TgBot::InlineKeyboardButton),
        btc_btn(new TgBot::InlineKeyboardButton);
    usd_btn->text = u8"Доллар";
    usd_btn->callbackData = "usd";
    eur_btn->text = u8"Евро";
    eur_btn->callbackData = "eur";
    uah_btn->text = u8"Гривна";
    uah_btn->callbackData = "uah";
    btc_btn->text = u8"Биткоин";
    btc_btn->callbackData = "btc";

    buttons_currency.push_back(usd_btn);
    buttons_currency.push_back(eur_btn);
    buttons_currency.push_back(uah_btn);
    buttons_currency.push_back(btc_btn);
    currency_menu->inlineKeyboard.push_back(buttons_currency);

    
    // Создание бота передавая токен
    TgBot::Bot bot("Token");


    // Приветствие и главное меню
    bot.getEvents().onCommand("start", [&bot, &main_menu](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
            u8"Привет " + message->chat->firstName +
            u8", я телеграм бот информер, я могу рассказать тебе о погоде и курсах валют.Что тебя интересует ? ",
            false, 0, main_menu);


        });

    //Функция  обрабатывающая любой ввод и проверяющая погоду если введен город

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (message->text == "/start") {

            return;
        }

        std::string weather = get_weather_json(message->text);
        if (weather == "-1") {
            bot.getApi().sendMessage(message->chat->id, u8"Не могу найти такой населенный пункт(( Попробуй еще раз.");
            return;
        }

        bot.getApi().sendMessage(message->chat->id, json_weather_parse(weather, message->text));

        });


    //Функция работающая с кнопками
    bot.getEvents().onCallbackQuery([&bot, &currency_menu, &main_menu, &url_curr_1, &url_curr_2, &url_btc_1, &url_btc_2](TgBot::CallbackQuery::Ptr query) {

        
        if (query->data == "weather") {
            bot.getApi().sendMessage(query->message->chat->id, u8"Введи название города");

        }
        else if (query->data == "currency") {
            bot.getApi().sendMessage(query->message->chat->id,
                u8"Курс какой валюты ты хотел бы узнать?", false, 0, currency_menu);

        }
        else {
            std::string cur;
            if (query->data == "usd")cur = json_currency_parse(get_currency_json(url_curr_1, url_curr_2), "USD");
            if (query->data == "eur")cur = json_currency_parse(get_currency_json(url_curr_1, url_curr_2), "EUR");
            if (query->data == "uah")cur = json_currency_parse(get_currency_json(url_curr_1, url_curr_2), "UAH");
            if (query->data == "btc")cur = json_currency_parse(get_currency_json(url_btc_1, url_btc_2), "BTC");
            bot.getApi().sendMessage(query->message->chat->id, cur);
        }

        });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}