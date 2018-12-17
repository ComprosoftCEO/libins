// Insanity Standard Library
//	Created by Bryan McClain (2018 - 2019)
//
//	Argc.c - Get the number of terminal arguments, store in ACC
//
#include "Args.h"


bool Argc(pInsanity_t insanity) {
	insanity->acc = insanity->argc;
	return true;
}
