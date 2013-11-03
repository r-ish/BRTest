#ifdef __cplusplus
extern "C" {
void abort(void);
#endif
void main(void);
#ifdef __cplusplus
}
#endif

/*インクルード***********************************************************/
#include<36064s.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "vs-wrc003lv.h"
#include "ixbus.h"

/*マクロ***********************************************************/

/*グローバル変数***********************************************************/

/*メイン関数***********************************************************/
/*
このサンプルにはIX010をつかったライントレースサンプルです。
最大の値を示したセンサ値によって、モータの速度を変更し、ライントレースを行います。

*/


/*メイン関数***********************************************************/

void main (void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const unsigned short MainCycle = 60;
	unsigned int data[8];

	Init(MainCycle);		//CPUの初期設定
	I2C_init();				//IXBUS初期化

	LED(3);

	//ループ
	while(1){
		int i;			//ループ用変数
		unsigned int max_param = 0;	//最大のセンサ値を記録する変数
		int s = 0;		//最大のセンサ値の番号を記録する変数
		short mot_L = 0 , mot_R = 0;	//モータ出力用変数

		Sync();

		//addr = 0x90、8個の値を受信
		if(Get_IX008(0x90,data) != 0){	//正常に受信したら
			for(i=0;i<8;i++){
				//現在確認しているセンサの値が,これまでの最大値よりも大きいとき
				if(data[i] > max_param){
					max_param = data[i];	//最大値を更新
					s = i;					//現在のセンサの番号を記録
				}
			}
		}

		//最大値がしきい値以上だったら
		if(max_param < 3000){

			LED(1);
			//取得したセンサ番号に応じてモータの速度を設定
			switch(s){
			case 0:								//S1の場合
				mot_R = -3000; mot_L = -10000;
				break;
			case 1:								//S2の場合
				mot_R = 0; mot_L = -10000;
				break;
			case 2:								//S3の場合
				mot_R = 3000; mot_L = -10000;
				break;
			case 3:								//S4の場合
				mot_R = 7000; mot_L = -10000;
				break;
			case 4:								//S5の場合
				mot_R = 10000; mot_L = -7000;
				break;
			case 5:								//S6の場合
				mot_R = 10000; mot_L = -3000;
				break;
			case 6:								//S7の場合
				mot_R = 10000; mot_L = 0;
				break;
			case 7:								//S8の場合
				mot_R = 10000; mot_L = 3000;
				break;
			}

			Mtr_Run_lv(mot_R,mot_L,0,0,0,0);	//モータ速度を更新
		}
		//しきい値以下だったら停止
		else {
			LED(2);
			Mtr_Run_lv(0,0,0,0,0,0);	//モータを停止
		}
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
