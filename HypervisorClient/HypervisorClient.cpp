#include <iostream>

#include <windows.h>

#include "CpuId.h"


constexpr char HYPERVISOR_DEVICE_PATH[] = R"(\Device\MyHypervisor)";


static bool cpuMeetsHypervisorRequirements()
{
    return 
        cpuIdAvailable() &&
        cpuIsIntel() &&
        cpuSupportsVmx();
}


int main()
{
    std::cout << 
        "  ____                                          _\r\n"
        " / ___| _   _  _   _  _ __    ___  _ __ __   __(_) ___   ___   _ __\r\n"
        "| |  _ | | | || | | || '_ \\  / _ \\| '__|\\ \\ / /| |/ __| / _ \\ | '__|\r\n"
        "| |_| || |_| || |_| || |_) ||  __/| |    \\ V / | |\\__ \\| (_) || |\r\n"
        " \\____| \\__,_| \\__, || .__/  \\___||_|     \\_/  |_||___/ \\___/ |_|\r\n"
        "               |___/ |_|\r\n\r\n\r\n";


    if (!cpuMeetsHypervisorRequirements()) {
        std::cerr << 
            "CPU does not meet requirements (cpuid support, intel-based and VMX support)" << 
            std::endl;
        exit(1);
    }


    HANDLE hvFile = CreateFileA(
        HYPERVISOR_DEVICE_PATH,
        GENERIC_WRITE,
        false,
        nullptr,
        CREATE_NEW,
        FILE_ATTRIBUTE_DEVICE,
        nullptr
    );

    if (nullptr == hvFile) {
        std::cerr << 
            "Could not open hypervisor device path (" <<
            HYPERVISOR_DEVICE_PATH << 
            ") for writing" <<
            std::endl;

        exit(1);
    }
}
