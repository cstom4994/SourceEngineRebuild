;; X64WIN
.CODE

pushAllRegisters PROC
        ;; Push all callee-saves registers to get them
        ;; on the stack for conservative stack scanning.
        ;; There is an 8-byte return address on the stack and we push
        ;; 72 bytes which maintains the required 16-byte stack alignment
        ;; at the call.
        push 0
        push rsi
        push rdi
        push rbx
        push rbp
        push r12
        push r13
        push r14
        push r15
        ;; Pass the two first arguments unchanged (rcx, rdx)
        ;; and the stack pointer after pushing callee-saved
        ;; registers to the callback.
        mov r9, r8
        mov r8, rsp
        call r9
        ;; Pop the callee-saved registers. None of them were
        ;; modified so no restoring is needed.
        add rsp, 72
        ret
pushAllRegisters ENDP

END