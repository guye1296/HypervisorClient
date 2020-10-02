bits 64


%define CPUID_EFLAGS_BIT 0x00200000


; apparently this is needed for the functions to be exported? why?
section .text


global cpuIdAvailable


; https://wiki.osdev.org/CPUID - checking CPUID availability
; also converted to 64 bit
cpuIdAvailable:
	pushfq                               ;Save EFLAGS
    pushfq                               ;Store EFLAGS
    xor qword [rsp], CPUID_EFLAGS_BIT    ;Invert the ID bit in stored EFLAGS
    popfq                                ;Load stored EFLAGS (with ID bit inverted)
    pushfq                               ;Store EFLAGS again (ID bit may or may not be inverted)
    pop rax                              ;eax = modified EFLAGS (ID bit may or may not be inverted)
    xor rax,[rsp]                        ;eax = whichever bits were changed
    popfq                                ;Restore original EFLAGS

    and rax,CPUID_EFLAGS_BIT             ;eax = zero if ID bit can't be changed, else non-zero
    shr rax, 21                          ;return type is `bool` which is 1 byte so shift to 1 byte boundary

    ret
