// Insanity Standard Library
//	Created by Bryan McClain (2018 - 2019)
//
//	initData.c - Initialize all argument data
//
#include "Args.h"
#include <stdlib.h>
#include <string.h>


ArgData_t* init_data(int argc, char** argv) {
	ArgData_t* data = calloc(argc,sizeof(ArgData_t));
	for (int i = 0; i < argc; ++i) {
		data[i].len = strlen(argv[i]);
	}

	return data;
}
