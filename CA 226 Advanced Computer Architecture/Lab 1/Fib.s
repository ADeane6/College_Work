      .data
A:    .word 18
B:	  .word 0
CON:  .word 0x10000
DA:   .word 0x10008

      .text
main:
	ld r10,CON(r0)
	ld r11,DA(r0)
	
	ld r2,A(r0) ;load N from Mem location A
	ld r3,B(r0)
	
	daddi r4,r0,0
	daddi r5,r0,1
	
	loop:
	beq r2, r3, done
	daddu r6,r5,r0
	daddu r5,r5,r4
	daddu r4,r6,r0
	
	daddi r3,r3,1
	j loop
	
	done:
	sd r6,0(r11)
	daddi r1,r0,2
	sd r1,0(r10)
	halt
	
	
	
