#pragma once
#include<iostream>

#include <fstream>

using namespace std;
namespace LoggerClass
{
    class Logger
    {
    public:
        virtual ostream& GetStream() = 0;
    };

    class ConsoleLogger :public Logger
    {
    public:
        ostream& GetStream();
    };

    class FileLogger :public Logger
    {
    private:
        ofstream m_filellogger;
    public:

        ostream& GetStream();
        FileLogger(std::string filename) 
        {
            m_filellogger.open(filename.c_str());
        }
        ~FileLogger()
        {
            m_filellogger.close();
        }
    };

    class LoggerFactory
    {
    public:
        static Logger* CreateFileLogger(std::string FilePath);
        static Logger* CreateConsoleLogger();
    };
    static LoggerClass::Logger* g_logger = LoggerClass::LoggerFactory::CreateFileLogger("isha.log");
    //static Logger* g_logger = LoggerFactory::CreateConsoleLogger();
#define LOG() g_logger->GetStream()
}

