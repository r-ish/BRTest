#ifndef  _VSWRC003_H
#define _VSWRC003_H

typedef signed char SBYTE;
typedef unsigned char UBYTE;
typedef unsigned char BYTE;
typedef signed short SWORD;
typedef unsigned short UWORD;
typedef signed int SINT;
typedef unsigned int UINT;
typedef signed long SDWORD;
typedef unsigned long UDWORD;


//汎用********************************************************************/
/*
CPU初期化
CPU全体の初期化関数。Sync()関数で利用する周波数を与える。
引数：Sync関数の同期周波数（単位はHz、30Hz以上)
戻り値：無し
*/
void Init(BYTE MainCycle);

/*
ボタン状態取得
CPUボード上の押しボタンの状態を取得する　
引数：　無し
戻り値：　0:off　1:on
*/
BYTE getSW();

/*
LED制御
CPUボード上の２つのLEDを制御する関数
引数：　0:消灯　1:緑　2:オレンジ　3：両方
戻り値：　無し
*/
void LED(BYTE LedOn);

/*
時間待ち　
引数：　待ち時間（単位：msec）
戻り値：　無し
*/
void Wait(int msec);

/*
同期関数
Init()関数で設定した周波数で同期し、処理を戻す関数。
例：Maincycle を60Hzに設定した場合、以下のソースでは、処理Aが60Hzで実行される。
ただし、処理Aが1/60sec以上かかる場合は意味を成さない。
while(1){
	Sync();
	処理A;
}

引数：　無し
戻り値：　内部で待ったカウント（単位無し）。０の場合、設定した周波数で同期できていない。
			
*/
UINT Sync();

/*
Sync関数の同期周波数取得
Initで設定した同期周波数を取得する
引数：　無し
戻り値：　同期周波数（Hz）
*/
BYTE getMainCycle();


//モータ********************************************************************/

/*
モータの駆動
設定した速度でモータを駆動。呼び出した後はその状態を保持し、制御値に0を与えるまで停止しない。

引数：　モータの制御値
		0		：フリー	
		0x8000	：フリー
		CW_MAX	：0x7FFF　(32767)
		CCW_MAX	：0x8001　(-32767)
戻り値：　無し
*/
void Mtr_Run_lv(int mt1,int mt2,int mt3,int mt4,int mt5,int mt6);

//VS-WRC003との互換性確保のため使用
/*
モータの駆動
設定した速度でモータを駆動。呼び出した後はその状態を保持し、制御値に0を与えるまで停止しない。

引数：　モータの制御値
		0		：フリー
		0x80	：フリー
		CW_MAX	：0x7F　(127)
		CCW_MAX	：0x81　(-127)
戻り値：　無し
*/
void Mtr_Run(BYTE mt1,BYTE mt2,BYTE mt3,BYTE mt4);


//AD入力値取得　0～7チャンネル*****************************************************/
//#define AD_SCANMODE

/*
AD入力値取得
A/D変換の入力値を取得。
引数：　チャンネル（0～7　=　1～8)
戻り値：　A/D変換の値(0～1023)
*/
UINT AdRead(BYTE ch);


//シリアル通信********************************************************************/
#define SCI_RB_SIZE 60	//受信バッファ
#define SCI_TX_SIZE 128	//送信バッファ

//送信に割り込みを使用しない場合、コメントアウトすること。
//わからない場合、そのままでもOKです。
//#define SCI_TX_INTERRUPT

//ボーレート vs-wrc003lv 12MHz
enum brd{
CBR_115200 = 2,
CBR_57600 = 6,
CBR_38400 = 9,
CBR_31250 = 11,
CBR_19200 = 19,
CBR_14400 = 25,
CBR_9600 = 38,
CBR_4800 = 77,
CBR_2400 = 155,
};

/*パリティ*/
enum Parity{
even,
odd,
non
};

/*
初期化
シリアル通信を使用する前に初期化が必要。
引数：　baudrate　：　ボーレートの指定（上記列挙子から指定）
		parity　：　パリティの設定（上記列挙子から指定）
		stop　：　ストップビット長の設定（0～2）
戻り値：無し
*/
void InitSci3(BYTE baudrate,BYTE parity ,BYTE stop);

/*
1バイト受信
シリアル通信で1バイト受信する関数。
（実際にはバッファから1バイトのみ持ってくる）
引数：　受信データを入れる変数のポインタ
戻り値：	0：バッファが空
			1：バッファにデータ有り		
*/
BYTE SciByteRx(BYTE *data);

/*
1バイト送信
シリアル通信で1バイト送信する関数。
引数：　送信データ
戻り値：	0：バッファががいっぱい、送信エラー
			1：送信完了	
*/
BYTE SciByteTx(BYTE data);

/*
文字列送信
文字列orバイトデータの配列を送信する関数。
引数：　*str：送信する文字列のポインタ
		dataleng：送信する文字数
戻り値：	0：バッファががいっぱい、送信エラー
			1：送信完了	
*/
BYTE SciStrTx(BYTE *str,UINT dataleng);


//ブザー********************************************************************/


/*
音程、ボリュームの設定
ブザーを鳴らす際の音程とボリュームを設定
引数：　pitch：音程の設定（0～255、値が大きいほど低い音）
		vol：ボリュームの設定（0～128）
戻り値：無し
*/
void BuzzerSet(BYTE pitch , BYTE vol);

/*
開始
ブザーを鳴らし始める。BuzzerStop()関数を呼ぶまでなり続ける。
引数：無し
戻り値：無し
*/
void BuzzerStart();

/*
停止
ブザーを止める。
引数：無し
戻り値：無し
*/
void BuzzerStop();

/*
ブザーが鳴っているかどうか確認
引数：無し
戻り値：	0：鳴っていない
			1：鳴っている	
*/
BYTE isBuzzer();


//PSPAD********************************************************************/
/*
PADデータ更新
getPADで取得するPADデータのバッファを最新の情報に更新。
呼び出さない場合、getPADで同じタイミングのデータが取得される。
定期的に呼び出すことが必要。
引数：無し
戻り値：無し
*/
void updatePAD();

/*
データ取得
バッファからパッドの状態データを取得する。
引数には列挙子PADDATAから必要なものを指定

引数：　取得するデータの番号（列挙子からの指定でOK）
戻り値：　パッドの状態データ
*/
char getPAD(BYTE num);


/*
		b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0
PAD_B1：	左 | 下 | 右 | 上 |ｽﾀｰﾄ| R3 | L3 |ｾﾚｸﾄ
PAD_B2：	□ | × | ○ | △ | R1 | L1 | R2 | L2 
PAD_AN_RX：	左:00h,中心:80h,右:FFh
PAD_AN_RY：	上:00h,中心:80h,下:FFh
PAD_AN_LX：	左:00h,中心:80h,右:FFh
PAD_AN_LY：	上:00h,中心:80h,下:FFh
*/

enum PADDATA{
PAD_B1,			//ボタン1バイト目
PAD_B2,			//ボタン2バイト目
PAD_AN_RX,		//右アナログスティック左右
PAD_AN_RY,		//右アナログスティック上下
PAD_AN_LX,		//左アナログスティック左右
PAD_AN_LY		//左アナログスティック上下
};


//エンコーダ**************************************************/
/*
エンコーダ初期化
エンコーダ拡張を使用する際に、Init()後に1度だけ実行する必要がある
引数：無し
戻り値：無し
*/
void InitEncoder();

/*
エンコーダクリア
エンコーダでカウントしている値を0にクリアする
引数：無し
戻り値：無し
*/
void ClearEncoder();

/*
エンコーダ値取得
エンコーダでカウントしている値取得する
引数：	*L：左側のカウントを取得する変数のポインタ
		*R：右側のカウントを取得する変数のポインタ
戻り値：無し
*/
void GetEncoder(long *L,long *R);



//ユーザ使用不可
void intencoder();
BYTE intsci3();

#endif