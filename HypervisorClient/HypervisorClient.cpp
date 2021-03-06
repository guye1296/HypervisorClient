#include <iostream>

#include <windows.h>

#include "CpuId.h"


// This is a DOS device path
constexpr char HYPERVISOR_DEVICE_PATH[] = R"(\\.\\MyHypervisor)";


int main()
{
    std::cout << 
        "  ____                                          _\r\n"
        " / ___| _   _  _   _  _ __    ___  _ __ __   __(_) ___   ___   _ __\r\n"
        "| |  _ | | | || | | || '_ \\  / _ \\| '__|\\ \\ / /| |/ __| / _ \\ | '__|\r\n"
        "| |_| || |_| || |_| || |_) ||  __/| |    \\ V / | |\\__ \\| (_) || |\r\n"
        " \\____| \\__,_| \\__, || .__/  \\___||_|     \\_/  |_||___/ \\___/ |_|\r\n"
        "               |___/ |_|\r\n\r\n\r\n";

    if(!cpuIdAvailable()) {
        std::cerr << "[*] cpuid not available" << std::endl;
        exit(1);
    }
    std::cout << "[*] cpuid command available" << std::endl;

    if(!cpuIsIntel()) {
        std::cerr << "[*] CPU is not Intel based" << std::endl;
    }
    std::cout << "[*] CPU is Intel based" << std::endl;

    if (!cpuSupportsVmx()) {
        std::cerr << "[*] CPU does not support VMX" << std::endl;
    }
    std::cout << "[*] CPU supports VMX" << std::endl;


    std::cout << "[*] CPU is Intel-based and has VTx support. Ready to Go!" << std::endl;


    HANDLE hypervisorHandle = CreateFileA(
        HYPERVISOR_DEVICE_PATH,
        GENERIC_WRITE,
        false,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        nullptr
    );

    if (nullptr == hypervisorHandle) {
        std::cerr << 
            "Could not open hypervisor device path (" <<
            HYPERVISOR_DEVICE_PATH << 
            ") for writing" <<
            std::endl;

        exit(1);
    }

    char outBuffer[0x1000] = { 0 };
    char inBuffer [] = "Hello from userland";
    unsigned long bytesReturned;

    auto ioctlCallSuccessful = DeviceIoControl(
        hypervisorHandle,
        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS),
        inBuffer,
        strlen(inBuffer),
        outBuffer,
        0x1000,
        &bytesReturned,
        nullptr
    );

    if (!ioctlCallSuccessful) {
        std::cerr << "[*] Error in device control: " << GetLastError() << std::endl;
        exit(1);
    }
    std::cout << "[*] Got following string from driver: " << outBuffer << std::endl;
}
