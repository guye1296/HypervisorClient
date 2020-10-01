#include <iostream>

#include "CpuId.h"


int main()
{
    std::cout << 
        "  ____                                          _\r\n"
        " / ___| _   _  _   _  _ __    ___  _ __ __   __(_) ___   ___   _ __\r\n"
        "| |  _ | | | || | | || '_ \\  / _ \\| '__|\\ \\ / /| |/ __| / _ \\ | '__|\r\n"
        "| |_| || |_| || |_| || |_) ||  __/| |    \\ V / | |\\__ \\| (_) || |\r\n"
        " \\____| \\__,_| \\__, || .__/  \\___||_|     \\_/  |_||___/ \\___/ |_|\r\n"
        "               |___/ |_|\r\n\r\n\r\n";

    if (!cpuIdAvailable()) {
        std::cerr << "CPUID not available :(" << std::endl;
        exit(1);
    }


    std::cout << "CPUID available!" << std::endl;

    std::cout << "CPUID with eax=0: " << std::endl;

    CpuIdResult result;
    (void)cpuId(0, &result);

    std::cout << "eax: 0x" << std::hex << result.eax << '\t';
    std::cout << "ebx: 0x" << std::hex << result.ebx << '\t';
    std::cout << "ecx: 0x" << std::hex << result.ecx << '\t';
    std::cout << "edx: 0x" << std::hex << result.edx << '\t';
    std::cout << std::endl;

    if (!cpuIsIntel()) {
        std::cerr << "CPU is not Intel. sad times" << std::endl;
        exit(2);
    }
    std::cout << "CPU is Intel-based :)" << std::endl;

    std::cout << "checking for VTx support..." << std::endl;
}
