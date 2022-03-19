/**
	@file database.h
	@author Alex Zettlemoyer
*/
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Database *makeDataBase();

void freeDataBase(Database *database);