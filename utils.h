#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include "defs.h"
#include "Data.h"

using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);
int leInteiro(int min, int max);

unsigned int leUnsignedInt();
int leInt();

float leFloat();

char leCharYorN();

void clientesHeader();

