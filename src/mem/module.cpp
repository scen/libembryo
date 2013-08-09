#include "module.h"

#include <logger.h>
#include <util.h>

#include <sys/types.h>
#include <mach/error.h>
#include <mach/vm_types.h>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>
#include <mach/mach.h>
#include <sys/stat.h>

namespace embryo
{
    module::module(const std::string& name) : m_start(0), m_size(0)
    {
        bool found = false;
        unsigned int imageCount = _dyld_image_count();
        for (int i = 0; i < imageCount; i++)
        {
            mach_header *header = (mach_header *)_dyld_get_image_header(i);

            const char *imageName = _dyld_get_image_name(i);
            if (!imageName) continue;

            std::string shortName = util::getFileNameFromPath(std::string(imageName));
            if (shortName != name) continue;

            struct stat sb;
            if (stat(imageName, &sb))
            {
                log().error("stat() image failed");
                break;
            }
            found = true;
            m_start = (void *)header;
            m_size = (unsigned int)sb.st_size;
            log().info(format("found image %s start=0x%X size=0x%X") % name
                % m_start % m_size);
            break;
        }
        if (!found)
        {
            log().error(format("unable to found module %s") % name);
        }
    }

}