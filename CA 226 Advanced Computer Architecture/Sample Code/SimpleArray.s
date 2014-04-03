;Simple array
;this program does nothing
.data

pos: .word 0 ;this x8 is the indexing of the array
array: .spcae 2048

.text

	ld r2,top(r0)		;get next position on array
    sd r3,base(r2)   	;store whatever is in r3 in array
    daddi r2,r2,8		;inc posdition
    sd r2,top(r0)		;store position