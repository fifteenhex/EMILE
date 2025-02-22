/*
 *
 * (c) 2004, 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#ifndef __MACOS_LOWMEM_H__
#define __MACOS_LOWMEM_H__

#include <macos/osutils.h>

#define VIA1Base	(*(volatile unsigned long*)0x01D4)
#define SCCRd		(*(volatile unsigned long*)0x01d8)
#define SCCWr		(*(volatile unsigned long*)0x01dc)
#define ScrnBase	(*(volatile unsigned long*)0x0824)
#define ROMBase		(*(short**)0x02ae)
#define HWCfgFlags	(*(volatile unsigned long*)0x0B22)
#define SCSIBase	(*(volatile unsigned long*)0x0C00)
#define ASCBase		(*(volatile unsigned long*)0x0CC0)
#define VIA2Base	(*(volatile unsigned long*)0x0CEC)
#define PMgrBase	(*(volatile unsigned long*)0x0D18)
#define UnivROMBits	(*(volatile unsigned long*)0x0DD4)
#define TimeVIADB	(*(volatile unsigned short*)0x0cea)
#define TimeDBRA	(*(volatile unsigned short*)0x0D00)
#define MemTop		(*(volatile unsigned long*)0x0108)
#define Time		(*(volatile unsigned long*)0x020C)
#define KeyLast		(*(volatile unsigned short*)0x0184)
#define KeyTime		(*(volatile unsigned long*)0x0186)
#define KeyRepTime	(*(volatile unsigned long*)0x018A)
#define Ticks		(*(volatile unsigned long*)0x016A)

#define LMGetUnitTableEntryCount()	(*(volatile short*)0x1d2)
#define LMGetUTableBase()	(*(volatile unsigned long*)0x11c)
#define LMGetDrvQHdr()		((QHdrPtr)0x0308)
#define	LMGetMainDevice()	(*(GDHandle*)0x08A4)
#define LMGetBootDrive()	(*(short*)0x0210)
#define LMSetBootDrive(a)	do { (*(short*)0x0210) = a; } while(0)
#endif /* __MACOS_LOWMEM_H__ */
