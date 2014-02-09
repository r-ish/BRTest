#ifndef _HAL_IN_H_
#define _HAL_IN_H_
/*
************************************************************************
【File Name】Hardware Abstraction Layer 共通ヘッダー(内部隠蔽用)
【Description】
【Revision History】
   REV.00 2013-11-04  BY T.OOSAKI
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

#include "HAL.h"
#include "HAL_Operation.h"

/*
 * 関数ポインタ宣言
 */

// 1msタイマー割り込み関数ポインタ宣言
typedef	void (*HAL_TIMER_IR_1MS)(void);
extern	HAL_TIMER_IR_1MS	fpHAL_TIMER_IR_1MS;

// タスクスケジューラ関数ポインタ宣言
typedef	void (*HAL_TASKMAIN_1MS)(void);
extern	HAL_TASKMAIN_1MS	fpHAL_TASKMAIN_1MS;

/*
 * 関数
 */


#endif /* _HAL_IN_H_ */
