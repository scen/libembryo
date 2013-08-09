#include "vmt.h"

#include <libembryo/logger.h>

#include <cstdlib>

#include <mach/mach.h>

namespace embryo
{
	unsigned int vmt::countFuncs(void **vmt)
	{
		int cnt = -1;

        vm_region_basic_info_data_t info;
        do {
            cnt++;
	        vm_size_t vmsize;
	        vm_address_t address = (vm_address_t)vmt[cnt];
	        mach_msg_type_number_t infoCount = VM_REGION_BASIC_INFO_COUNT;
	        memory_object_name_t object;
        	
        	kern_return_t status = vm_region(mach_task_self(), &address, &vmsize, VM_REGION_BASIC_INFO, (vm_region_info_t)&info,
                                         &infoCount, &object);
        	if (status)
        	{
        		log().error("vm_region() failed");
        		break;
        	}
        } while (((info.protection & VM_PROT_EXECUTE) && (info.protection & VM_PROT_READ)) || // read/exec
        	((info.protection & VM_PROT_READ) && (info.protection & VM_PROT_EXECUTE) && (info.protection & VM_PROT_WRITE))); // read/write/exec
        
        log().info(format("vfunc count: %d") % cnt);
		return cnt;
	}
    
	int vmt::findFunc(void **vmt, void *func, unsigned int vfuncs)
	{
		if (!vfuncs) vfuncs = countFuncs(vmt);
		for (unsigned int i = 0; i < vfuncs; i++)
		{
			if (vmt[i] == func) return i;
		}
		return -1;
	}
    
	vmt::vmt(void *inst, size_t offset, unsigned int vfuncs)
	{
		vftable = makeptr<void **>(inst, offset);
		oldvmt = *vftable;
		if (!vfuncs) vfuncs = countFuncs(oldvmt);
		vcount = vfuncs;
		array = (void **)malloc((vfuncs + 3) * sizeof(void *));
		array[2] = oldvmt[-1];
		for (unsigned int i = 0; i < vfuncs; ++i) array[i + 3] = oldvmt[i];
		*vftable = array + 3;
	}
	vmt::~vmt()
	{
		if (vftable) unhook();
		free(array);
	}
}