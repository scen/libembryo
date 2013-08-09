#include "logger.h"

#include <sstream>
#include <sys/time.h>

// Colors
#define RESET       "\033[0m"
#define BLACK       "\033[30m"             /* Black */
#define RED         "\033[31m"             /* Red */
#define GREEN       "\033[32m"             /* Green */
#define YELLOW      "\033[33m"             /* Yellow */
#define BLUE        "\033[34m"             /* Blue */
#define MAGENTA     "\033[35m"             /* Magenta */
#define CYAN        "\033[36m"             /* Cyan */
#define WHITE       "\033[37m"             /* White */

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

    void logger::error(boost::format fmt)
    {
        error(fmt.str());
    }

    void logger::warn(const std::string& text)
    {
        write(text, BLUE, "warn");
    }

    void logger::warn(boost::format fmt)
    {
        warn(fmt.str());
    }

    void logger::info(const std::string& text)
    {
        write(text, GREEN, "info");
    }

    void logger::info(boost::format fmt)
    {
        info(fmt.str());
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
            outFile << header.str() << text << '\n';
        }
    }

    logger& log()
    {
        return logger::get();
    }
};