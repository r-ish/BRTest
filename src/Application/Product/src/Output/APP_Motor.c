/*
************************************************************************
�yFile Name�z�r���[�g���[�o�[(VS-WRC003LV)�p
             ���[�^�[����֐�(�A�v���P�[�V������)
�yDescription�z
�yRevision History�z
   REV.00 2014-08-02  BY R.ISHIKAWA
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
#include "PF_Common.h"

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

/******************************************************************************
�y���́z���[�^�[�o�͓��e�ύX
�y�ē��z�񃊃G���g�����g
�y���́z���[�^�[1�A2�̏o�͕���
        ���[�^�[1�A2�̃f���[�e�B��(0.00%�`100.00%)
�y�o�́z�Ȃ�
�y�ߒl�z�Ȃ�
�y�����z���[�^�[�̏o�͓��e�������̒l�ɕύX����
******************************************************************************/
void APP_Motor_Set(UB ubMotor1Dir,  UB ubMotor2Dir, 
                   UH uhMotor1Duty, UH uhMotor2Duty)
{
	// �f���[�e�B��̐ݒ�
	HAL_PWM_Duty(uhMotor1Duty, uhMotor2Duty, 0, 0, 0, 0);
	// ���[�^�[�̏o�͕����ݒ�
	HAL_Motor_DirSet(ubMotor1Dir, ubMotor2Dir);

}

