#ifndef libembryo_log_h
#define libembryo_log_h

#include <boost/format.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace embryo
{
    class logger
    {
    public:
        enum
        {
            log_stdout = 1,
            log_file   = 2
        };

        static logger& get();

        void init(int flags, const std::string& fn = "");

        void error(const std::string& text);
        void error(boost::format fmt);

        void warn(const std::string& text);
        void warn(boost::format fmt);

        void info(const std::string& text);
        void info(boost::format fmt);
    private:
        int flags;
        std::ofstream outFile;

        logger() {};
        ~logger() {};

        void write(const std::string& text, const std::string& col, const std::string& title);
    };
    
    logger& log();
}

#endif
