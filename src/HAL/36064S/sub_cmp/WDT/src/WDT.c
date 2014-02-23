/*
************************************************************************
【File Name】ウォッチドッグタイマ
【Description】
【Revision History】
   REV.00 2014-02-23  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * インクルード
 */
#include "HALIn.h"
#include "36064s.h"
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


#if ( HAL_HW_SWITCH == HAL_HW_H836064S )
/******************************************************************************
【名称】ウォッチドッグタイマ初期化
【再入】非リエントラント
【入力】なし
【出力】なし
【戻値】なし
【処理】WDTレジスタの初期化
        ＊ウォッチドッグタイマは初期値では動作しないようにする
******************************************************************************/
void WDT_Init( void )
{
	WDT.TCSRWD.BYTE=0x92;	
	WDT.TCSRWD.BYTE=0x92;
	
	WDT.TCSRWD.BIT.B4WI = 0;
	WDT.TCSRWD.BIT.TCSRWE=1;

	WDT.TCSRWD.BIT.B2WI=0;
	WDT.TCSRWD.BIT.WDON=0;
	
	WDT.TMWD.BYTE=0xFF;
	WDT.TCSRWD.BIT.B6WI = 1;
	WDT.TCSRWD.BIT.TCWE = 1;
	WDT.TCWD=0x00;
}

#endif
