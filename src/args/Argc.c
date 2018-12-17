#include "Insanity-Dev.h"
#include <stdlib.h>
#include <string.h>


static bool Argc(pInsanity_t insanity);
static bool Argv(pInsanity_t insanity);
static bool ArgvReset(pInsanity_t insanity);

INSANITY_METHOD(Argc,Argc);
INSANITY_METHOD(Argv,Argv);
INSANITY_METHOD(ArgvReset,ArgvReset);


typedef struct {
	int index;
	int len;
} ArgData_t;




static ArgData_t* initData(int argc, char** argv) {
	ArgData_t* data = calloc(argc,sizeof(ArgData_t));
	for (int i = 0; i < argc; ++i) {
		data[i].len = strlen(argv[i]);
	}
}

//
// Get the number of terminal arguments
//
static bool Argc(pInsanity_t insanity) {
	insanity->acc = insanity->argc;
	return true;
}


//
// Get one char from the argument value (stored in the backup)
//
static bool Argv(pInsanity_t insanity) {

	//Get the stream data
	ArgData_t* data = (ArgData_t*) getData(insanity,"STDARGS");
	if (!data) {
		data = initData(insanity->argc,insanity->argv);
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


//
// Reset the location in the argument stream
//
static bool ArgvReset(pInsanity_t insanity) {

	//Get the stream data
	ArgData_t* data = (ArgData_t*) getData(insanity,"STDARGS");
	if (!data) {
		data = initData(insanity->argc,insanity->argv);
		setData(insanity,"STDARGS",data);
	}

	int toRead = insanity->acc;
	if ((toRead >= 0) && (toRead < insanity->argc)) {
		data[toRead].index  = 0;
	}

	return true;
}
