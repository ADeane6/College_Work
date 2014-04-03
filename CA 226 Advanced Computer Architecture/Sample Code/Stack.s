;Stack

.data

	CONTROL: 	.word 0x10000
	DATA: 		.word 0x10008

	POINTER: 	.word 0  		;pointer to top of stack
	STACK: 		.space 4096		;Stack in mem

.text

	MAIN:

		jal INPUTINT
		jal PUSH

		daddi r30,r30,10
		jal PUSH
		daddi r30,r30,34
		jal PUSH

		jal POP
		jal OUTPUTINT
		jal POP
		jal OUTPUTINT
		jal POP
		jal OUTPUTINT
		halt

	POP:                    
	    ld r29,POINTER(r0)     
	    daddi r29,r29,-8   
	    ld r30,STACK(r29)   
	    sd r29,POINTER(r0)
		daddi r29,r0,0
	    jr r31

	PUSH:
		ld r29,POINTER(r0)
		sd r30,STACK(r29)
		daddi r29,r29,8
		sd r29,POINTER(r0)
		daddi r29,r0,0
		jr r31

	PEEK:
		daddi r28,r28,8
		dmul r29,r29,r28
		ld r30,STACK(r29)
		daddi r29,r0,0
		daddi r28,r0,0
		jr r31

	INPUTINT:
		ld r11,CONTROL(r0)
		ld r10,DATA(r0)

		daddi r1,r0,8
		sd r1,0(r11)
		ld r30,0(r10)
		jr r31

	OUTPUTINT:
		ld r10,CONTROL(r0)
		ld r11,DATA(r0)

		sd r30,0(r11)
		daddi r1,r0,2
		sd r1,0(r10)
		jr r31