#ifndef libembryo_signature_h
#define libembryo_signature_h

#include <string>

namespace embryo
{
    class signature
    {
    public:
        signature(std::string idapattern);
        signature(const std::string& pattern, const std::string& mask);

        std::string pattern() const { return m_pattern; };
        std::string mask() const { return m_mask; }
    private:
        std::string m_pattern;
        std::string m_mask;
    };
}

#endif