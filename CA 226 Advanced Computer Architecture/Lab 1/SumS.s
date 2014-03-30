      .data
A:    .word 0
B:    .word 1
C:    .word 101

      .text
main:
	ld r8,C(r0)
	daddi r6,r0,0
	daddi r5, r0, 1
	daddu r7, r0, r8
	
	loop:
	beq r5, r7, done
    daddu r6,r6,r5
	daddi r5,r5,1
	j loop
	
	done:
    sd r6,A(r0)
    halt          

