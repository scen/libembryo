//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_log_h
#define libembryo_log_h

#include <boost/format.hpp>

#include <iostream>
#include <fstream>
#include <string>

using boost::format;

namespace embryo
{
    class logger
    {
    public:
        enum logflags
        {
            log_stdout = 1,
            log_file   = 2,
            force_flush= 4,
            file_color = 8
        };

        static logger &get();

        void init(int flags, const std::string &fn = "");

        void error(const std::string &text);
        void error(const format &fmt);

        void warn(const std::string &text);
        void warn(const format &fmt);

        void info(const std::string &text);
        void info(const format &fmt);
        
        void verb(const std::string &text);
        void verb(const format &fmt);
    private:
        int flags;
        std::ofstream outFile;

        logger() {};
        ~logger() {};

        void write(const std::string &text, const std::string &col, const std::string &title);
    };
    
    logger &log();
}

#endif
