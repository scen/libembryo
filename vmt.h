//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_vmt_h
#define libembryo_vmt_h

#include <libembryo/memhelp.h>

namespace embryo
{
    class vmt
    {
    public:
        vmt(void *inst, size_t offset = 0, unsigned int vfuncs = 0);
        ~vmt();
        vmt() {}
        static unsigned int countFuncs(void **pVMT);
        static int findFunc(void **pVMT, void *pFunc, unsigned int vfuncs = 0);
        inline void hookMethod(void* newfunc, size_t index) { array[index + 3] = newfunc; }
        inline void unhookMethod(size_t index) { array[index + 3] = oldvmt[index]; }
        inline void unhook() {*vftable = oldvmt; }
        inline void rehook() { *vftable = array + 3; }
        inline bool hooked() const { return *vftable != oldvmt; }
        inline void eraseHooks() { for (unsigned int i = 0; i < vcount; ++i) array[i+3] = vftable[i]; }
        inline unsigned int numFuncs() const { return vcount; }
        inline void poof() { vftable = NULL; }
        template<typename Fn>
        inline Fn getMethod(size_t index) const
        {
            return (Fn)oldvmt[index];
        }
    protected:
        vmt(const vmt&);
        vmt& operator= (const vmt&);
        inline void _set_guard(size_t S) { array[1] = (void *) S; }
        inline size_t _get_guard() const { return (size_t) array[1]; }
        inline void _set_backptr(void *ptr) { array[0] = ptr; }
        inline void* _get_backptr() const { return array[0]; }
    private:
        void ***vftable;
        void **oldvmt;
        void **array;
        unsigned int vcount;
    };
}

#endif