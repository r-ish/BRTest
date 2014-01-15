#ifndef _HAL_H_
#define _HAL_H_
/*
************************************************************************
ÅyFile NameÅzHardware Abstraction Layer ã§í ÉwÉbÉ_Å[
ÅyDescriptionÅz
ÅyRevision HistoryÅz
   REV.00 2013-11-04  BY T.OOSAKI
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX
   REV.XX 20XX-XX-XX  BY X.XXXXXX

                      (C) 2013 IPL CORPORATION All Rights Reserved
************************************************************************
*/

#include "PF_Common.h"

// äÑÇËçûÇ›ã÷é~Ç∆ã÷é~èÛë‘Ç©ÇÁå≥èÛë‘Ç…ïúãA
extern UB   HAL_DisableIr( void );
extern void HAL_ReturnIr( UB ubCCR );

#endif /* _HAL_H_ */
