/*
************************************************************************
�yFile Name�z�r���[�g���[�o�[(VS-WRC003LV)�p
�@�@�@�@�@�@ �X�C�b�`���́�LED�\���֐�
�yDescription�z
�yRevision History�z
   REV.00 2014-09-06  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * �C���N���[�h
 */
#include "HAL.h"
#include "Application.h"
#include "PF_Common.h"

/*
 * �萔��`
 */

// LED��Ԃ̕ω��J�E���g��
// #define LED_CHANGE_CNT (50)
// �`���^�����O�h�~�����L��
// #define LED_CHATTERLING_CHK_FLG (1)

/*
 * �O���[�o���ϐ��錾
 */

/*
 * �O���֐��錾
 */

/******************************************************************************
�y���́z�X�C�b�`���LED���f�֐�
�y�ē��z�񃊃G���g�����g
�y���́z�Ȃ�
�y�o�́z�Ȃ�
�y�ߒl�z�Ȃ�
�y�����z�X�C�b�`�̏�Ԃ��擾���ALED�̏�Ԃɔ��f������
******************************************************************************/

void APP_Switch_To_LED()
{
	UB ubSwitch = 0x0;
	UB ubLED    = 0x0;

	// �O��̃X�C�b�`����
	static UB ubInputBefore = HAL_SWITCH_OFF;
	// �X�C�b�`���͂̓��l�p����
	static UH uhInputCnt = 0;
		
	// �X�C�b�`�̒l���擾
	ubSwitch = APP_Switch_Get();
	
	// �X�C�b�`���͂�ON�̏ꍇ
	if(ubSwitch == HAL_SWITCH_ON)
	{
		// ����̒l���LEDON
		APP_LED2_Set(HAL_LED_ON);
		// �O���ON�̏ꍇ
		if(ubInputBefore == HAL_SWITCH_ON)
		{
			// �J�E���g�A�b�v
			uhInputCnt++;
		}
		// �O��OFF�̏ꍇ
		else
		{
			// �O��l��ύX
			ubInputBefore = HAL_SWITCH_ON;
			// �J�E���g���Z�b�g
			uhInputCnt = 0;
		}
	}
	// �X�C�b�`���͂�OFF�̏ꍇ
	else
	{
		// ����̒l���LEDOFF
		APP_LED2_Set(HAL_LED_OFF);
		// �O���OFF�̏ꍇ
		if(ubInputBefore == HAL_SWITCH_OFF)
		{
			// �J�E���g�A�b�v
			uhInputCnt++;
		}
		// �O��ON�̏ꍇ
		else
		{
			// �O��l��ύX
			ubInputBefore = HAL_SWITCH_OFF;
			// �J�E���g���Z�b�g
			uhInputCnt = 0;
		}
	}
	
	// �J�E���g���K��񐔈ȏ�
	if(uhInputCnt >= 500)
	{
		// �I�[�o�[�t���[�΍�
		uhInputCnt = 500;
		
		// �O����͂ɍ��킹��LED��ԕύX
		if(ubInputBefore == HAL_SWITCH_ON)
		{
			// LED�̕\����ύX����
			APP_LED1_Set(HAL_LED_ON);
			//APP_LED2_Set(ubLED);
		}
		else
		{
			// LED�̕\����ύX����
			APP_LED1_Set(HAL_LED_OFF);
			//APP_LED2_Set(ubLED);
		}
	}
	
	/*
	// �X�C�b�`�̒l����LED�̕\����Ԃ�����
	if(ubSwitch == HAL_SWITCH_ON)
	{
		ubLED = HAL_LED_ON;
	}
	else
	{
		ubLED = HAL_LED_OFF;
	}
	// LED�̕\����ύX����
	APP_LED1_Set(ubLED);
	APP_LED2_Set(ubLED);
	*/
}


/*
 * �����֐��錾
 */

