#include "signature.h"

#include <libembryo/logger.h>

#include <sstream>

namespace embryo
{
    signature::signature(std::string idapattern)
    {
        idapattern.erase(std::remove(idapattern.begin(), idapattern.end(), ' '), idapattern.end());
        log().info(idapattern);
        for (auto it = idapattern.cbegin(); it != idapattern.cend();)
        {
            if (*it == '?')
            {
                m_pattern += '\0';
                m_mask += '?';
                ++it;
                continue;
            }
            std::stringstream converter(std::string(it, it + 2));
            log().info(format("welp: %s") % std::string(it, it + 2));
            unsigned short cur = 0;
            converter >> std::hex >> cur;
            unsigned char byteCur = static_cast<unsigned char>(cur);
            m_pattern += byteCur;
            m_mask += 'x';
            it += 2;
        }
        log().info(m_mask);
    }

    signature::signature(const std::string& pattern, const std::string& mask) : m_pattern(pattern),
        m_mask(mask)
    {
    }
}