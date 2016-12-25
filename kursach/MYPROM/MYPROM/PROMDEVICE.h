//----- Заголовочный файл MTDEVICE.h ------------------------------------
#pragma once
#include "vsm.h"

class PROMDEVICE : public IDSIMMODEL
{
public:
	INT isdigital(CHAR *pinname);
	VOID setup(IINSTANCE *inst, IDSIMCKT *dsim);
	VOID runctrl(RUNMODES mode);
	VOID actuate(REALTIME time, ACTIVESTATE newstate);
	BOOL indicate(REALTIME time, ACTIVEDATA *data);
	VOID simulate(ABSTIME time, DSIMMODES mode);
	VOID callback(ABSTIME time, EVENTID eventid);
private:
	const UINT DELAY__ = 80000;
	IINSTANCE *inst;
	IDSIMCKT *ckt;
	
	IDSIMPIN *Pin1; //vcc
	IDSIMPIN *Pin2; //reset
	IDSIMPIN *Pin3; //clock
	IDSIMPIN *Pin4; //not conect
	IDSIMPIN *Pin5; //ground

	IDSIMPIN *Pin6; //io3 input
	IDSIMPIN *Pin7; //io1	
	IDSIMPIN *Pin8; //io2 output
	

	UINT TO_UINT(IDSIMPIN * p32, IDSIMPIN * p16, IDSIMPIN * p8, IDSIMPIN *p4, IDSIMPIN *p2, IDSIMPIN *p1);
	STATE TO_STATE(UINT value);
};
