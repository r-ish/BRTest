#ifndef _PF_IN_H_
#define _PF_IN_H_
/*
************************************************************************
【File Name】プラットフォーム機能ヘッダ（内部用）
【Description】
【Revision History】
   REV.00 2014-05-05  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2014 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * インクルード
 */

/*
 * 定数定義
 */

#define TASK_NUM_MAX (2)
#define TASK_LED_ON (0)
#define TASK_LED_OFF (1)

/*
 * 構造体宣言
 */
 
struct STR_TaskData{
	void (*pf)();
	UB request;
}
 
/*
 * 外部関数宣言
 */

#endif /* _PF_IN_H_ */
