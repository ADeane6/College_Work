.data

DATA:		.word 0x10000
CONTROL:	.word 0x10008

I:			.word 1
N:     		.word 100   ; The first N numbers in Recamans sequence
POINT:		.word 0 	;Point to front of array
ARRAY: 		.space 4096 ; Space, for use as an array

.text

MAIN:
	daddi r12,r12,2
	ld r11,DATA(r0)
	ld r10,CONTROL(r0)

	ld r1,I(r0)
	ld r2,I(r0)
	ld r20,N(r0)

	daddi r7,r7,8

	LOOP:
	ld r6,POINT(r0)
	daddi r6,r6,8

	daddi r2,r2,1
	dsub r3,r2,r1 		;A(n)-1

	dsub r4,r3,r2 		;A(n)-1 - N

	slti r5,r4,1   		;Check if <=0

	beq r5,r1,ADD+		;if<=0

	WHILE:
	dsub r6,r6,r7
	ld r8,ARRAY(r6)

	beq r8,r4,ADD+		;Check if in array already

	bnez r6,WHILE		;loop if pointer not zero

	ADD-:
	ld r6,POINT(r0)
	sd r4,ARRAY(r6)
	daddi r6,r6,8
	sd r6,POINT(r0)
	j NEXT

	ADD+:
	dadd r3,r3,r2 		;A(n)-1 + N
	ld r6,POINT(r0)
	sd r3,ARRAY(r6)
	daddi r6,r6,8
	sd r6,POINT(r0)

	NEXT:
	bne r2,r20,LOOP

	jal OUTPUT
	halt

OUTPUT:
	ld r1,POINT(r0)

	LOOP2:
	dsub r1,r1,r7
	ld r30,ARRAY(r1)
	sd r30,0(r11)
	sd r12,0(r10)
	bne r1,r0,LOOP2
	jr r31
