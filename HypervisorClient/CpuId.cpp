#include <string.h>
#include "CpuId.h"


constexpr char CPU_VENDOR_INTEL_EBX[] = "Genu";
constexpr char CPU_VENDOR_INTEL_ECX[] = "ntel";
constexpr char CPU_VENDOR_INTEL_EDX[] = "ineI";

constexpr uint32_t CPUID_GETFEATURES = 1;
constexpr uint32_t CPUID_FEAT_ECX_VMX = 1 << 5;


bool cpuIsIntel(void)
{
	CpuIdResult result;
	(void)cpuId(0, &result);

	return
		strcmp(CPU_VENDOR_INTEL_EBX, reinterpret_cast<const char*>(&result.ebx)) &&
		strcmp(CPU_VENDOR_INTEL_ECX, reinterpret_cast<const char*>(&result.ecx)) &&
		strcmp(CPU_VENDOR_INTEL_EDX, reinterpret_cast<const char*>(&result.edx));
}

bool cpuSupportsVmx(void)
{
	CpuIdResult result;
	(void)cpuId(CPUID_GETFEATURES, &result);

	return (result.ecx & CPUID_FEAT_ECX_VMX);
}
