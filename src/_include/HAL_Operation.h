#ifndef _HAL_OPERATION_H_
#define _HAL_OPERATION_H_
/*
************************************************************************
【File Name】Hardware Abstraction Layer オペレーションヘッダー
【Description】
【Revision History】
   REV.00 2013-12-19  BY T.OOSAKI
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

// ハードウェアの種類
#define HAL_HW_H836064S (0)
#define HAL_HW_H8XXXXXX (1)

/*******************************************************************************
 【コンフィギュレーション】
   利用するハードウェアに合わせて定数を設定する ★★★
*/
#define HAL_HW_SWITCH  (HAL_HW_H836064S)
/*******************************************************************************/

// ハードウェアスイッチに合わせてインクルード
#if   ( HAL_HW_SWITCH == HAL_HW_H836064S )
//	#include "36064s.h"
#elif ( HAL_HW_SWITCH == HAL_HW_H8XXXXXX )
//	#include "XXXXXX.h"
#endif

#endif /* _HAL_OPERATION_H_ */
