#ifndef _ARCH_H_
#define _ARCH_H_

#ifdef x86
#include <kernel/x86/arch.hpp>
#else
#error "Architecture not defined."
#endif

#endif
