bits 64


%define CPUID_EFLAGS_BIT 0x00200000


; apparently this is needed for the functions to be exported? why?
section .text


global cpuIdAvailable
global cpuId


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

; void cpuId(uint32_t eax, CpuIdResult * result);
; see https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention?view=vs-2019 for calling conventions
cpuId:
    mov rax, rcx
    ; rdi = result
    mov rdi, dword rdx
    
	cpuid 
    ; cpuid return values are e{b,c,d}x
    mov [rdi],       eax
    mov [rdi + 0x4], ebx
    mov [rdi + 0x8], ecx
    mov [rdi + 0xC], edx
    
    xor rax, rax
	ret
