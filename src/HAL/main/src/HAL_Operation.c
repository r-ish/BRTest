/*
************************************************************************
【File Name】HAL オペレーション（運用側面）
【Description】
【Revision History】
   REV.00 2013-12-19  BY T.OOSAKI
   REV.01 2014-01-25  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * インクルード
 */
#include "HALIn.h"

/*
 * 定数定義
 */

/*
 * 外部関数宣言
 */

/*
 * 内部関数宣言
 */

/*
 * グローバル変数宣言
 */

// 1msタイマー割り込み関数ポインタ
HAL_TIMER_IR_1MS	fpHAL_TIMER_IR_1MS = PF_NULL;
// タスクスケジューラ関数ポインタ宣言
HAL_TASKMAIN_1MS	fpHAL_TASKMAIN_1MS = PF_NULL;

/******************************************************************************
【名称】1ミリ秒タイマ割り込み関数登録
【再入】非リエントラント
【入力】1ミリ秒タイマ割り込みで呼び出される関数ポインタ
【出力】なし
【戻値】なし
【処理】タイマ割り込み関数を登録する
******************************************************************************/
void HAL_OPE_EntryTmrIR_1MS(HAL_TIMER_IR_1MS fpEntryIR )
{
	// 引数がnullでない場合、グローバル変数に登録する
	if(fpEntryIR != PF_NULL)
	{
		fpHAL_TIMER_IR_1MS = fpEntryIR;
	}
}

/******************************************************************************
【名称】タスクメイン関数登録
【再入】非リエントラント
【入力】タスク処理関数ポインタ
【出力】なし
【戻値】なし
【処理】タクス処理関数を登録する
******************************************************************************/
void HAL_OPE_EntryTaskMain(HAL_TASKMAIN_1MS fpEntryTASK )
{
	// 引数がnullでない場合、タスク処理関数をグローバル変数に登録する
	if(fpEntryTASK != PF_NULL)
	{
		fpHAL_TASKMAIN_1MS = fpEntryTASK;
	}
}

