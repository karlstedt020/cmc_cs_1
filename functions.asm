
section .text
; f = exp(x) + 2    
global f
f: 
    finit
    fld qword[esp + 4]
    fldl2e
    fmul
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    fadd
    fscale
    fstp st1
    fld1
    faddp
    fld1
    faddp
    ret
    
; g = -2x + 8
global g
g:
    finit
    fld1
    fld1
    faddp
    fchs
    fld qword[esp + 4]
    fmulp
    mov eax, 0
.L:
    cmp eax, 8
    je .end
    inc eax
    fld1
    faddp
    jmp .L
.end:
    ret


;t = -5 / x
global t
t:
    finit
    fld1
    fld1
    faddp
    fld1
    faddp
    fld1
    faddp
    fld1
    faddp
    fchs
    fld qword[esp + 4]
    fdivp
    ret
