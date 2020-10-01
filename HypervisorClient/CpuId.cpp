#include <string.h>
#include "CpuId.h"


constexpr char CPU_VENDOR_INTEL_EBX[] = "GenuineIntel";
constexpr char CPU_VENDOR_INTEL_ECX[] = "ntel";
constexpr char CPU_VENDOR_INTEL_EDX[] = "ineI";


bool cpuIsIntel(void)
{
	CpuIdResult result;
	(void)cpuId(0, &result);

	return
		strcmp(CPU_VENDOR_INTEL_EBX, reinterpret_cast<const char*>(&result.ebx)) &&
		strcmp(CPU_VENDOR_INTEL_ECX, reinterpret_cast<const char*>(&result.ecx)) &&
		strcmp(CPU_VENDOR_INTEL_EDX, reinterpret_cast<const char*>(&result.edx));
}
