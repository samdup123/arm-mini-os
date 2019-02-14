                .text                    @ begin text section

                .global add              @ add subroutine 'add' globally
add:                                     @ define 'add'
                add r0, r0, r1           @ perform the actual addition
                bx  lr                   @ branch out of subroutine

                .global sub              @ add subroutine 'sub' globally
sub:
                sub r0, r0, r1
                bx  lr                   @ branch out of subroutine

                .global mul              @ add subroutine 'mul' globally
mul:                                     @ define 'mul'
                mul r0, r1, r0           @ perform the actual multiplication
                bx  lr                   @ branch out of subroutine

		.global div_remainder
div_remainder:				 @ move registers around to free up the return register
		mov r3, r2
		mov r2, r1
		mov r1, r0
		mov r0, #0
		mov r4, #0
    div_n1:				 @ negate the dividend if negative and flag
		cmp r1, #0
		bgt div_n2
		rsb r1, r1, #0
		add r4, r4, #1
    div_n2:				 @ negate the divisor if negative and flag
		cmp r2, #0
		bgt div_rec
		rsb r2, r2, #0
		sub r4, r4, #1

  div_rec:				 
		cmp r1, r2		 @ compares the dividend and divisor
		blt div_rem		 @ branches if the division is complete
		sub r1, r1, r2		 @ subtracts the divisor from the divedend
		add r0, r0, #1		 @ adds 1 to the return register
		b   div_rec		 @ branches to recursion label
  div_rem:	
		cmp r4, #0		 @ check the negative flag
		rsbne r0, r0, #0	 @ negate the result if flag set
		str r1, [r3]		 @ stores the remainder in the specified memory addr
		bx  lr			 @ branch out of subroutine




@ TODO: implement division
@                 .global	__aeabi_idiv     @ add div subroutine globally
@                 .global	__aeabi_idivmod  @ add divmod subroutine globally

@                 .global	div_remainder    @ add 'div_remainder' globally
@ div_remainder:                           @ define 'div_remainder'
@                 push {r4, r5, r6, lr}    @ push our needed registers
@                 mov  r5, r2              @ now use r5
@                 mov  r6, r0              @ now use r6
@                 mov  r4, r1              @ now use r4
@                 bl   __aeabi_idivmod     @ perform the actual divmod
@                 mov  r0, r6              @ use the r0 divmod result
@                 str  r1, [r5]            @ store r1's value to r5
@                 mov  r1, r4              @ r4 into r1
@                 bl   __aeabi_idiv        @ perform the actual div
@                 pop  {r4, r5, r6, pc}    @ pop back our needed registers 
