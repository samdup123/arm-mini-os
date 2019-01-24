.text

.global add
add:
  add r0, r0, r1
  bx  lr

.global sub
sub:
  sub r0, r0, r1
  bx  lr

.global mul
mul:
  mul r0, r1, r0
  bx  lr

.global	__aeabi_idiv
.global	__aeabi_idivmod
.global	div_remainder
div_remainder:
  push {r4, r5, r6, lr}
  mov  r5, r2
  mov  r6, r0
  mov  r4, r1
  bl   __aeabi_idivmod
  mov  r0, r6
  str  r1, [r5]
  mov  r1, r4
  bl   __aeabi_idiv
  pop  {r4, r5, r6, pc}
  
