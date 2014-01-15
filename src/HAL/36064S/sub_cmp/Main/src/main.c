/*
************************************************************************
【File Name】メイン関数
【Description】
【Revision History】
   REV.00 2013-11-04  BY T.OOSAKI
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * インクルード
 */
#include	"HALIn.h"

#if ( HAL_HW_SWITCH == HAL_HW_H836064S )

/*
 * 定数定義
 */

/*
 * 外部関数宣言
 */

/*
 * 内部関数宣言
 */
extern void main(void);
extern void TIMER_Init( void );

/*
 * グローバル変数宣言
 */

/******************************************************************************
【名称】メイン関数
【再入】非リエントラント
【入力】なし
【出力】なし
【戻値】なし
【処理】メイン関数
******************************************************************************/
const UB a = 1; // リンカの警告抑制のため一時的に挿入：L1100 (W) Cannot find "C" specified in option "start"
void main( void )
{
	// タイマー初期化
	TIMER_Init();

	// 全割り込み許可
	IENR1.IENDT = 1;

	/* 運用側面側でタスクスケジューラ関数が定義されている場合コール */
	if (fpHAL_TASKMAIN_1MS != PF_NULL)
	{
		fpHAL_TASKMAIN_1MS();
	}
}
#endif
