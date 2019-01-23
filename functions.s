/**
 * Instructor:  Eugene Rockey
 * Author:      Nolan Holden
 * Assignment:  Lab 1
 */

.text  @ begin text section

.global add       @ add subroutine 'add' to the global namespace
add:              @ define 'add'
  add r0, r0, r1  @ perform the actual addition
  bx  lr          @ branch out of subroutine

.global sub  @ add subroutine 'sub' to the global namespace
sub:
  sub r0, r0, r1
  bx  lr          @ branch out of subroutine

.global mul       @ add subroutine 'mul' to the global namespace
mul:              @ define 'mul'
  mul r0, r1, r0  @ perform the actual multiplication
  bx  lr          @ branch out of subroutine

.global	__aeabi_idiv     @ add div subroutine to the global namespace
.global	__aeabi_idivmod  @ add divmod subroutine to the global namespace
.global	div_remainder    @ add 'div_remainder' to the global namespace
div_remainder:           @ define 'div_remainder'
  push {r4, r5, r6, lr}  @ push our needed registers
  mov  r5, r2            @ now use r5
  mov  r6, r0            @ now use r6
  mov  r4, r1            @ now use r4
  bl   __aeabi_idivmod   @ perform the actual divmod
  mov  r0, r6            @ use the r0 divmod result
  str  r1, [r5]          @ store r1's value to r5
  mov  r1, r4            @ r4 into r1
  bl   __aeabi_idiv      @ perform the actual div
  pop  {r4, r5, r6, pc}  @ pop back our needed registers 

