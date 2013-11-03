#include<36064s.h>
#include <string.h>
#include "vs-wrc003lv.h"
#include <machine.h>

int PS_Set_AN();
BYTE Ds2rw(const BYTE *cmd);
void Ds2Com(const BYTE * cmd,BYTE txLen);


void InitAD();
void InitMtrPwm();

//MtrPWM ********************************************************************//
UINT mtr_pwm_cyc = 0x7000;

void InitMtrPwm()
{	
	TZ.TSTR.BIT.STR0=0;
	TZ.TSTR.BIT.STR1=0;
	
	TZ0.TCR.BYTE =	0x20;	//GRAでクリア、立上りエッジ、φでカウント
	TZ1.TCR.BYTE =	0x20;	//GRAでクリア、立上りエッジ、φでカウント
	
	TZ.TPMR.BYTE =	0xFF;	//PWM
		
	TZ.TOCR.BYTE =	0x00;	//TZ0：はじめ1出力	,1:1出力
		
	TZ0.POCR.BYTE = 0x00;
	TZ1.POCR.BYTE = 0x00;
	
	TZ.TOER.BYTE =	0x11;	//TZ0：出力許可
		
	TZ.TMDR.BYTE =	0x00;	//通常
	TZ.TFCR.BYTE =	0x00;	//通常
	
	TZ0.TSR.BYTE =	0x00;	//エラーフラグクリア
	TZ1.TSR.BYTE =	0x00;	//エラーフラグクリア

	TZ0.TCNT=0;
	TZ1.TCNT=0;

	TZ0.GRA=mtr_pwm_cyc;
	TZ1.GRA=mtr_pwm_cyc;
	
	TZ0.GRB = 0;
	TZ0.GRC = 0;
	TZ0.GRD = 0;
	TZ1.GRB = 0;
	TZ1.GRC = 0;
	TZ1.GRD = 0;	
}

void Mtr_Run(BYTE mt1,BYTE mt2,BYTE mt3,BYTE mt4){
	if(mt1 == 0x80)
		mt1 == 0;
	if(mt2 == 0x80)
		mt2 == 0;
	if(mt3 == 0x80)
		mt3 == 0;
	if(mt4 == 0x80)
		mt4 == 0;
	Mtr_Run_lv(	(int)mt1*0x00FF,
				(int)mt2*0x00FF,
				(int)mt3*0x00FF,
				(int)mt4*0x00FF,
				0,0);
}

void Mtr_Run_lv(int mt1,int mt2,int mt3,int mt4,int mt5,int mt6)
{
	BYTE i,PortOut_3,PortOut_5,PortOut_1;
	UINT duty[6];
	PortOut_3 = 0x00;
	PortOut_5 = 0x00;
	PortOut_1 = 0x00;
		//デューティのセット
		for(i=0;i<6;i++){
			int MTRtemp,MTRtempB;
			int tempSint;
			switch(i){
				case 0:
					MTRtemp = mt1;
					break;
				case 1:
					MTRtemp = mt2;
					break;
				case 2:
					MTRtemp = mt3;
					break;
				case 3:
					MTRtemp = mt4;
					break;
				case 4:
					MTRtemp = mt5;
					break;
				case 5:
					MTRtemp = mt6;
					break;
			}			
			if(MTRtemp == 0 || MTRtemp == 0x8000){
				tempSint=0;
			}
			else if(MTRtemp > 0){
				tempSint = MTRtemp;
				switch(i){
					case 0: //P31
					case 2:	//P35
						PortOut_3 |= (0x02 << i*2);			
						break;
					case 1:	//P32
					case 3:	//P36
						PortOut_3 |= (0x01 << i*2);	
						break;
					case 4://P12
						PortOut_1 = (0x01 << 2);
						break;
					case 5:	//P54
						PortOut_5 = (0x01 << 4);
						break;
				}			
			}
			else if(MTRtemp < 0){			//P31,32,35,36,12,54
				tempSint = -MTRtemp;
				switch(i){
					case 0:	//P30
					case 2:	//P34
						PortOut_3 |= (0x01 << i*2);	
						break;
					case 1:	//P33
					case 3: //P37
						PortOut_3 |= (0x02 << i*2);
						break;	
					case 4://P10
						PortOut_1 = (0x01 << 0);
						break;
					case 5:	//P55
						PortOut_5 = (0x01 << 5);
						break;
				}	
			}
			duty[i]=(UINT)(((unsigned long)tempSint*(unsigned long)mtr_pwm_cyc)/0x8000);
		}
		IO.PDR3.BYTE = 0x00;
		
		TZ0.GRB = duty[0];
		TZ0.GRC = duty[1];
		TZ0.GRD = duty[2];
		TZ1.GRB = duty[3];
		TZ1.GRC = duty[4];
		TZ1.GRD = duty[5];
		
		//TZが止まっていたらスタート
		if(TZ.TSTR.BIT.STR0!=1){
			TZ.TSTR.BIT.STR0=1;		//カウントスタート
		}
		if(TZ.TSTR.BIT.STR1!=1){
			TZ.TSTR.BIT.STR1=1;		//カウントスタート
		}
		// LL :HiZ（out：ZZ）  HL,LH:drive  HH:ブレーキ（out：LL）に変更必要 
		
		IO.PDR3.BYTE = PortOut_3;
		IO.PDR1.BYTE = (PortOut_1 & 0x05)|(IO.PDR1.BYTE & 0xFA);	//P10,12 0x05 0xFA
		IO.PDR5.BYTE = (PortOut_5 & 0x30)|(IO.PDR5.BYTE & 0xCF);	//P54,55 0x30 0xCF
}



//ADin ********************************************************************//
void InitAD()
{
#ifdef AD_SCANMODE
	AD.ADCR.BYTE=0x00;	
	AD.ADCSR.BYTE=0x13;
#else
	AD.ADCR.BYTE=0x00;	
	AD.ADCSR.BYTE=0x03;
	AD.ADCSR.BIT.ADST=1;
#endif
}

UINT AdRead(BYTE ch)
{
#ifdef AD_SCANMODE
		return 0;
#else
	BYTE temp;
	UDWORD x;
	
	AD.ADCSR.BIT.ADST=0;
	AD.ADCR.BYTE=0x00;
	AD.ADCSR.BYTE=0;
	
	if(ch>0x07)
		return 0;
		
	AD.ADCSR.BYTE=ch;
		
	AD.ADCSR.BIT.ADST=1;
	
	while (AD.ADCSR.BIT.ADF!=1);
	AD.ADCSR.BIT.ADF=0;	
	AD.ADCSR.BIT.ADST=0;
	
	
	x=0;
	switch(ch%4){
		case 0:
			x=AD.ADDRA;
			break;
		case 1:
			x=AD.ADDRB;
			break;
		case 2:
			x=AD.ADDRC;
			break;
		case 3:
			x=AD.ADDRD;
			break;
	}
	return (UINT)(x>>6);
	
#endif
}

//buzzer **********************************************************************//
//BYTE bzr_PITCH;
//BYTE bzr_VOL;

void BuzzerSet(BYTE pitch , BYTE vol){
	TV.TCRV1.BYTE=0x01;
	TV.TCRV0.BYTE=0x10;
	TV.TCSRV.BYTE=0x06;

	//bzr_PITCH = pitch;
	//bzr_VOL = vol;
	
	TV.TCRV0.BIT.CKS=0;
	TV.TCORA=(BYTE)((double)vol*((double)pitch/256.0));
	TV.TCORB=pitch;
}

void BuzzerStart(){	
	TV.TCRV0.BIT.CKS=3;
}
BYTE isBuzzer(){
	if(TV.TCRV0.BIT.CKS == 0){
		return 0;
	}
	return 1;
}
void BuzzerStop(){
	TV.TCRV0.BIT.CKS=0;
}


//SCI ************************************************************************//

#ifdef SCI_TX_INTERRUPT
volatile BYTE sci_txrb[SCI_TX_SIZE]; 
#endif

volatile BYTE sci_rxrb[SCI_RB_SIZE];
BYTE rb_rd_num;
BYTE rb_wr_num;
BYTE tx_rd_num;
BYTE tx_wr_num;

BYTE intsci3(){
	BYTE str[4],temp,next;

	if((SCI3.SSR.BYTE & 0x18) == 0 && SCI3.SSR.BIT.RDRF == 1)
	{          
		next=(rb_wr_num+1)%SCI_RB_SIZE;
		
		if(rb_rd_num!=next){
			SCI3.SSR.BYTE &= 0x87;
			sci_rxrb[rb_wr_num] = SCI3.RDR;			//  データを受け取りdataに保存 
			rb_wr_num=next;
			return 0;
		}
	}
	else{
		temp = SCI3.RDR;
		SCI3.SSR.BYTE &= 0x87;
	}
	
	
#ifdef SCI_TX_INTERRUPT
	if(SCI3.SSR.BIT.TDRE == 1){	
		if(tx_rd_num != tx_wr_num)	//受信バッファ空じゃなかったら
		{
			SCI3.TDR = sci_txrb[tx_rd_num];
			tx_rd_num = (tx_rd_num + 1) % SCI_TX_SIZE;
			return 1;
			
		}
	}
	if(SCI3.SSR.BIT.TEND == 1){
		SCI3.SCR3.BIT.TIE = 0;
	}
	
#endif
	
    return 1;
}


BYTE SciByteRx(BYTE *data)
{
	if(rb_rd_num!=rb_wr_num)	//受信バッファ空じゃなかったら
	{	
		*data=sci_rxrb[rb_rd_num];
		rb_rd_num=(rb_rd_num+1)%SCI_RB_SIZE;
		return 1;
	}
	else
		return 0;
}

void InitSci3(BYTE baudrate,BYTE parity ,BYTE stop)
{
	UINT dmy;
	BYTE smr = 0;
	
	switch(parity){
		case even:
			smr = 0x20;
		break;
		case odd:
			smr = 0x30;
		break;
		case non:
		default:
			smr = 0x00;
		break;
	}
	if(stop == 2){
		smr |= 0x08;
	}
	rb_rd_num = 0;
	rb_wr_num = 0;
	
	SCI3.SCR3.BYTE = 0;       //ｼﾘｱﾙｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ(SCIの送信/受信動作設定)
	SCI3.SMR.BYTE = smr;       //ｼﾘｱﾙﾓｰﾄﾞﾚｼﾞｽﾀ(SCIの通信ﾌｫｰﾏｯﾄの設定)
	SCI3.BRR = (BYTE)baudrate;	          //1bps
	
	for(dmy = 280;dmy > 0;dmy--); //Wait 1bit transfer time
	
	SCI3.SCR3.BYTE = 0x70;    //Enable Tx & Rx ,enable Rx interrupt
	IO.PMR1.BIT.TXD=1;
	SCI3.SSR.BYTE &= 0x80;   //Clear receive error flag
	
}

#ifdef SCI_TX_INTERRUPT

BYTE SciByteTx(BYTE data)
{
	BYTE next;
	next=(tx_wr_num + 1)%SCI_TX_SIZE;
		
	if(tx_rd_num != next){	
		sci_txrb[tx_wr_num] = data;			//  データを受け取りdataに保存 
		tx_wr_num = next;
	}
	else
		return 0;
		
	if(SCI3.SSR.BIT.TEND == 1 && SCI3.SSR.BIT.TDRE == 1){	//送信中じゃなかったら
		SCI3.SCR3.BIT.TIE = 1;
		intsci3();	
	}
	return 1;
	
		
}
BYTE SciStrTx(BYTE *str,UINT dataleng){
	BYTE next,i,wr_temp;
	wr_temp = tx_wr_num;
	//バッファの空き状況を確認
	for(i = 0;i < dataleng;i++){
		next = (wr_temp + 1)%SCI_TX_SIZE;		
		if(wr_temp != next){
			wr_temp = next;
		}
		else
			return 0;
		
	}
	//送信データをバッファにセット
	for(i = 0;i < dataleng;i++){
		next = (tx_wr_num + 1)%SCI_TX_SIZE;
		
		//念のため再確認
		if(tx_rd_num != next){	
			sci_txrb[tx_wr_num] = str[i];			//  データを受け取りdataに保存 
			tx_wr_num = next;
		}
		else
			return 0;
	}
	if(SCI3.SSR.BIT.TEND == 1 && SCI3.SSR.BIT.TDRE == 1){	//送信中じゃなかったら
		SCI3.SCR3.BIT.TIE = 1;
		intsci3();
	}
	return 1;
}

#else

BYTE SciByteTx(BYTE data)
{
	
	SCI3.SCR3.BIT.TE=1;
	while(SCI3.SSR.BIT.TDRE!=1);
	
	SCI3.TDR=data;
	
	while(SCI3.SSR.BIT.TEND!=1);
	SCI3.SCR3.BIT.TE=0;
	
	return 1;
}

BYTE SciStrTx(BYTE *str,UINT dataleng)
{
	UINT i;
	SCI3.SCR3.BIT.TE=1;
	
	for(i=0;i<dataleng;i++)
		SciByteTx(str[i]);
		
	return 1;
}

#endif

//GAME_PAD ********************************************************//

//GAME_PAD
#define PS_SEL_raise	IO.PDR2.BIT.B3 = 1
#define PS_SEL_fall		IO.PDR2.BIT.B3 = 0
#define PS_CLK_raise	IO.PDR2.BIT.B4 = 1
#define PS_CLK_fall		IO.PDR2.BIT.B4 = 0
#define PS_CMD_raise	IO.PDR2.BIT.B0 = 1
#define PS_CMD_fall		IO.PDR2.BIT.B0 = 0
#define PS_DAT			IO.PDR7.BIT.B5
#define PS_CLK_BIT		IO.PDR2.BIT.B4

static const BYTE CMD_config_mode_enter[] =     {0x01,0x43,0x00,0x01, 0x00,0x00,0x00,0x00, 0x00};
static const BYTE CMD_config_mode_exit[] =      {0x01,0x43,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00};
static const BYTE CMD_config_mode_exit2[] =      {0x01,0x43,0x00,0x00, 0x5a,0x5a,0x5a,0x5a, 0x5a};
static const BYTE CMD_set_mode_and_lock[] =     {0x01,0x44,0x00,0x01, 0x03,0x00,0x00,0x00, 0x00};
static const BYTE CMD_query_model_and_mode[] =  {0x01,0x45,0x00,0x5a, 0x5a,0x5a,0x5a,0x5a, 0x5a};
static const BYTE CMD_vibration_enable[] =      {0x01,0x4d,0x00,0x00, 0x01,0xff,0xff,0xff, 0xff};
static const BYTE CMD_vibration_disnable[] =    {0x01,0x4d,0x00,0xff, 0xff,0xff,0xff,0xff, 0xff};
static const BYTE CMD_query_DS2_analog_mode[] = {0x01,0x41,0x00,0x5a, 0x5a,0x5a,0x5a,0x5a, 0x5a};
static const BYTE CMD_set_DS2_native_mode[] =   {0x01,0x4f,0x00,0xff, 0xff,0x03,0x00,0x00, 0x00};
static const BYTE CMD_read_data[] =             {0x01,0x42,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00}; 
static const BYTE CMD_read_data2[] =            {0x01,0x42,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 
											0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00};

BYTE PS_DATA[10];
//受信データ
static BYTE PADRD[30];
#define muda 4

BYTE Ds2rw(const BYTE *cmd){
	
	BYTE TempCmd;
	BYTE i,j,data,clk_cnt = 1;
	

	data=0;
	PS_CLK_raise;
	PS_CMD_raise;
	TempCmd = *cmd;

  
  for(j=0;j<muda;j++);	//muda
  
  for(i=0;i<8;i++){
    if( (TempCmd & 0x01) == 0) /* CMDセット */
        PS_CMD_fall;
    else
        PS_CMD_raise;

    TempCmd = TempCmd >> 1;
    PS_CLK_fall;
    
    for(j=0;j<muda;j++);	//muda
	
	if(PS_DAT!=0)
    	data+=clk_cnt;
	PS_CLK_raise;

    clk_cnt*=2;
    
  }
  PS_CMD_raise;
  return data;
}


//各コマンド送受信
void Ds2Com(const unsigned char * cmd,unsigned char txLen){
  unsigned char i,j;
  PS_SEL_fall;
  
  for(j=0;j<muda;j++);	//muda
  
  for(i = 0; i < txLen;i++){
    for(j=0;j<muda*3;j++);	//muda
	PADRD[i]=Ds2rw(cmd+i);
  }
  
  PS_SEL_raise;
  
}


int PS_Set_AN()
{
	int a,i;
	const unsigned char temp[4]={0xFF,0xFF,0x03,0x5A};
	
	a=0;
	for(i=0;i<30;i++);
	Ds2Com(CMD_config_mode_enter,sizeof(CMD_config_mode_enter));	//コンフィグモードへ
	for(i=0;i<30;i++);
	Ds2Com(CMD_config_mode_enter,sizeof(CMD_config_mode_enter));	//コンフィグモードへ
	for(i=0;i<30;i++);

	Ds2Com(CMD_query_model_and_mode,sizeof(CMD_query_model_and_mode));
	for(i=0;i<30;i++);
	Ds2Com(CMD_query_model_and_mode,sizeof(CMD_query_model_and_mode));
	for(i=0;i<30;i++);

		Ds2Com(CMD_set_mode_and_lock,sizeof(CMD_set_mode_and_lock));
		for(i=0;i<100;i++);
		Ds2Com(CMD_set_mode_and_lock,sizeof(CMD_set_mode_and_lock));
		for(i=0;i<100;i++);
		Ds2Com(CMD_config_mode_exit,sizeof(CMD_config_mode_exit));
		for(i=0;i<100;i++);
		Ds2Com(CMD_config_mode_exit,sizeof(CMD_config_mode_exit));
		return 1;

	return 0;
}


void updatePAD()
{
	static unsigned char flag;
	int i;
	
	Ds2Com(CMD_read_data,sizeof(CMD_read_data));	
	
	if(PADRD[2] == 0x5a)
	{
		if(PADRD[1] == 0x73){
			PS_DATA[0] = ~PADRD[3];
			PS_DATA[1] = ~PADRD[4];
			for(i = 2 ; i < 6 ; i++ )
				PS_DATA[i] = PADRD[3+i] - 0x80;
		}
		else{
			PS_DATA[0]=~PADRD[3];
			PS_DATA[1]=~PADRD[4];
			for(i=2;i<6;i++)
				PS_DATA[i] = 0x00;
			flag = PS_Set_AN();
		}
	}
	else
	{
		for(i=0;i<2;i++)
			PS_DATA[i] = 0;
		for(i=2;i<6;i++)
			PS_DATA[i] = 0;
	}
}

char getPAD(BYTE num){
	if(num <= PAD_AN_LY && num>= 0)
		return PS_DATA[num];
	else
		return 0;
}
//encoder**********************************************************//
long enc_L,enc_R;

const signed char enctbl[16] = {
  00, //* 00 -> 00 
  +1, //* 00 -> 01 
  -1, //* 00 -> 10 
  00, //* 00 -> 11 
  -1, //* 01 -> 00 
  00, //* 01 -> 01 
  00, //* 01 -> 10 
  +1, //* 01 -> 11 
  +1, //* 10 -> 00 
  00, //* 10 -> 01 
  00, //* 10 -> 10 
  -1, //* 10 -> 11 
  00, //* 11 -> 00 
  -1, //* 11 -> 01 
  +1, //* 11 -> 10 
  00, //* 11 -> 11 
};

void InitEncoder(){
	//encoder
	IEGR1.BIT.IEG3 = 1;	
	IEGR1.BIT.IEG2 = 1;	
	IEGR1.BIT.IEG1 = 1;	
	IEGR1.BIT.IEG0 = 1;		
	IENR1.BYTE |= 0x0F;

	IWPR.BYTE = 0x00;
	IEGR2.BIT.WPEG0 = 0;
	IEGR2.BIT.WPEG1 = 0;
	IEGR2.BIT.WPEG2 = 0;
	IEGR2.BIT.WPEG3 = 0;
	IENR1.BIT.IENWP = 1;	
	
	ClearEncoder();
}

void intencoder(){

  static unsigned char L = 0;
  static unsigned char old_L = 0;
  static unsigned char R = 0;
  static unsigned char old_R = 0;
 
 	unsigned char temp1,temp2;
	temp1 = IWPR.BYTE;
	temp2 = IRR1.BYTE;

	L |= (temp1 & 0x03);
	R |= ((temp1 >>2 ) & 0x03);
	L &= ~(temp2 & 0x03);
	R &= ~((temp2 >> 2 ) & 0x03);
	
	enc_L += enctbl[(old_L<<2) | L];
	old_L = L;
	enc_R += enctbl[(old_R<<2) | R];
	old_R = R;
	
	IWPR.BYTE = 0x00;
	IRR1.BYTE = 0x00;
	
}
void ClearEncoder(){
	enc_L = 0;
	enc_R = 0;
}

void GetEncoder(long *L,long *R){
	*L = enc_L;
	*R = enc_R;
}
BYTE MAINCYCLE;
//other ***********************************************************//
void Init(BYTE MainCycle)
{
	MAINCYCLE = MainCycle;
	IENR1.BIT.IENWP = 0;
		
// P10:(ext)MTRout
// P11:(ext)
// P12:(ext)MTRout
// P14:(ENC1A)
// P15:(ENC1B)
// P16:(ENC2A)
// P17:(ENC2B)
	IO.PMR1.BYTE=0xF0;
	IO.PCR1=0x05;
	IO.PDR1.BYTE=0x00;
	
	IO.PUCR1.BYTE=0x00;
	
// P20:PSPAD-CMD
// P21:PROG-USB
// P22:PROG-USB
// P23:PSPAD-SEL
// P24:PSPAD-CLK

	IO.PCR2=0xFF;
	IO.PDR2.BIT.B3 = 1;
	IO.PDR2.BIT.B4 = 1;
	IO.PDR2.BIT.B0 = 1;

// P30:Motor Dout
// P31:Motor Dout
// P32:Motor Dout
// P33:Motor Dout
// P34:(Motor Dout)
// P35:(Motor Dout)
// P36:(Motor Dout)
// P37:(Motor Dout)
	IO.PCR3=0xFF;
	IO.PDR3.BYTE=0x00;

// P50:(ENC1A)
// P51:(ENC1B)
// P52:(ENC2A)
// P53:(ENC2B)
// P54:(ext)MTRout
// P55:(ext)MTRout
// P56:(IXBUS)
// P57:(IXBUS)
	IO.PMR5.BYTE= 0x0F;
	IO.PCR5=0x30;
	
	//プルアップ
	IO.PUCR5.BYTE=0x00;
	


// P60:LED
// P61:M1PWM
// P62:M2PWM
// P63:(M3PWM)
// P64:LED:
// P65:(M4PWM)
// P66:(servo PWM)
// P67:(servo PWM)
	//motor PWM & SV PWM
	IO.PCR6=0xFF;
	IO.PDR6.BYTE=0x00;
	
// P70:(ext)
// P71:(IXBUS)
// P72:(IXBUS)
// P74:PUSH-SW
// P75:PSPAD-DAT
// P76:buzzer
	IO.PCR7=0xC0;	
	IO.PDR7.BIT.B6=0;
	
// P85:(E8)
// P86:(E8)
// P87:(E8)
	IO.PCR8 = 0xFF;
	IO.PDR8.BYTE = 0x00;


// PB0:AN0
// PB1:AN1
// PB2:AN2
// PB3:AN3
// PB4:(AN4)
// PB5:(AN5)
// PB6:(AN6)
// PB7:VBATT/2
	
	//WD->off
	WDT.TCSRWD.BYTE=0x92;	
	WDT.TCSRWD.BYTE=0x92;
	
	WDT.TCSRWD.BIT.B4WI = 0;
	WDT.TCSRWD.BIT.TCSRWE=1;

	WDT.TCSRWD.BIT.B2WI=0;
	WDT.TCSRWD.BIT.WDON=0;
	
	WDT.TMWD.BYTE=0xFF;
	WDT.TCSRWD.BIT.B6WI = 1;
	WDT.TCSRWD.BIT.TCWE = 1;
	WDT.TCWD=0x00;
	
	//TB1 main
	TB1.TMB1.BYTE=0xF9;		//オートリロード、φ/2048
	TB1.TCB1 = (BYTE)(256.0-((12000000.0/2048.0)/(double)MAINCYCLE)); //(256-5760/cycle)
	
	InitMtrPwm();
	InitAD();
}

BYTE getMainCycle(){
	return MAINCYCLE;
}

BYTE getSW()		//スイッチ読み込み
{
	BYTE x=0;
	if(IO.PDR7.BIT.B4 == 0)
		x+=1;
	return x;
}

//b0 LED1 P60,b1 LED2 P64
void LED(BYTE LedOn){	
	IO.PDR6.BIT.B4 = ~LedOn&0x01;
	IO.PDR6.BIT.B0 = (~LedOn>>1)&0x01;
}

void Wait(int msec)
{
	//0.000170666667　
	double waittime,waitcnt = 0.0;
	waittime = 1000.0/(double)MAINCYCLE;
	(BYTE)(((12000000.0/2048.0)/(double)MAINCYCLE));
	do{
		Sync();
		waitcnt += waittime;
	}while(waitcnt < (double)msec);
}

UINT Sync()
{
	UINT aa = 0;
	WDT.TCWD=0x00;
	
	while(IRR2.BIT.IRRTB1!=1)
		aa++;
	IRR2.BIT.IRRTB1=0;
	return aa;
}

