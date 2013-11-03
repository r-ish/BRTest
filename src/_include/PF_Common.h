#ifndef _PF_COMMON_H_
#define _PF_COMMON_H_
/*
************************************************************************
yFile Namez•W€Œ^’è‹`
yDescriptionz
yRevision Historyz
   REV.00 2013-11-04  BY T.OOSAKI
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * ƒCƒ“ƒNƒ‹[ƒh
 */
#include "HAL_Common.h"

/*
 * ’è”’è‹`
 */
#define PF_NULL  (void *)0
#define PF_FALSE (0)
#define PF_TRUE  (1)

/*
 * Œ^’è‹`
 */
typedef	char			B;
typedef	short			H;
typedef	long			W;
typedef unsigned char   UB;
typedef	unsigned short	UH;
typedef	unsigned long	UW;


/*
 * ŠO•”ŠÖ”éŒ¾
 */
extern UB   PF_DisableIr( void );		// Š„‚è‚İ‹Ö~
extern void PF_ReturnIr( UB ucCCR );	// ‹Ö~ó‘Ô‚©‚çŒ³ó‘Ô‚É•œ‹A

#endif /* _PF_COMMON_H_ */
