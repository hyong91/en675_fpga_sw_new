#include "dev.h"

WORD Checksum16(BYTE *apbDst, UINT anNum)
{
	CHKSUM_ADR = (intptr_t)apbDst;
	CHKSUM_LEN = anNum;
	CHKSUM_GO = 1;
	while (CHKSUM_GO);
	return (WORD)CHKSUM_DAT;
}
