#include "mainAlg.h"
#include "platform_Types.h"

static uint32 pVal = 0;
static uint32 pThreshold = 20;
void (*MAIN_ALG_state) ();

void readPressureValue(int pValue)
{
	pVal = pValue;
	DPRINTF("mainAlg:...............pressure value=%d.............../n",pVal);
}

STATE_define(MAIN_ALG_highPressureDetect)
{
	mainAlg_state_id = mainAlg_highPressireDetect;

	if(pVal >= pThreshold)
		highPressureDetected();
	DPRINTF("MAIN_ALG_highPressureDetect.............../n",pVal);
	MAIN_ALG_state = STATE(MAIN_ALG_highPressureDetect);
}
