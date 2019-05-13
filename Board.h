/*
 * Board.h
 *
 *  Created on: May 10, 2019
 *      Author: plotner
 */

#ifndef BOARD_H_
#define BOARD_H_
class Board{
public:
	unsigned short dimension;
	unsigned short row_size;
	unsigned int board_byte_count;
	unsigned int* dimension_cache;
	unsigned char* board;
	Board(unsigned short _dimension, unsigned short _row_size){ // @suppress("Class members should be properly initialized")
		row_size=_row_size;
		dimension=_dimension;
		unsigned int bit_count=1;
		for(short i=0;i<dimension;i++){
			i*=row_size; //m_n game has n^m positions.
		}
		bit_count*=2; //We want to have two bits of data for each pos. (State and value)
		board_byte_count=(bit_count+3) / 4; //Integer division is our friend.
		board = new unsigned char[board_byte_count];
		for(int i=0;i<board_byte_count;i++){
			board[i]=0; //Initialize everything to 0.
		}
		dimension_cache=new unsigned int[row_size];
		dimension_cache[0]=1;
		for(int i=1;i<row_size;i++){
			dimension_cache[i]=dimension_cache[i-1]*row_size;
		}
	}
	inline unsigned int get_bit_count(unsigned char* vector){
		//Assume vector has length dimension, values from 0 to row_size-1
		unsigned int bit_count=0;
		for(int i=0;i<dimension;i++){
			bit_count+=vector[i]*dimension_cache[i];//Construct offset values
		}
		bit_count = bit_count << 1; //Multiply by two.
		return bit_count;
	}
	inline unsigned char* vectorSum(unsigned char* vector1, unsigned char* vector2){
		unsigned char* vector3=new unsigned char[row_size];
		for(int i=0;i<row_size;i++){
			vector3[i]=vector1[i]+vector2[i];
		}
		return vector3;
	}
	inline unsigned char* vectorProd(char* vector1,unsigned char multer){
		unsigned char* vector2=new unsigned char[row_size];
		for(int i=0;i<row_size;i++){
			vector2[i]=vector1[i]*multer;
		}
		return vector2;
	}
	unsigned char getPosition(unsigned char* vector, bool getSetBit=false){
		//Returns 0b000000ab, where a is set bit, b is value bit.
		//Assume vector has length dimension, values from 0 to row_size-1
		unsigned int bit_count=get_bit_count(vector);
		unsigned int byte_count=bit_count >> 2; //Truncate/integer divide by 4
		unsigned char byte_offset=bit_count & 0b11; //Get byte_count % 4
		if(getSetBit) return ((board[byte_count] & (0b11 << byte_offset))>>byte_offset); //Evil bitwise magic.
		else return ((board[byte_count] & (0b1 << byte_offset))>>byte_offset);
	}
	void setPosition(unsigned char* vector, unsigned char value){
		//Value in the form of 0b0000000b, where b is value bit.
		unsigned int bit_count=get_bit_count(vector);
		unsigned int byte_count=bit_count >> 2;//Truncate/integer divide by 4
		unsigned char byte_offset=bit_count & 0b11; //Get byte_count % 4
		board[byte_count]=((board[byte_count]>>(byte_offset+0b10))<<(byte_offset+0b10))+((0b10+value)<<byte_offset)+((board[byte_count]<<(0b100-byte_count))>>(0b100-byte_count));
		//Horrifying byte shifting above to set the two bits at the byte_offset;
	}
	bool checkRow(unsigned char* vector,char* offsets);
	void print3D();
	void safeSetPosition(unsigned char* vector, unsigned char value);
	unsigned char safeGetPosition(unsigned char* vector, bool getSetBit=false);
};



#endif /* BOARD_H_ */
