#include <iostream>


extern "C" bool cpuIdAvailable(void);
extern "C" size_t cpuId(size_t eax);


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
        std::cerr << "cpuid not available :(" << std::endl;
        exit(1);
    }


    std::cout << "cpuid available!" << std::endl;
    std::cout << "checking for VTx support..." << std::endl;
}
