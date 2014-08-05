/*
************************************************************************
�yFile Name�z���C���֐�
�yDescription�z
�yRevision History�z
   REV.00 2013-11-04  BY T.OOSAKI
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

#if ( HAL_HW_SWITCH == HAL_HW_H836064S )

/*
 * �萔��`
 */

/*
 * �O���֐��錾
 */
extern void TIMER_Init( void );
extern void IO_Init( void );
extern void PWM_Init( void );
extern void WDT_Init( void );
extern void PF_Init( void );

/*
 * �����֐��錾
 */
extern void main(void);

/*
 * �O���[�o���ϐ��錾
 */

/******************************************************************************
�y���́z���C���֐�
�y�ē��z�񃊃G���g�����g
�y���́z�Ȃ�
�y�o�́z�Ȃ�
�y�ߒl�z�Ȃ�
�y�����z���C���֐�
******************************************************************************/
const UB a = 1; // �����J�̌x���}���̂��߈ꎞ�I�ɑ}���FL1100 (W) Cannot find "C" specified in option "start"
void main( void )
{
	// �^�C�}�[������
	TIMER_Init();
	// IO�|�[�g������
	IO_Init();
	// PWM���䏉����
	PWM_Init();
	// �v���b�g�t�H�[��������
	PF_Init();
		// �E�H�b�`�h�b�O�^�C�}��~
	WDT_Init();
	// �S���荞�݋���
	IENR1.BIT.IENDT = 1;

	/* �^�p���ʑ��Ń^�X�N�X�P�W���[���֐�����`����Ă���ꍇ�R�[�� */
	if (fpHAL_TASKMAIN_1MS != PF_NULL)
	{
		fpHAL_TASKMAIN_1MS();
	}
}
#endif
