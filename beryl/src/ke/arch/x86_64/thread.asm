section .text

extern KiSystemStartupInternal

global KiSystemStartup
KiSystemStartup:
    mov rdi, rsp
    add rdi, 8

    jmp KiSystemStartupInternal

global KiJumpIntoThread
KiJumpIntoThread:
    mov rsp, rdi

    jmp LoadContext

global KiSwitchContext
KiSwitchContext:
    ; TODO: Implement this

LoadContext:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp

    ret

global KiThreadTrampoline
KiThreadTrampoline:
    xor rbp, rbp

    mov rdi, r12
    mov rsi, r13

    jmp rbx
