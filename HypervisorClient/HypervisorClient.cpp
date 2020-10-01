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

    if(!cpuIsIntel()) {
        std::cerr << "CPU is not Intel. sad times" << std::endl;
        exit(2);
    }
    std::cout << "CPU is Intel-based :)" << std::endl;

    if (!cpuSupportsVmx()) {
        std::cerr << "CPU does not support VMX operation. Aborting :(" << std::endl;
        exit(3);
    }

    std::cout << "CPU supports VMX! :)" << std::endl;

}
