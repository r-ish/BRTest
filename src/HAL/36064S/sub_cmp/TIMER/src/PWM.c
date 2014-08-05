/*
************************************************************************
【File Name】PWM出力
【Description】
【Revision History】
   REV.00 2014-08-03  BY R.ISHIKAWA
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
【名称】PWM初期化
【再入】非リエントラント
【入力】なし
【出力】なし
【戻値】なし
【処理】TimerZレジスタをPWM動作用としての初期化
        目的：周期設定を10000クロックに設定する
******************************************************************************/
void PWM_Init( void )
{
	TZ.TSTR.BIT.STR0=0;	// チャネル0:タイマ停止
	TZ.TSTR.BIT.STR1=0;	// チャネル1:タイマ停止
	
	TZ0.TCR.BYTE =	0x20;	// チャネル0:GRAでクリア(001)、立上りエッジ(00)、φでカウント(000)
	TZ1.TCR.BYTE =	0x20;	// チャネル1:GRAでクリア(001)、立上りエッジ(00)、φでカウント(000)
	
	TZ.TPMR.BYTE =	0xFF;	// 全部のFTIOをPWMモードにする
		
	TZ.TOCR.BYTE =	0x00;	// TZ：全てのFTIOの初期出力が0
		
	TZ0.POCR.BYTE = 0x00;	// チャネル0:全てのFTIOの出力レベルはローアクティブ
	TZ1.POCR.BYTE = 0x00;	// チャネル1:全てのFTIOの出力レベルはローアクティブ
	
	TZ.TOER.BYTE =	0x11;	// FTIOB、FTIOC、FTIOD端子の出力許可(FTIOAは不許可)
		
	TZ.TMDR.BYTE =	0x00;	// TCNT0、1は非同期動作、その他のGBレジスタ通常動作
	TZ.TFCR.BYTE =	0x00;	// 通常
	
	TZ0.TSR.BYTE =	0x00;	// エラーフラグクリア
	TZ1.TSR.BYTE =	0x00;	// エラーフラグクリア

	TZ0.TCNT=0;	// タイマカウンタクリア
	TZ1.TCNT=0;	// タイマカウンタクリア

	TZ0.GRA=10000;	// チャネル0の周期設定
	TZ1.GRA=10000;	// チャネル1の周期設定
	
	TZ0.GRB = 0;	// デューティ比(VS-WRC003LVではモーター1)
	TZ0.GRC = 0;	// デューティ比(VS-WRC003LVではモーター2)
	TZ0.GRD = 0;	// デューティ比(VS-WRC003LVでは使用しない)
	TZ1.GRB = 0;	// デューティ比(VS-WRC003LVでは使用しない)
	TZ1.GRC = 0;	// デューティ比(VS-WRC003LVでは使用しない)
	TZ1.GRD = 0;	// デューティ比(VS-WRC003LVでは使用しない)
}

/******************************************************************************
【名称】PWM出力デューティ比設定
【再入】非リエントラント
【入力】TZ0レジスタ GRB～GRD
        TZ1レジスタ GRB～GRB
【出力】なし
【戻値】なし
【処理】PWM出力のデューティ比を設定し、タイマが止まっていたらスタートさせる
        VS-WRC003LVではTZ0のGRB、GRCのみ使用するため、その他のレジスタでは0の設定を推奨
******************************************************************************/
void HAL_PWM_Duty( UH uhTz0Grb, UH uhTz0Grc, UH uhTz0Grd, 
                   UH uhTz1Grb, UH uhTz1Grc, UH uhTz1Grd)
{
	// 引数に従いデューティ比を設定
	TZ0.GRB = uhTz0Grb;	// デューティ比(VS-WRC003LVではモーター1)
	TZ0.GRC = uhTz0Grc;	// デューティ比(VS-WRC003LVではモーター2)
	TZ0.GRD = uhTz0Grd;	// デューティ比(VS-WRC003LVでは使用しない)
	TZ1.GRB = uhTz1Grb;	// デューティ比(VS-WRC003LVでは使用しない)
	TZ1.GRC = uhTz1Grc;	// デューティ比(VS-WRC003LVでは使用しない)
	TZ1.GRD = uhTz1Grd;	// デューティ比(VS-WRC003LVでは使用しない)
	//TZが止まっていたらスタート
	if(TZ.TSTR.BIT.STR0!=1){
		TZ.TSTR.BIT.STR0=1;		//カウントスタート
	}
	if(TZ.TSTR.BIT.STR1!=1){
		TZ.TSTR.BIT.STR1=1;		//カウントスタート
	}
}
#endif
