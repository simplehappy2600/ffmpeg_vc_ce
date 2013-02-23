// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "test.h"

static const char* const channel_names[]={
	"FL", "FR", "FC", "LFE", "BL",  "BR",  "FLC", "FRC",
	"BC", "SL", "SR", "TC",  "TFL", "TFC", "TFR", "TBL",
	"TBC", "TBR",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	/*[29] = */"DL",
	/*[30] = */"DR"
};

int _tmain(int argc, _TCHAR* argv[])
{

	printf("%s", channel_names[29]);

exit:
	return 0;
}

