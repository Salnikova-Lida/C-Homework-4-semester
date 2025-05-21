#ifndef __LOG_H__
#define __LOG_H__

#include <ctime>
#include <iostream>
#include <list>
#include <string>
#include <memory>

template <typename Derived>
class Singleton{
  public:
    Singleton(){}
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;

    template <typename... T>
    static Derived* Instance(T... args){
        static Derived* object = new Derived(args...); //  просто статик без нью может помочь
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
                case LOG_NORMAL:{
                    str_level = "LOG_NORMAL ";
                    break;}
                case LOG_WARNING:{
                    str_level = "LOG_WARNING";
                    break;}
                case LOG_ERROR:{
                    str_level = "LOG_ERROR  ";
                    break;}
            }
            return str_time + "|" + str_level + "|: " + message;
        }
    };

    void message(LogLevel level, const std::string text){
        messages.push_back(std::make_unique<Message>(std::time(nullptr), text, level));
        if (messages.size() > buffer){
            messages.pop_front(); //очистить память, сдвинуть указатель. Утечка памяти. Done

        }
    }

    void print(){
        for (auto&& mes : messages){
            std::cout << mes->to_string() << std::endl;
        }
    }

    ~Log(){
        messages.clear();
    }

  private:
    const int buffer = 10;
    std::list<std::unique_ptr<Message>> messages;
};

#endif


// r-value ссылка на юник птр, потому что обычный указатель вызывал бы итератор, копирующий элементы, а так нельзя
// вместо обычного указателя перемещаем в это ауто ссылку и работаем 