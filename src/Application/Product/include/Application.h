#ifndef _APPLICATION_H_
#define _APPLICATION_H_
/*
************************************************************************
【File Name】アプリケーション昨日
【Description】
【Revision History】
   REV.00 2014-02-11  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

// 外部関数

/******************************************************************************
【名称】LED操作関数
【再入】非リエントラント
【入力】LED1(オレンジ)状態、LED2(緑)状態
【出力】なし
【戻値】なし
【処理】LED1、2の状態を引数で指定した状態に変更する
******************************************************************************/
void APP_LED_Set(UB ubLed1, UB ubLed2);


#endif /* _APPLICATION_H_ */
