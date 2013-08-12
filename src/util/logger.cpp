//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#include <libembryo/logger.h>

#include <sstream>
#include <sys/time.h>

// Colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

namespace embryo
{
    logger& logger::get()
    {
        static logger l;
        return l;
    }

    void logger::init(int flags, const std::string& fn)
    {
        this->flags = flags;
        if (flags & logger::log_file)
        {
            outFile.open(fn, std::ios::out | std::ios::trunc);
        }
        info("Logging system initialized");
    }

    void logger::error(const std::string& text)
    {
        write(text, RED, "erro");
        if (flags & logger::log_file) outFile.flush();
    }

    void logger::error(const format &fmt)
    {
        error(fmt.str());
    }

    void logger::warn(const std::string& text)
    {
        write(text, BLUE, "warn");
    }

    void logger::warn(const format &fmt)
    {
        warn(fmt.str());
    }

    void logger::info(const std::string& text)
    {
        write(text, GREEN, "info");
    }

    void logger::info(const format &fmt)
    {
        info(fmt.str());
    }

    void logger::verb(const std::string& text)
    {
        write(text, YELLOW, "verb");
    }

    void logger::verb(const format &fmt)
    {
        verb(fmt.str());
    }

    void logger::write(const std::string& text, const std::string& col, const std::string& title)
    {
        std::stringstream header;
        
        timeval tv;
        tm *_tm;
        gettimeofday(&tv, NULL);
        _tm = localtime(&tv.tv_sec);
        char curTime[256];
        strftime(curTime, 256, "%H:%M:%S", _tm);
        
        header << '[' << title << " @ " << std::string(curTime) << "]: ";
        if (flags & logger::log_stdout)
        {
            std::cout << col << header.str();
            std::cout << RESET << text << '\n';
        }
        if (flags & logger::log_file)
        {
            if (flags & logger::file_color) outFile << col << header.str() << RESET << text << '\n';
            else outFile << header.str() << text << '\n';
            if (flags & logger::force_flush) outFile.flush();
        }
    }

    logger& log()
    {
        return logger::get();
    }
};