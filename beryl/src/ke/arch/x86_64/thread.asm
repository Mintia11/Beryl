section .text

global KiJumpIntoThread
KiJumpIntoThread:
    mov rsp, rdi

    jmp LoadContext

global KiSwitchContext
KiSwitchContext:
    ; TODO: Implement this

LoadContext:
    mov r15, [rsp + 0x00]
    mov r14, [rsp + 0x08]
    mov r13, [rsp + 0x10]
    mov r12, [rsp + 0x18]
    mov rbp, [rsp + 0x50]
    mov rbx, [rsp + 0x68]

    add rsp, 0x80

    jmp [rsp - 0x8]

global KiThreadTrampoline
KiThreadTrampoline:
    xor rbp, rbp

    mov rdi, r12
    mov rsi, r13

    jmp rbx
