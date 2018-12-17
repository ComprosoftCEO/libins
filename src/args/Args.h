// Insanity Standard Library
//	Created by Bryan McClain (2018 - 2019)
//
//	Args.h - Standard functions for arguments
//
#ifndef ARGS_HEADER
#define ARGS_HEADER

#include <Insanity-Dev.h>


typedef struct {
	int index;
	int len;
} ArgData_t;



//Public functions
bool Argc(pInsanity_t insanity);
bool Argv(pInsanity_t insanity);
bool ArgvReset(pInsanity_t insanity);


//Private functions
ArgData_t* init_data(int argc, char** argv);


#endif
