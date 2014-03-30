.data
A:   	.word 11 ; N number
B:	 	.word 2
C:		.word 0 
CON: 	.word 0x10000
DA:   	.word 0x10008

.text

main:
	ld r10,CON(r0)
	ld r11,DA(r0)
	
	ld r2,A(r0) 	;load N from Mem location A
	ld r3,B(r0)		;load 2 from Mem location B
	ld r4,C(r0)		;load 0 from Mem location C
	ddiv r5,r2,r3

	loop:
	ddiv r2,r5
	mfhi r6
	beq r6,r4,done

	daddi r5,r5,1
	beq r5,r2,doneA

	j loop

	

	doneA:
	sd r3,0(r11)
	daddi r1,r0,2
	sd r1,0(r10)
	done:
	halt
	
