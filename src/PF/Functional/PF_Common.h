#ifndef _PF_COMMON_H_
#define _PF_COMMON_H_
//************************************************************************
//
// [File Name]   : 標準型定義
//
// [Description] : 
//
// [Revision History] :
//   REV.00 2013-11-04  BY T.OOSAKI
//
//                      (C) 2013 IPL CORPORATION All Rights Reserved
//************************************************************************

#include "HAL_Common.h"

// 標準型定義
typedef	char			B;
typedef	short			H;
typedef	long			W;
typedef unsigned char   UB;
typedef	unsigned short	UH;
typedef	unsigned long	UW;

#define PF_NULL  (void *)0
#define PF_FALSE (0)
#define PF_TRUE  (1)

// 割り込み禁止と禁止状態から元状態に復帰
extern UB   PF_DisableIr( void );
extern void PF_ReturnIr( UB ucCCR );

#endif /* _PF_COMMON_H_ */
