#ifndef _PF_IN_H_
#define _PF_IN_H_
/*
************************************************************************
�yFile Name�z�v���b�g�t�H�[���@�\�w�b�_�i�����p�j
�yDescription�z
�yRevision History�z
   REV.00 2014-05-05  BY R.ISHIKAWA
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2014 IPL CORPORATION All Rights Reserved
************************************************************************
*/

/*
 * �C���N���[�h
 */

/*
 * �萔��`
 */

#define TASK_NUM_MAX (2)
#define TASK_LED_ON (0)
#define TASK_LED_OFF (1)

/*
 * �\���̐錾
 */
 
struct STR_TaskData{
	void (*pf)();
	UB request;
}
 
/*
 * �O���֐��錾
 */

#endif /* _PF_IN_H_ */
