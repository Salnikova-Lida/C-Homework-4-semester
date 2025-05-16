#ifndef __LOG_H__
#define __LOG_H__

#include <ctime>
#include <iostream>
#include <list>
#include <string>

template <typename Derived>
class Singleton{
  public:
    Singleton(){}
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;

    template <typename... T>
    static Derived* Instance(T... args){
        static Derived* object = new Derived(args...);
        return object;
    }
};

enum LogLevel{LOG_NORMAL = 0, LOG_WARNING, LOG_ERROR};

class Log : public Singleton<Log>{
  public:
    struct Message{
        std::time_t time;
        const std::string message;
        LogLevel level;

        Message(std::time_t _time, const std::string _message, LogLevel _level) : time{_time}, message{_message}, level{_level}{}
        
        std::string to_string(){
            std::string str_time = std::string(std::asctime(std::localtime(&time)));
            str_time.pop_back();
            std::string str_level;
            switch (level){
                case LOG_NORMAL:
                    str_level = "LOG_NORMAL ";
                case LOG_WARNING:
                    str_level = "LOG_WARNING";
                case LOG_ERROR:
                    str_level = "LOG_ERROR  ";
            }
            return str_time + "|" + str_level + "|: " + message;
        }
    };

    void message(LogLevel level, const std::string text){
        messages.push_back(new Message(std::time(nullptr), text, level));
        if (messages.size() > buffer){
            messages.pop_front();
        }
    }

    void print(){
        for (Message* const mes : messages){
            std::cout << (*mes).to_string() << std::endl;
        }
    }

    ~Log(){
        for (const Message* mes : messages){
            delete mes;
        }
        messages.clear();
    }

  private:
    static const int buffer = 10;
    std::list<Message*> messages;
};

#endif