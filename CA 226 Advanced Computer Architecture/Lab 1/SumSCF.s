      .data
A:    .word 100
B:	  .word 0
CON:  .word 0x10000
DA:   .word 0x10008

      .text
main:
	ld r10,CON(r0)
	ld r11,DA(r0)
	
	ld r2,A(r0) ;load N from Mem location A
	daddi r5,r5,2	;Put 2 in r5
	daddi r3,r2,1	;N+1
	dmulu r4,r2,r3	;N(N+1)
	ddivu r6,r4,r5 ;N(N+1)/2
	
	sd r6,0(r11)
	daddi r1,r0,2
	sd r1,0(r10)
	halt
	
	
	
