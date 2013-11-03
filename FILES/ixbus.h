#ifndef _I2C_H
#define _I2C_H

/* 関数 */
//IXBUS***************************************************/
//I2C初期化
void I2C_init(void);

//VS-IX008またはVS-IX001からデータを取得
//Addr : 拡張ボードのアドレス　,　retdata:　受信データ(長さ8以上、16byte)
char Get_IX008(BYTE Addr,unsigned int *retdata);

#endif