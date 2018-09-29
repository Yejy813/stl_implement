//smart_ptr_define.h
#ifndef __SMART_PTR_DEFINE_H__
#define __SMART_PTR_DEFINE_H__

#include <assert.h>

#define PTR_ASSERT(x) assert(x)

#define _SMART_PTR_BEGIN    namespace smartptr {
#define _SMART_PTR_END        }
#define _SMART_PTR    ::smartptr::

#endif