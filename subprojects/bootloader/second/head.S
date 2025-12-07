/*
 *
 * (c) 2004, 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

.include "../first/macos.i"

#if defined(APPLE_DRIVER)
.include "../first/32bitmode.i"
#endif

.equ	paramstring_length, 1024

/***************************************************************************
 *
 * second level arguments
 *
 ***************************************************************************/

.section .text.head

.global _start
_start:	
	/* 
	 * Do not add anything here, we expect the following
	 * signature to always be at the exact same offset!
	 */
	bra	setup
	
_signature:		.dc.b	'E','M','0','7'

/* EM06 */

_conf_size:		.dc.w	paramstring_length
_configuration:		.skip	paramstring_length, 0

	.align	4
setup:
	/* When trying to debug with QEMU + GDB put your "jmp ." here. */
#if defined(APPLE_DRIVER)
	lea	boot_unit(%pc), %a0
	move.l	%d5, (%a0)
	switch32bitmode
#endif

_reloc:
	pea __rel_dyn_end(%pc)
	pea __rel_dyn_start(%pc)
	pea _start(%pc)
	/* Do the ELF relocations */
	lea relocate(%pc), %a0
	jsr (%a0)

	/* begin to work */
	lea	_start(%pc), %a0
	move.l	%a0, -(%sp)
	lea	start(%pc), %a0
	jsr	(%a0)

	/* We guess to never come here */
loop:
	bra	loop

#if defined(APPLE_DRIVER)
PRAM_buffer:
        .long   0

	.globl boot_unit
boot_unit:
	.long	0
#endif
