
#include<36064s.h>
#include <string.h>
#include <machine.h>
#include "vs-wrc003lv.h"
#include "ixbus.h"


void I2C_waitFree(void);
void I2C_sendStartBit(void);
void I2C_sendStopBit(void);
void I2C_setTransmitMode(BYTE);
BYTE I2C_sendByte(BYTE);
BYTE I2C_receiveByte(BYTE, BYTE);
BYTE I2C_receive008(BYTE *data, BYTE size);

const char cHexString[16] = "0123456789ABCDEF";
unsigned char errcnt;

// I2C初期化
void I2C_init(void) {
	unsigned temp;

	//I2Cを停止、リセット
    IIC2.ICCR1.BIT.ICE = 0;	
    IIC2.ICCR2.BIT.BBSY = 0;
    IIC2.ICCR2.BIT.SCP = 0;
	Wait(1);
	IIC2.ICCR2.BIT.IICRST = 1;
	temp = IIC2.ICSR.BYTE;
	IIC2.ICSR.BYTE = 0;
	
	//初期化
	IIC2.ICCR1.BIT.CKS = 0x0F;		// I2Cの転送レートΦ/128(Φ=14.7456MHz, 115.2kHz)

	IIC2.ICMR.BIT.MLS = 0;			// MSB First
	IIC2.ICMR.BIT.WAIT = 0;			// WAIT無し
	IIC2.ICMR.BIT.BCWP = 0;			// ビットカウンタライトプロテクト解除
	IIC2.ICMR.BIT.BC = 0;			// 9ビット
	IIC2.ICMR.BIT.BCWP = 1;			// ビットカウンタライトプロテクト開始

    IIC2.ICCR1.BIT.ICE = 1;
}

// I2Cが空くまで待つ
void I2C_waitFree() {
	unsigned int i = 0;
    while (IIC2.ICCR2.BIT.BBSY == 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}
	};
}

// I2Cに開始要求
void I2C_sendStartBit() {
    IIC2.ICCR2.BYTE = 0xBD;
}

// I2Cに停止要求
void I2C_sendStopBit() {
	unsigned int i = 0;
	IIC2.ICSR.BIT.STOP = 0;
	IIC2.ICCR2.BYTE = 0x3D;
	
    while(IIC2.ICSR.BIT.STOP != 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}		//TimeOut wait
	};
//	while (IIC2.ICSR.BIT.STOP != 1);
}

// I2C送受信モードの設定
//    0: スレーブ受信
//    1: スレーブ送信
//    2: マスタ受信
//    3: マスタ送信
void I2C_setTransmitMode(BYTE mode) {
	mode <<= 4;
	IIC2.ICCR1.BYTE = ((IIC2.ICCR1.BYTE & 0xCF) | mode);	// 送受信モード設定
}

// I2C バスへ1バイト送信
BYTE I2C_sendByte(BYTE data) {
	unsigned int i = 0;
    while (IIC2.ICSR.BIT.TDRE != 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}
	};
//	while(IIC2.ICSR.BIT.TDRE != 1);
	IIC2.ICDRT = data;
	while (IIC2.ICSR.BIT.TEND != 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}
	};		// データ送信
//	while(IIC2.ICSR.BIT.TEND != 1);
	return(IIC2.ICIER.BIT.ACKBR);	// ACKを返す
}

// I2C バスから1バイト受信
//    ack: データ受信時相手に返すACKビット
//    rcvd: 最終バイトをリードするときは1にするこの後停止条件発行可能になる
//          連続してデータ受信する場合は0
BYTE I2C_receiveByte(BYTE ack, BYTE rcvd) {
   	unsigned int i = 0;
   
    BYTE rdt;

    IIC2.ICIER.BIT.ACKBT = ack;		// データ受信後に送信するACKフラグを設定する
    IIC2.ICCR1.BIT.RCVD = rcvd;		// 最終バイト読み込み時は1
    rdt = IIC2.ICDRR;				// 受信開始
     while (IIC2.ICSR.BIT.RDRF != 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}
	}; 
	//while(IIC2.ICSR.BIT.RDRF != 1);	// データが8bit転送されるまで待つ
    rdt = IIC2.ICDRR;
    return(rdt);
}

BYTE I2C_receive008(BYTE *data, BYTE size) {
    BYTE rdt;
	unsigned int i = 0;
	
	IIC2.ICIER.BIT.ACKBT = 0;		// データ受信後に送信するACKフラグを設定する
    IIC2.ICCR1.BIT.RCVD = 0;		// 最終バイト読み込み時は1
    rdt = IIC2.ICDRR;				// 受信開始
    while (IIC2.ICSR.BIT.RDRF != 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}
	}; 
//	while(IIC2.ICSR.BIT.RDRF != 1);	// データが8bit転送されるまで待つ	
	IIC2.ICIER.BIT.ACKBT = 1;		// データ受信後に送信するACKフラグを設定する
    IIC2.ICCR1.BIT.RCVD = 1;		// 最終バイト読み込み時は1
    data[0] = IIC2.ICDRR;
	i = 0;
    while (IIC2.ICSR.BIT.RDRF != 1){
		i++;
		if(i > 0xFFFE){
			errcnt++;
			break;
		}
	}; 
//	while(IIC2.ICSR.BIT.RDRF != 1);	// データが8bit転送されるまで待つ	
    data[1] = IIC2.ICDRR;
	
    return 1;
}

//addr = 0x90,0x92,0x94,0x96
char Get_IX008(BYTE Addr,unsigned int *retdata){
	const BYTE commandByte[] = {0x8C,0xCC,0x9C,0xDC,0xAC,0xEC,0xBC,0xFC};
	BYTE data[2];
	unsigned int a;
	BYTE i,j,z;
	
// アナログ入力（IXBUS）
	i = 0;	
	errcnt = 0;
	z = 0;
	while(i < 8){
		I2C_waitFree();					// I2C バス空き待ち
		if(errcnt>0){errcnt++;break;}
		
		I2C_setTransmitMode(3);		// マスタ送信モード
		
		I2C_sendStartBit();			// I2C バスを開始条件にする
		
		if(I2C_sendByte(Addr) == 1){  	// スレーブアドレスを送信
			if(errcnt>0){errcnt++;break;}
			I2C_sendStopBit();		// i2c バスを停止条件にする。
			if(errcnt>0){errcnt++;break;}
			errcnt ++;
		}
		
		if(!errcnt){
			I2C_sendByte(commandByte[i]);	// 8C CC 9C DC AC EC BC FC (chセレクト）
			if(errcnt>0){errcnt++;break;}
			
		    I2C_sendStartBit();				// i2c バスを開始条件にする
			
			if(I2C_sendByte(Addr + 1) == 1)	{		// スレーブアドレスを送信
				if(errcnt>0){errcnt++;break;}
				I2C_sendStopBit();			// i2c バスを停止条件にする。
				if(errcnt>0){errcnt++;break;}
				errcnt ++;
			}
		}		
		if(!errcnt){
		    I2C_setTransmitMode(2);			// マスタ受信モード
		    IIC2.ICSR.BIT.TDRE = 0;

		    I2C_receive008(data, 2);
			if(errcnt>0){errcnt++;break;}
				
			I2C_sendStopBit();				// i2c バスを停止条件にする。
			if(errcnt>0){errcnt++;break;}
				
		    IIC2.ICCR1.BIT.RCVD = 0;
		
			I2C_setTransmitMode(0);			// スレーブ受信モードにする
			
			retdata[i] = ((unsigned int)data[0] << 8) + data[1];		// 12ビットデータに
			
			i++;
		//	errcnt = 0;
		}
		else{
			break;
		}
	}
	if(errcnt){
		I2C_init();
		errcnt = 0;
		
		return 0;
	}
	return 1;
}