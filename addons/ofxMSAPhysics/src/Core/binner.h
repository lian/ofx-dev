
#include <stdio.h>

#ifndef 	BINNER_H
#define 	BINNER_H

void			setupBins(int x_size, int y_size, int z_size, int nDivisionsX, int nDivisionsY, int nDivisionsZ);	// do this once! 
void 			computeBinPosition(int xpos, int ypos, int zpos, unsigned int *bitFlagX, unsigned int *bitFlagY, unsigned int *bitFlagZ);

//------------------------------------------------------


#endif