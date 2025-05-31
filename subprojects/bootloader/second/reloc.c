/* Basic ELF relocation - Daniel Palmer <daniel@thingy.jp> */

#include <stdint.h>

/* From u-boot elf.h */

typedef uint32_t Elf32_Addr; /* Unsigned program address */
typedef uint32_t Elf32_Off; /* Unsigned file offset */
typedef int32_t Elf32_Sword; /* Signed large integer */
typedef uint32_t Elf32_Word; /* Unsigned large integer */
typedef uint16_t Elf32_Half; /* Unsigned medium integer */

/* Relocation entry with explicit addend */
typedef struct {
	Elf32_Addr r_offset; /* offset of relocation */
	Elf32_Word r_info; /* symbol table index and type */
	Elf32_Sword r_addend;
} Elf32_Rela;

/* */

#define R_68K_32 1
#define R_68K_JMP_SLOT 21
#define R_68K_RELATIVE 22

void relocate(uint32_t reloc_offset, Elf32_Rela *rel_start, Elf32_Rela *rel_end)
	__attribute__((const)) __attribute__((section(".text.reloc")));
void relocate(uint32_t reloc_offset, Elf32_Rela *rel_start, Elf32_Rela *rel_end)
{
	/* Do ELF relocation */
	for (Elf32_Rela *rel = rel_start; rel != rel_end; rel++) {
		uint8_t x = rel->r_info & 0xff;
		void *offset = (void *)rel->r_offset;
		uint32_t *newsym32 = offset + reloc_offset;
		uint32_t newval;

		switch (x) {
		case R_68K_32:
			*newsym32 = (*newsym32) + reloc_offset + rel->r_addend;
			break;
		case R_68K_RELATIVE:
			newval = reloc_offset + rel->r_addend;
			*newsym32 = newval;
			break;
		case R_68K_JMP_SLOT:
			// I don't think this should be in our final binary but
			// for some reason with 030 turned on it happens
			*newsym32 = *newsym32 + reloc_offset;
			break;
		default:
			while (1) {
			}
			break;
		}
	}
}
