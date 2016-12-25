//------- MTDEVICE.CPP ---------------------------------------------------------------
#include "stdafx.h"
#include "PROMDEVICE.h" //- заголовочный файл для реализации класса нашей модели.
//------------------------------------------------------------------------------------
#define KEY 142

void delayMicroSeconds(float microseconds)
{
	__int64 timeEllapsed;
	__int64 timeStart;
	__int64 timeDelta;

	QueryPerformanceFrequency((LARGE_INTEGER*)(&timeDelta));

	__int64 timeToWait = (double)timeDelta * (double)microseconds / 1000000.0f;

	QueryPerformanceCounter((LARGE_INTEGER*)(&timeStart));

	timeEllapsed = timeStart;

	while ((timeEllapsed - timeStart) < timeToWait)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)(&timeEllapsed));
	}
}
//--- DEVICE::isdigital --------------------------------------------------------------
INT PROMDEVICE::isdigital(CHAR *pinname)
{
	return 1;
}

//--- DEVICE::setup ------------------------------------------------------------------
VOID PROMDEVICE::setup(IINSTANCE *instance, IDSIMCKT *dsimckt)
{
	inst = instance;
	ckt = dsimckt;

	Pin1 = inst->getdsimpin("VCC", false);
	Pin2 = inst->getdsimpin("RST", false);
	Pin3 = inst->getdsimpin("CLK", false);
	Pin4 = inst->getdsimpin("NC", true);
	Pin5 = inst->getdsimpin("GND", false);
	Pin6 = inst->getdsimpin("IO3", true);
	Pin7 = inst->getdsimpin("IO1", true);
	Pin8 = inst->getdsimpin("IO2", true);
	


	

	//Pin8->setstate(TO_STATE(ROM[0][0]));
	//Pin9->setstate(TO_STATE(ROM[0][1]));
	//Pin10->setstate(TO_STATE(ROM[0][2]));
	//Pin11->setstate(TO_STATE(ROM[0][3]));
	//Pin12->setstate(TO_STATE(ROM[0][4]));

}

//---- DEVICE::runctrl ------------------------------------------------------------------
VOID PROMDEVICE::runctrl(RUNMODES mode)
{

}

//---- DEVICE::actuate ------------------------------------------------------------------
VOID PROMDEVICE::actuate(REALTIME time, ACTIVESTATE newstate)
{
	//---- анализируется состояние (ACTIVESTATE newstate)
}

//---- DEVICE::indicate ------------------------------------------------------------------
BOOL PROMDEVICE::indicate(REALTIME time, ACTIVEDATA *data)
{
	return FALSE;
}

//---- DEVICE::simulate ------------------------------------------------------------------
VOID PROMDEVICE::simulate(ABSTIME time, DSIMMODES mode)
{
	

	char mes[66];
	char temp;
	if (ishigh(Pin4->istate())) {  // чтение данных 9600 бит/с = 1 бит каждые 105 мкс		
		for (int i = 0; i < 66; ++i)
		{
			temp = 0;
			for (int j = 0; j < 8; ++j)
			{
				temp <<= 1;
				if (ishigh(Pin6->istate()))
					temp |= 1;	
				delayMicroSeconds(105);
			}
			mes[i] = temp ^ KEY;
		}


		for (int i = 0; i < 66; ++i) // отправка зашифрованных данных
		{
			temp = mes[i];
			for (int j = 0; j < 8; ++j)
			{
				Pin8->setstate(TO_STATE(temp & 1));					
				delayMicroSeconds(105);
				temp >>= 1;
			}			 
		}


	/*	
		Pin9->setstate(time, DELAY__, TO_STATE(ROM[ADDR][1]));
		Pin10->setstate(time, DELAY__, TO_STATE(ROM[ADDR][2]));
		Pin11->setstate(time, DELAY__, TO_STATE(ROM[ADDR][3]));
		Pin12->setstate(time, DELAY__, TO_STATE(ROM[ADDR][4]));
		Pin13->setstate(time, DELAY__, TO_STATE(ROM[ADDR][5]));*/

	}
}

//---- DEVICE::callback ------------------------------------------------------------------
VOID PROMDEVICE::callback(ABSTIME time, EVENTID eventid)
{

}

UINT PROMDEVICE::TO_UINT(IDSIMPIN * p32, IDSIMPIN * p16, IDSIMPIN * p8, IDSIMPIN * p4, IDSIMPIN * p2, IDSIMPIN * p1)
{
	UINT res = 0U;
	if (ishigh(p32->istate())) {
		res += 32U;
	}
	if (ishigh(p16->istate())) {
		res += 16U;
	}
	if (ishigh(p8->istate())) {
		res += 8U;
	}
	if (ishigh(p4->istate())) {
		res += 4U;
	}
	if (ishigh(p2->istate())) {
		res += 2U;
	}
	if (ishigh(p1->istate())) {
		res += 1U;
	}
	return res;
}

STATE PROMDEVICE::TO_STATE(UINT value)
{
	return (value > 0) ? STATE::SHI : STATE::SLO;
}


