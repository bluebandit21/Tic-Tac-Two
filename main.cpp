#include "Board.h"
#include <iostream>
using namespace std;

int main(){
	Board board1(3,3);
	unsigned char vec1[3]={0,1,2};
	cout << "@GET/SET checks" << endl;
	cout << (int) board1.safeGetPosition(vec1) << endl;
	cout << (int) board1.safeGetPosition(vec1,false) << endl;
	board1.safeSetPosition(vec1,1);
	cout << (int) board1.safeGetPosition(vec1) << endl;
	cout << (int) board1.safeGetPosition(vec1,true) << endl;
	cout << "Expected output: 0,0,1,3" << endl;
	board1.print3D();
	cout << "@CHECK_ROW check" << endl;
	vec1[2]=1;
	board1.safeSetPosition(vec1,1);
	char offset1[3]={0,0,1};
	vec1[2]=0;
	board1.print3D();
	cout << board1.checkRow(vec1,offset1) << endl;
	board1.safeSetPosition(vec1,1);
	board1.print3D();
	cout << board1.checkRow(vec1,offset1) << endl;
	cout << "Expected output: 1,0"  << endl;
	return 0;
}
