#include "binner.h"



//------------------------------------------------------
int 			nBinDivisionsX; // must be an odd number
int 			nBinDivisionsY; // must be an odd number
int				nBinDivisionsZ;

float 			binDivisionXSize;
float			binDivisionXSizeInv;
float 			binDivisionSubBoundaryMinX, binDivisionSubBoundaryMaxX;
float 			binDivisionYSize;
float 			binDivisionYSizeInv;
float 			binDivisionSubBoundaryMinY, binDivisionSubBoundaryMaxY;
float 			binDivisionZSize;
float 			binDivisionZSizeInv;
float 			binDivisionSubBoundaryMinZ, binDivisionSubBoundaryMaxZ;

void computeBinPosition(int xpos, int ypos, int zpos, unsigned int *bitFlagX, unsigned int *bitFlagY, unsigned int *bitFlagZ){
	int posBin1, posBin2;
	*bitFlagX = 0x00000000;
	*bitFlagY = 0x00000000;
	*bitFlagZ = 0x00000000;
	
	
	if (xpos < 0) xpos = 0;
	if (ypos < 0) ypos = 0;
	if (zpos < 0) zpos = 0;
	if (xpos > binDivisionXSize*nBinDivisionsX) xpos = binDivisionXSize*nBinDivisionsX;
	if (ypos > binDivisionYSize*nBinDivisionsY) ypos = binDivisionYSize*nBinDivisionsY;
	if (zpos > binDivisionZSize*nBinDivisionsZ) zpos = binDivisionZSize*nBinDivisionsZ;
	
	// compute for X
	posBin1 = (int)((float)xpos * binDivisionXSizeInv);
	*bitFlagX |= (0x00000001 << (posBin1 * 2));
	
	if (xpos > binDivisionSubBoundaryMinX && xpos < binDivisionSubBoundaryMaxX){
		posBin2 = (int)((float)(xpos - binDivisionSubBoundaryMinX) * binDivisionXSizeInv);
		*bitFlagX |=  (0x00000001 << (1 + posBin2 * 2));
	}
	
	// compute for Y
	posBin1 = (int)((float)ypos * binDivisionYSizeInv);
	*bitFlagY |= (0x00000001 << ( posBin1 * 2));
	
	if (ypos > binDivisionSubBoundaryMinY && ypos < binDivisionSubBoundaryMaxY){
		posBin2 = (int)((float)(ypos - binDivisionSubBoundaryMinY) * binDivisionYSizeInv);
		*bitFlagY |=  (0x00000001 << (1 + posBin2 * 2));
	}
	
	// compute for Z
	posBin1 = (int)((float)zpos * binDivisionZSizeInv);
	*bitFlagZ |= (0x00000001 << ( posBin1 * 2));
	
	if (zpos > binDivisionSubBoundaryMinZ && zpos < binDivisionSubBoundaryMaxZ){
		posBin2 = (int)((float)(zpos - binDivisionSubBoundaryMinZ) * binDivisionZSizeInv);
		*bitFlagZ |=  (0x00000001 << (1 + posBin2 * 2));
	}
}

//-------------------------------------
void setupBins(int x_size, int y_size, int z_size, int nDivisionsX, int nDivisionsY, int nDivisionsZ){

	nBinDivisionsX = nDivisionsX;
	nBinDivisionsY = nDivisionsY;
	nBinDivisionsZ = nDivisionsZ; 

	binDivisionXSize = x_size / (float)nBinDivisionsX;
	binDivisionYSize = y_size / (float)nBinDivisionsY;
	binDivisionZSize = z_size / (float)nBinDivisionsZ;
	
	binDivisionXSizeInv = 1.0f/binDivisionXSize;
	binDivisionYSizeInv = 1.0f/binDivisionYSize;
	binDivisionZSizeInv = 1.0f/binDivisionZSize;

	binDivisionSubBoundaryMinX = binDivisionXSize / 2.0f;
	binDivisionSubBoundaryMaxX = x_size - binDivisionXSize / 2.0f;

	binDivisionSubBoundaryMinY = binDivisionYSize / 2.0f;
	binDivisionSubBoundaryMaxY = y_size - binDivisionYSize / 2.0f;
	
	binDivisionSubBoundaryMinZ = binDivisionZSize / 2.0f;
	binDivisionSubBoundaryMaxZ = z_size - binDivisionZSize / 2.0f;

}

//-------------------------------------
