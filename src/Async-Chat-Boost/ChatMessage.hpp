#pragma once
#include <string>
#include <vector>
#include <ctime>


enum class MessageType { BROADCAST, MULTICAST };


struct ChatMessage {
    std::string _senderUserName; 
    std::string _time;           
    std::string _message;       
    MessageType _messageType;    
    std::vector<std::string> _recipients; 


    std::string serialize() const {
        std::string serialized = _senderUserName + "|" + _time + "|" + std::to_string(static_cast<int>(_messageType)) + "|";

        for (const auto& recipient : _recipients) {
            serialized += recipient + ";";
        }

        serialized += "|" + _message;
        return serialized;
    }

    static ChatMessage deserialize(const std::string& data) {
        ChatMessage msg;
        size_t pos1 = data.find('|');
        size_t pos2 = data.find('|', pos1 + 1);
        size_t pos3 = data.find('|', pos2 + 1);
        size_t pos4 = data.find('|', pos3 + 1);

        msg._senderUserName = data.substr(0, pos1);
        msg._time = data.substr(pos1 + 1, pos2 - pos1 - 1);
        msg._messageType = static_cast<MessageType>(std::stoi(data.substr(pos2 + 1, pos3 - pos2 - 1)));

        size_t start = pos3 + 1;
        size_t pos;
        while ((pos = data.find(';', start)) < pos4) {
            msg._recipients.push_back(data.substr(start, pos - start));
            start = pos + 1;
        }

        msg._message = data.substr(pos4 + 1); 
        return msg;
    }

    static std::string getCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        int hour = localTime->tm_hour;
        int minute = localTime->tm_min;

        std::string hourStr = (hour < 10 ? "0" : "") + std::to_string(hour);
        std::string minuteStr = (minute < 10 ? "0" : "") + std::to_string(minute);

        return hourStr + ":" + minuteStr;
    }
};
