/*
************************************************************************
【File Name】ビュートローバー(VS-WRC003LV)用
             モーター操作関数(アプリケーション部)
【Description】
【Revision History】
   REV.00 2014-08-02  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * インクルード
 */
#include "HAL.h"
#include "PF_Common.h"

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

/******************************************************************************
【名称】モーター出力内容変更
【再入】非リエントラント
【入力】モーター1、2の出力方向
        モーター1、2のデューティ比(0.00%～100.00%)
【出力】なし
【戻値】なし
【処理】モーターの出力内容を引数の値に変更する
******************************************************************************/
void APP_Motor_Set(UB ubMotor1Dir,  UB ubMotor2Dir, 
                   UH uhMotor1Duty, UH uhMotor2Duty)
{
	// デューティ比の設定
	HAL_PWM_Duty(uhMotor1Duty, uhMotor2Duty, 0, 0, 0, 0);
	// モーターの出力方向設定
	HAL_Motor_DirSet(ubMotor1Dir, ubMotor2Dir);

}

