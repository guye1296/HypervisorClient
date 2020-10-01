#pragma once

#include <stdint.h>


#pragma pack(push, 1)
typedef struct _CpuIdResult {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
} CpuIdResult;
#pragma pack(pop)


extern "C" bool cpuIdAvailable(void);

extern "C" void cpuId(uint32_t eax, CpuIdResult * result);

bool cpuIsIntel(void);

