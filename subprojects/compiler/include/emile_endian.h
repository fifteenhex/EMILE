/*
 *
 * (c) 2004,2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#ifndef _EMILE_ENDIAN_H
#define _EMILE_ENDIAN_H
#include <endian.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* 
 * Use this to get the address of member in a packed struct without
 * alignment warnings. You still need to handle the potentially unaligned pointer correctly.
 */
#define struct_member_pointer(_struct_ptr, _member) \
	(((void *)_struct_ptr) + offsetof(typeof(*_struct_ptr), _member))

#if __BYTE_ORDER == __BIG_ENDIAN

/* nothing to do, because m68k is big endian too */

static inline uint16_t read_short(const void *addr)
{
	uint16_t val;

	memcpy(&val, addr, sizeof(val));

	return val;
}

static inline void write_short(void *addr, uint16_t value)
{
	memcpy(addr, &value, sizeof(value));
}

static inline uint32_t read_long(const void *addr)
{
	uint32_t val;

	memcpy(&val, addr, sizeof(val));

	return val;
}

static inline void write_long(void *addr, uint32_t value)
{
	memcpy(addr, &value, sizeof(value));
}

#else /* __BYTE_ORDER == __LITTLE_ENDIAN */

/* little endian (or unknown), read byte by byte to get it in good order */

static inline u_int16_t read_short(u_int16_t *addr)
{
	unsigned char *baddr = (unsigned char *)addr;

	return ((u_int16_t)(*baddr) << 8) | (u_int16_t) * (baddr + 1);
}

static inline void write_short(u_int16_t *addr, u_int16_t value)
{
	unsigned char *baddr = (unsigned char *)addr;

	*baddr = (unsigned char)(value >> 8);
	*(baddr + 1) = (unsigned char)value;
}

static inline u_int32_t read_long(u_int32_t *addr)
{
	u_int16_t *saddr = (u_int16_t *)addr;

	return ((u_int32_t)read_short(saddr) << 16) |
	       (u_int32_t)read_short(saddr + 1);
	;
}

static inline void write_long(u_int32_t *addr, u_int32_t value)
{
	u_int16_t *saddr = (u_int16_t *)addr;

	write_short(saddr, (u_int16_t)(value >> 16));
	write_short(saddr + 1, (u_int16_t)value);
}
#endif
#endif
