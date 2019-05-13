#include "Board.h"
#include <assert.h>
#include <iostream>
bool Board::checkRow(unsigned char* origin, char* offsets){
//Origin determines starting pos, offsets determines the offset values.
//The nth offset can only be 1 if the nth pos is 0, and -1 if the pos if row_size.
//The offset vector can not be entirely 0.
//This should return true if there is no solution.

//Sanity checking
bool non_zero_flag=0;
for(unsigned char i=0;i<row_size;i++){
	if(offsets[i]!=0)	non_zero_flag=true;
	assert(offsets[i]==0 || offsets[i]==1 || offsets[i]==-1); //Otherwise some funky stuff is happening.
	assert(offsets[i]==0 || (offsets[i]==1 && origin[i]==0) || (offsets[i]==-1 && origin[i]==row_size));
	//Ensure that non-zero offsets happen at appropriate places.
}
assert(non_zero_flag);
bool o_flag=0;
bool x_flag=0;
for(unsigned char i=0;i<row_size;i++){
	unsigned char* vector=vectorSum(origin,vectorProd(offsets,i));
	unsigned char val=getPosition(vector);
	if(val) x_flag=true;
	else o_flag=true;
	if(x_flag && o_flag) return true;
}
return false;
}
void Board::print3D(){
	std::cout << "--------------------" << std::endl;
	assert(dimension==3);
	for(int i=0;i<row_size;i++){
		for(int j=0;j<row_size;j++){
			for(int k=0;k<row_size;k++){
				unsigned char vector[3]={i,j,k};
				std::cout << (int) getPosition(vector) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
}
unsigned char Board::safeGetPosition(unsigned char* vector, bool getSetBit){
	//Safe getPosition. (It's impossible to access non-existent position)
	for(int i=0;i<dimension;i++){
		assert(vector[i]<row_size && vector[i]>=0);
	}
	return getPosition(vector,getSetBit);
}
void Board::safeSetPosition(unsigned char* vector, unsigned char value){
	for(int i=0;i<dimension;i++){
		assert(vector[i]<row_size && vector[i]>=0);
	}
	assert(value==0 || value==1);
	setPosition(vector,value);
}
