// Insanity Standard Library
//	Created by Bryan McClain (2018 - 2019)
//
//	Argv.c - Get one char from the argument value, store in the backup
//
#include "Args.h"


bool Argv(pInsanity_t insanity) {

	//Get the stream data
	ArgData_t* data = (ArgData_t*) getData(insanity,"STDARGS");
	if (!data) {
		data = init_data(insanity->argc,insanity->argv);
		setData(insanity,"STDARGS",data);
	}

	int toRead = insanity->acc;
	if (toRead >= insanity->argc || toRead < 0) {
		insanity->bak = -1;
	} else {
		if (data[toRead].index < data[toRead].len) {
			insanity->bak = insanity->argv[toRead][data[toRead].index++];
		} else {
			insanity->bak = -1;
		}
	}

	return true;
}
