
#include "stdafx.h"


#include "vsm.h"    // - заголовочный файл VSM API от Labcenter Electronics.
#include "PROMDEVICE.h" //-заголовочный файл для реализации класса нашей модели.

//---------------------------------------------------------------------------
#define model_key 0x00000000 // - код авторизации от Labcenter Electronics
//---------------------------------------------------------------------------

extern "C" IDSIMMODEL __declspec(dllexport) *createdsimmodel(CHAR *device, ILICENCESERVER *ils)
{
	if (ils->authorize(model_key))
	{
		return new PROMDEVICE; // - указатель на класс модели FFDEVICE
	}
	else
	{
		return NULL;
	}
}

extern "C" VOID __declspec(dllexport) deletedsimmodel(IDSIMMODEL *model)
{
	delete (PROMDEVICE *)model; // - указатель на IDSIMMODEL интерфейс, который был ранее
							  // - создан функцией createdsimmodel.
}
