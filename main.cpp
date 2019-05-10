#include "Board.h"
#include <iostream>
using namespace std;

int main(){
	Board board1(2,2);
	unsigned char vec1[2];
	vec1[0]=0;
	vec1[1]=1;
	cout << (int) board1.getPosition(vec1) << endl;
	cout << (int) board1.getPosition(vec1,false) << endl;
	board1.setPosition(vec1,1);
	cout << (int) board1.getPosition(vec1) << endl;
	cout << (int) board1.getPosition(vec1,true) << endl;

	return 0;
}
