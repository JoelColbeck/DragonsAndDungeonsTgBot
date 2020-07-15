#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <tgbot/tgbot.h>

int main() {
    srand(time(0));
    std::ifstream token_file;
    std::string token;
    token_file.open("/Users/joelcolbeck/CLionProjects/DnDbot/token_file");
    if (token_file.is_open())
    {
        getline(token_file, token);
    }

    std::cout << token << std::endl;

    TgBot::Bot bot(token);

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/random")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "I don't know, wtf is it");
    });

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                "Hello! I'm DnDbot. I can give you random number from 1 to 20. Just type \"/random\"");
    });

    bot.getEvents().onCommand("random", [&bot](TgBot::Message::Ptr message) {
        std::string result;
        result = std::to_string(rand() % 20 + 1);
        bot.getApi().sendMessage(message->chat->id, "You've got " + result);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while(true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e){
        printf("error: %s\n", e.what());
    }
    return 0;
}
