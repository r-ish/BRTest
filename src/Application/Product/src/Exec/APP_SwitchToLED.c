/*
************************************************************************
【File Name】ビュートローバー(VS-WRC003LV)用
　　　　　　 スイッチ入力→LED表示関数
【Description】
【Revision History】
   REV.00 2014-09-06  BY R.ISHIKAWA
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
#include "Application.h"
#include "PF_Common.h"

/*
 * 定数定義
 */

// LED状態の変化カウント数
// #define LED_CHANGE_CNT (50)
// チャタリング防止処理有無
// #define LED_CHATTERLING_CHK_FLG (1)

/*
 * グローバル変数宣言
 */

/*
 * 外部関数宣言
 */

/******************************************************************************
【名称】スイッチ状態LED反映関数
【再入】非リエントラント
【入力】なし
【出力】なし
【戻値】なし
【処理】スイッチの状態を取得し、LEDの状態に反映させる
******************************************************************************/

void APP_Switch_To_LED()
{
	UB ubSwitch = 0x0;
	UB ubLED    = 0x0;

	// 前回のスイッチ入力
	static UB ubInputBefore = HAL_SWITCH_OFF;
	// スイッチ入力の同値継続回数
	static UH uhInputCnt = 0;
		
	// スイッチの値を取得
	ubSwitch = APP_Switch_Get();
	
	// スイッチ入力がONの場合
	if(ubSwitch == HAL_SWITCH_ON)
	{
		// 今回の値を青LEDON
		APP_LED2_Set(HAL_LED_ON);
		// 前回もONの場合
		if(ubInputBefore == HAL_SWITCH_ON)
		{
			// カウントアップ
			uhInputCnt++;
		}
		// 前回OFFの場合
		else
		{
			// 前回値を変更
			ubInputBefore = HAL_SWITCH_ON;
			// カウントリセット
			uhInputCnt = 0;
		}
	}
	// スイッチ入力がOFFの場合
	else
	{
		// 今回の値を青LEDOFF
		APP_LED2_Set(HAL_LED_OFF);
		// 前回もOFFの場合
		if(ubInputBefore == HAL_SWITCH_OFF)
		{
			// カウントアップ
			uhInputCnt++;
		}
		// 前回ONの場合
		else
		{
			// 前回値を変更
			ubInputBefore = HAL_SWITCH_OFF;
			// カウントリセット
			uhInputCnt = 0;
		}
	}
	
	// カウントが規定回数以上
	if(uhInputCnt >= 500)
	{
		// オーバーフロー対策
		uhInputCnt = 500;
		
		// 前回入力に合わせてLED状態変更
		if(ubInputBefore == HAL_SWITCH_ON)
		{
			// LEDの表示を変更する
			APP_LED1_Set(HAL_LED_ON);
			//APP_LED2_Set(ubLED);
		}
		else
		{
			// LEDの表示を変更する
			APP_LED1_Set(HAL_LED_OFF);
			//APP_LED2_Set(ubLED);
		}
	}
	
	/*
	// スイッチの値からLEDの表示状態を決定
	if(ubSwitch == HAL_SWITCH_ON)
	{
		ubLED = HAL_LED_ON;
	}
	else
	{
		ubLED = HAL_LED_OFF;
	}
	// LEDの表示を変更する
	APP_LED1_Set(ubLED);
	APP_LED2_Set(ubLED);
	*/
}


/*
 * 内部関数宣言
 */

