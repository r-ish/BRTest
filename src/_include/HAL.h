#ifndef _HAL_H_
#define _HAL_H_
/*
************************************************************************
【File Name】Hardware Abstraction Layer 共通ヘッダー
【Description】
【Revision History】
   REV.00 2013-11-04  BY T.OOSAKI
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

#include "PF_Common.h"

// 割り込み禁止と禁止状態から元状態に復帰
extern UB   HAL_DisableIr( void );
extern void HAL_ReturnIr( UB ubCCR );

/*
 * 運用側側面への関数登録インターフェース
 */

/******************************************************************************
【名称】1ミリ秒タイマ割り込み関数登録
【再入】非リエントラント
【入力】1ミリ秒タイマ割り込みで呼び出される関数ポインタ
【出力】なし
【戻値】なし
【処理】タイマ割り込み関数を登録する
******************************************************************************/
extern void HAL_OPE_EntryTmrIR_1MS(void (*fpEntryIR)(void) );

/******************************************************************************
【名称】タスクメイン関数登録
【再入】非リエントラント
【入力】タスク処理関数ポインタ
【出力】なし
【戻値】なし
【処理】タクス処理関数を登録する
******************************************************************************/
extern void HAL_OPE_EntryTaskMain(void (*fpEntryTASK)(void) );

/*
 * LED操作インターフェース
 */

#define HAL_LED_ON  (0x0) // LEDをONにする
#define HAL_LED_OFF (0x1) // LEDをOFFにする

/******************************************************************************
【名称】LED1操作関数
【再入】非リエントラント
【入力】LED1(オレンジ)状態
【出力】なし
【戻値】なし
【処理】LEDの状態を引数で指定した値に変更します
******************************************************************************/

extern void HAL_LED1_Set(UB ubLled1);

/******************************************************************************
【名称】LED2操作関数
【再入】非リエントラント
【入力】LED2(緑)状態
【出力】なし
【戻値】なし
【処理】LEDの状態を引数で指定した値に変更します
******************************************************************************/

extern void HAL_LED2_Set(UB ubLed2 );

/*
 * モーター系統インターフェース
 */

#define HAL_MOTOR_FOWART  (0x1) // モーター方向：前進
#define HAL_MOTOR_BACK    (0x2) // モーター方向：後退

/******************************************************************************
【名称】PWM出力デューティ比設定
【再入】非リエントラント
【入力】TZ0レジスタ GRB〜GRD
        TZ1レジスタ GRB〜GRB
【出力】なし
【戻値】なし
【処理】PWM出力のデューティ比を設定し、タイマが止まっていたらスタートさせる
        VS-WRC003LVではTZ0のGRB、GRCのみモーター出力として使用する。その他のレジスタでは0の設定を推奨
******************************************************************************/
void HAL_PWM_Duty( UH uhTz0Grb, UH uhTz0Grc, UH uhTz0Grd, 
                   UH uhTz1Grb, UH uhTz1Grc, UH uhTz1Grd);

/******************************************************************************
【名称】モーター回転方向操作関数
【再入】非リエントラント
【入力】モーター1の回転方向
        モーター2の回転方向
【出力】なし
【戻値】なし
【処理】モーター1,2の回転方向を決定します
******************************************************************************/

extern void HAL_Motor_DirSet(UB ubMotor1, UB mbMotor2 );


/*
 * スイッチ入力系統インターフェース
 */

#define HAL_SWITCH_OFF  (0x1) // スイッチ状態：入力なし
#define HAL_SWITCH_ON   (0x0) // スイッチ状態：入力あり(押下中)

/******************************************************************************
【名称】スイッチ状態取得関数
【再入】非リエントラント
【入力】なし
【出力】なし
【戻値】スイッチ状態
【処理】スイッチの状態(データレジスタ7の4ビット目)を取得し戻り値で渡します
******************************************************************************/

extern UB HAL_Switch_Get();


#endif /* _HAL_H_ */
