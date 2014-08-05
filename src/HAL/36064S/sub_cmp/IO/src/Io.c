/*
************************************************************************
【File Name】ビュートローバー(VS-WRC003LV)用
             IOポート操作
【Description】
【Revision History】
   REV.00 2014-01-25  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2014 IPL CORPORATION All Rights Reserved
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
【名称】IOポートレジスタ初期化
【再入】非リエントラント
【入力】なし
【出力】なし
【戻値】なし
【処理】I/Oポートレジスタの初期化
        使用するポートのレジスタを初期化します
******************************************************************************/
void IO_Init( void )
{
	// ポート6のビット4、ビット0を出力に指定します
	// (LED出力を行います)
	TZ.TOER.BIT.EA1   = 0x0;
	TZ.TOER.BIT.EA0   = 0x0;
	TZ0.TIORA.BIT.IOA = 0x0;
	IO.PCR6 = 0x17;// 0〜2ビット目、4ビット目(PCR60、61、62、64)を1(出力)に変更する
	IO.PCR3 = 0xFF;// 全ビットを1(出力)に変更する
	IO.PDR6.BIT.B0 = 0;
	IO.PDR6.BIT.B4 = 0;
}

/******************************************************************************
【名称】LED1操作関数
【再入】非リエントラント
【入力】LED1(オレンジ)状態
【出力】なし
【戻値】なし
【処理】LEDの状態(データレジスタ6の0ビット目)を引数で指定した値に変更します
******************************************************************************/

void HAL_LED1_Set(UB ubLled1)
{
	IO.PDR6.BIT.B0 = ubLled1;
}

/******************************************************************************
【名称】LED2操作関数
【再入】非リエントラント
【入力】LED2(緑)状態
【出力】なし
【戻値】なし
【処理】LEDの状態(データレジスタ6の4ビット目)を引数で指定した値に変更します
******************************************************************************/

void HAL_LED2_Set(UB ubLed2 )
{
	IO.PDR6.BIT.B4 = ubLed2;
}

/******************************************************************************
【名称】モーター回転方向操作関数
【再入】非リエントラント
【入力】モーター1の回転方向
        モーター2の回転方向
【出力】なし
【戻値】なし
【処理】モーター1,2の回転方向を決定します
******************************************************************************/

void HAL_Motor_DirSet(UB ubMotor1, UB mbMotor2 )
{
	UB ubTmp;
	
	// PDR3の値のうち、モーター1、2の部分(下位4バイト)を0に初期化する
	ubTmp = IO.PDR3.BYTE;
	ubTmp &= 0xF0;
	
	// 取得したPDR3の下位4バイトを変数の値にして、データレジスタに書き込む
	ubTmp |= ubMotor1;
	ubTmp |= mbMotor2 << 2;
	
	IO.PDR3.BYTE = ubTmp;
}




#endif
