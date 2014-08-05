/*
************************************************************************
�yFile Name�zPWM�o��
�yDescription�z
�yRevision History�z
   REV.00 2014-08-03  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * �C���N���[�h
 */
#include "HALIn.h"
#include "36064s.h"
/*
 * �萔��`
 */

/*
 * �O���֐��錾
 */

/*
 * �����֐��錾
 */

/*
 * �O���[�o���ϐ��錾
 */


#if ( HAL_HW_SWITCH == HAL_HW_H836064S )
/******************************************************************************
�y���́zPWM������
�y�ē��z�񃊃G���g�����g
�y���́z�Ȃ�
�y�o�́z�Ȃ�
�y�ߒl�z�Ȃ�
�y�����zTimerZ���W�X�^��PWM����p�Ƃ��Ă̏�����
        �ړI�F�����ݒ��10000�N���b�N�ɐݒ肷��
******************************************************************************/
void PWM_Init( void )
{
	TZ.TSTR.BIT.STR0=0;	// �`���l��0:�^�C�}��~
	TZ.TSTR.BIT.STR1=0;	// �`���l��1:�^�C�}��~
	
	TZ0.TCR.BYTE =	0x20;	// �`���l��0:GRA�ŃN���A(001)�A�����G�b�W(00)�A�ӂŃJ�E���g(000)
	TZ1.TCR.BYTE =	0x20;	// �`���l��1:GRA�ŃN���A(001)�A�����G�b�W(00)�A�ӂŃJ�E���g(000)
	
	TZ.TPMR.BYTE =	0xFF;	// �S����FTIO��PWM���[�h�ɂ���
		
	TZ.TOCR.BYTE =	0x00;	// TZ�F�S�Ă�FTIO�̏����o�͂�0
		
	TZ0.POCR.BYTE = 0x00;	// �`���l��0:�S�Ă�FTIO�̏o�̓��x���̓��[�A�N�e�B�u
	TZ1.POCR.BYTE = 0x00;	// �`���l��1:�S�Ă�FTIO�̏o�̓��x���̓��[�A�N�e�B�u
	
	TZ.TOER.BYTE =	0x11;	// FTIOB�AFTIOC�AFTIOD�[�q�̏o�͋���(FTIOA�͕s����)
		
	TZ.TMDR.BYTE =	0x00;	// TCNT0�A1�͔񓯊�����A���̑���GB���W�X�^�ʏ퓮��
	TZ.TFCR.BYTE =	0x00;	// �ʏ�
	
	TZ0.TSR.BYTE =	0x00;	// �G���[�t���O�N���A
	TZ1.TSR.BYTE =	0x00;	// �G���[�t���O�N���A

	TZ0.TCNT=0;	// �^�C�}�J�E���^�N���A
	TZ1.TCNT=0;	// �^�C�}�J�E���^�N���A

	TZ0.GRA=10000;	// �`���l��0�̎����ݒ�
	TZ1.GRA=10000;	// �`���l��1�̎����ݒ�
	
	TZ0.GRB = 0;	// �f���[�e�B��(VS-WRC003LV�ł̓��[�^�[1)
	TZ0.GRC = 0;	// �f���[�e�B��(VS-WRC003LV�ł̓��[�^�[2)
	TZ0.GRD = 0;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	TZ1.GRB = 0;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	TZ1.GRC = 0;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	TZ1.GRD = 0;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
}

/******************************************************************************
�y���́zPWM�o�̓f���[�e�B��ݒ�
�y�ē��z�񃊃G���g�����g
�y���́zTZ0���W�X�^ GRB�`GRD
        TZ1���W�X�^ GRB�`GRB
�y�o�́z�Ȃ�
�y�ߒl�z�Ȃ�
�y�����zPWM�o�͂̃f���[�e�B���ݒ肵�A�^�C�}���~�܂��Ă�����X�^�[�g������
        VS-WRC003LV�ł�TZ0��GRB�AGRC�̂ݎg�p���邽�߁A���̑��̃��W�X�^�ł�0�̐ݒ�𐄏�
******************************************************************************/
void HAL_PWM_Duty( UH uhTz0Grb, UH uhTz0Grc, UH uhTz0Grd, 
                   UH uhTz1Grb, UH uhTz1Grc, UH uhTz1Grd)
{
	// �����ɏ]���f���[�e�B���ݒ�
	TZ0.GRB = uhTz0Grb;	// �f���[�e�B��(VS-WRC003LV�ł̓��[�^�[1)
	TZ0.GRC = uhTz0Grc;	// �f���[�e�B��(VS-WRC003LV�ł̓��[�^�[2)
	TZ0.GRD = uhTz0Grd;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	TZ1.GRB = uhTz1Grb;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	TZ1.GRC = uhTz1Grc;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	TZ1.GRD = uhTz1Grd;	// �f���[�e�B��(VS-WRC003LV�ł͎g�p���Ȃ�)
	//TZ���~�܂��Ă�����X�^�[�g
	if(TZ.TSTR.BIT.STR0!=1){
		TZ.TSTR.BIT.STR0=1;		//�J�E���g�X�^�[�g
	}
	if(TZ.TSTR.BIT.STR1!=1){
		TZ.TSTR.BIT.STR1=1;		//�J�E���g�X�^�[�g
	}
}
#endif
