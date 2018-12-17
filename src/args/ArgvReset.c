// Insanity Standard Library
//	Created by Bryan McClain (2018 - 2019)
//
//	ArgsReset.c - Reset the location in the argument stream
//
#include "Args.h"

bool ArgvReset(pInsanity_t insanity) {

	//Get the stream data
	ArgData_t* data = (ArgData_t*) getData(insanity,"STDARGS");
	if (!data) {
		data = init_data(insanity->argc,insanity->argv);
		setData(insanity,"STDARGS",data);
	}

	int toRead = insanity->acc;
	if ((toRead >= 0) && (toRead < insanity->argc)) {
		data[toRead].index  = 0;
	}

	return true;
}
