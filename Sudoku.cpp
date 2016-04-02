#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include "Sudoku.h"
using namespace std;
//----------------------------------------
int Sudoku::Ans = 0;
int Sudoku::A = 0;
int Sudoku::cul = 0;
int Sudoku::map_tmp[81];

//----------------------------------------
Sudoku::Sudoku()
{
	for(int i=0; i<sudokuSize; i++)
	{
		map[i] = 0;
		count[i]=0;
		for(int j=0;j<Size;j++)
			tag[i][j] = 0;
	}
	Found = 0;
}
//----------------------------------------
Sudoku::Sudoku(vector<int> init_map, int A)
{
	cul++;
	for(int i=0; i<sudokuSize; i++)
		map[i] = init_map[i];
	//
	for(int i=0;i<sudokuSize;i++)
	{
		count[i]=0;
		for(int j=0;j<Size;j++)
			tag[i][j] = 0;
	}
	Found = 0;
	setAns(A);
	solve();
}
//----------------------------------------
void Sudoku::giveQuestion()//fun.1
{
	//ofstream out("SudokuBoard",ios::out);
	//if(!out){
	//	cerr<<"Failed opening"<<endl;
	//	exit(1);
	//}
	cout<<"0 6 7 0 0 4 3 2 0"<<endl
	    <<"1 0 0 2 0 0 9 0 0"<<endl
	    <<"2 4 0 0 0 0 8 1 7"<<endl
	    <<"0 0 0 0 0 3 0 0 0"<<endl
	    <<"3 0 0 0 0 0 5 0 1"<<endl
	    <<"8 0 2 9 5 0 4 7 0"<<endl
	    <<"7 0 6 0 4 0 1 3 9"<<endl
	    <<"0 3 9 0 0 0 0 8 4"<<endl
	    <<"0 8 1 0 6 9 7 0 2"<<endl;
}

//----------------------------------------
void Sudoku::readIn()//fun.2
{
	
	//int sudoku_in[sudokuSize];
	
	//ifstream in("SudokuBoard",ios::in);
	//if(!in){
	//	cerr<<"Failed opening"<<endl;
	//	exit(1);
	//}
	//for(int i=0;i<sudokuSize;i++)
	//{
	//	in>>sudoku_in[i];
	//}
	//for(int i=0;i<sudokuSize;i++)
	//{
	//	map[i] = sudoku_in[i];
	//}
	for(int i=0;i<sudokuSize;++i)
	{
		cin>>map[i];
	}
}
//----------------------------------------
void Sudoku::solve()//fun.3
{
	int DisNum_row, DisNum_column, DisNum_cell;
	int Blank_row, Blank_column, Blank_cell;
    int	BlankAddress_row, BlankAddress_column, BlankAddress_cell;
	
	if(checkZero() == true)
	{
		cout << "2"<<endl;
		exit(1);
	}
	else
	{
	if(isSolvable() == false)
	{
		cout << getAns() <<endl;
		exit(1);
	}
	else
	{
    for(int i=0;i<sudokuSize;i++)
	{
		if(map[i])
			Found++;
		else{
			for(int j=0;j<Size;j++)
			{
				DisNum_row = map[(i/Size)*Size+j];
				if(DisNum_row && !tag[i][DisNum_row-1])
				{
					count[i]++;
					tag[i][DisNum_row-1] = true;
				}
				DisNum_column = map[j*Size+i%Size];
				if(DisNum_column && !tag[i][DisNum_column-1])
				{
					count[i]++;
					tag[i][DisNum_column-1] = true;
				}
				DisNum_cell = map[((i/(Size*3))*3+j/3)*Size + ((i%Size)/3)*3+j%3];
				if(DisNum_cell && !tag[i][DisNum_cell-1])
				{
					count[i]++;
					tag[i][DisNum_cell-1] = true;
				}
			}
		}
	}
	
	for(int i=0;i<sudokuSize;i++)
	{
		if(!map[i] && count[i]==8)
		{
			count[i] = 0;
			Found++;
			for(int j=0;j<Size;j++)
			{
				if(!tag[i][j])
				{
					map[i] = j+1;
					for(int k=0;k<Size;k++)
					{
						Blank_row = map[(i/Size)*Size+k];
						BlankAddress_row = (i/Size)*Size+k;
						if(!Blank_row && !tag[BlankAddress_row][j])
						{
							
							count[BlankAddress_row]++;
							tag[BlankAddress_row][j] = true;
						}
						Blank_column = map[k*Size+i%Size];
						BlankAddress_column = k*Size+i%Size;
						if(!Blank_column && !tag[BlankAddress_column][j])
						{
							
							count[BlankAddress_column]++;
							tag[BlankAddress_column][j] = true;
						}
						Blank_cell = map[((i/(Size*3))*3+k/3)*Size+((i%Size)/3)*3+k%3];
						BlankAddress_cell = ((i/(Size*3))*3+k/3)*Size+((i%Size)/3)*3+k%3;
						if(!Blank_cell && !tag[BlankAddress_cell][j])
						{
							
							count[BlankAddress_cell]++;
							tag[BlankAddress_cell][j] = true;
						}
					}
				}
			}
			i = -1;	
		}
	}
	
	if(Found == 81)
	{
		setAns(Ans+1);
		if(Ans==1)
		{
			for(int i=0;i<sudokuSize;i++)
				map_tmp[i] = map[i];
		}	
		if(Ans>1)
		{
			cout<<"2"<<endl;
		    exit(1);
		}
	}
	else
	{
		int Max,i_Max;
		Max = 0;
		i_Max = -1;
		for(int i=0;i<sudokuSize;i++)
		{
			if(count[i]>Max)
			{
				Max = count[i];
				i_Max = i;
			}
		}
		for(int j=0;j<Size;j++)
		{
			if(!tag[i_Max][j])
			{
				map[i_Max] = j+1;
				
				Sudoku *tmp = new Sudoku(getBoard(),getAns());
				cul--;
				delete tmp;
			}
		}
	}
	
	if (cul==0 && Ans ==0)
	{
		cout << getAns() <<endl;
		exit(1);
	}
	if (cul==0 && Ans ==1)
	{
		cout << getAns() <<endl;
		for(int j=0;j<sudokuSize;j++)
				map[j] = map_tmp[j];
		for(int i=0; i<sudokuSize; i++)
		{			
			if(map[i]==0)
			{
				cout <<" "<< ' ';
			}
			else{
				cout << map[i] << ' ';
			}
			if ((i+1)%9 ==0)
			{
				cout << endl;
			}
		}
		cout << endl;
	}
	}
	}
}
//----------------------------------------
vector<int> Sudoku::getBoard()
{
	vector<int> out_map(sudokuSize);
	for(int i=0; i<sudokuSize; i++)
	{
		out_map[i] = map[i];
	}
	return out_map;
}
//----------------------------------------
int Sudoku::getAns()
{
	return Ans;
}
//----------------------------------------
void Sudoku::setAns(int A)
{
	Ans = A;
}
//----------------------------------------
bool Sudoku::checkZero()
{
	int zero = 0;
	for(int i=0; i<sudokuSize; i++)
	{
		if(map[i] == 0)
			++zero;
		else
			return false;
	}
	if(zero == 81)
		return true;
}
//----------------------------------------
bool Sudoku::checkRepeat(int arr[])
{
	int arr_repeat[Size]; // counters
	
	for(int i=0; i<Size; i++)
		arr_repeat[i] = 0; // initialize
	
	for(int i=0; i<Size; i++)
	{
		if (arr[i] != 0)
			++arr_repeat[arr[i]-1]; // count
	}
	for(int i=0; i<Size; i++)
	{
		if(arr_repeat[i] > 1) // all element
		return false; // must <= 1	
	}
	return true;
}
//----------------------------------------
bool Sudoku::isSolvable()
{
	bool check_result;
	int check_arr[Size];
	int location;
	
	for(int i=0; i<sudokuSize; i+=9) // check rows
	{
		for(int j=0; j<Size; j++)
			check_arr[j] = map[i+j];
		check_result = checkRepeat(check_arr);
		if(check_result == false)
			return false;
	}
	
	for(int i=0; i<Size; i++) // check columns
	{
		for(int j=0; j<Size; j++)
			check_arr[j] = map[i+9*j];
		check_result = checkRepeat(check_arr);
		if(check_result == false)
			return false;
	}

	for(int i=0; i<Size; i++) // check cells
	{
		for(int j=0; j<Size; j++)
		{
			location = 27*(i/3) + 3*(i%3)+9*(j/3) + (j%3);
			check_arr[j] = map[location];
		}
		check_result =checkRepeat(check_arr);
		if(check_result == false)
			return false;
	}
	return true;
}
//----------------------------------------
//----------------------------------------
void Sudoku::transform()
{
	readIn();
	change();
	printOut();
}
//----------------------------------------
void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%Size+1,rand()%Size+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}
//----------------------------------------
void Sudoku::changeNum(int a, int b)
{	
	for(int i=0; i<sudokuSize; i++)
	{
		map_tmp[i] = map[i];
	}
	for(int i=0; i<sudokuSize; i++)
	{
		if (map[i] == a)
			map[i] = b;
	}
	for(int i=0; i<sudokuSize; i++)
	{
		if (map_tmp[i] == b)
			map[i] = a;
	}
}
//----------------------------------------
void Sudoku::changeRow(int a, int b)
{
	for(int i=0; i<sudokuSize; i++)
	{
		map_tmp[i] = map[i];
	}
    if ((a==0 && b==1)||(a==1 && b==0))
	{
		for(int i=0; i<9;i++)
		{
			map[i+27] = map[i];
			map[i+36] = map[i+9];
			map[i+45] = map[i+18];
		}
		for(int i=0; i<9;i++)
		{
			map[i] = map_tmp[i+27];
			map[i+9] = map_tmp[i+36];
			map[i+18] = map_tmp[i+45];
		}
	}
	if ((a==0 && b==2)||(a==2 && b==0))
	{
		for(int i=0; i<9;i++)
		{
			map[i+54] = map[i];
			map[i+63] = map[i+9];
			map[i+72] = map[i+18];
		}
		for(int i=0; i<9;i++)
		{
			map[i] = map_tmp[i+54];
			map[i+9] = map_tmp[i+63];
			map[i+18] = map_tmp[i+72];
		}
	}
	if ((a==1 && b==2)||(a==2 && b==1))
	{
		for(int i=0; i<9;i++)
		{
			map[i+54] = map[i+27];
			map[i+63] = map[i+36];
			map[i+72] = map[i+45];
		}
		for(int i=0; i<9;i++)
		{
			map[i+27] = map_tmp[i+54];
			map[i+36] = map_tmp[i+63];
			map[i+45] = map_tmp[i+72];
		}
	}
}
//----------------------------------------
void Sudoku::changeCol(int a, int b)
{
	for(int i=0; i<sudokuSize; i++)
	{
		map_tmp[i] = map[i];	
	}
	if ((a==0 && b==1)||(a==1 && b==0))
	{
		for(int i=0; i<9;i++)
		{
			map[9*i+3] = map[9*i];
			map[9*i+4] = map[9*i+1];
			map[9*i+5] = map[9*i+2];
		}
		for(int i=0; i<9;i++)
		{
			map[9*i] = map_tmp[9*i+3];
			map[9*i+1] = map_tmp[9*i+4];
			map[9*i+2] = map_tmp[9*i+5];
		}
	}
	if ((a==0 && b==2)||(a==2 && b==0))
	{
		for(int i=0; i<9;i++)
		{
			map[9*i+6] = map[9*i];
			map[9*i+7] = map[9*i+1];
			map[9*i+8] = map[9*i+2];
		}
		for(int i=0; i<9;i++)
		{
			map[9*i] = map_tmp[9*i+6];
			map[9*i+1] = map_tmp[9*i+7];
			map[9*i+2] = map_tmp[9*i+8];
		}
	}
	if ((a==1 && b==2)||(a==2 && b==1))
	{
		for(int i=0; i<9;i++)
		{
			map[9*i+6] = map[9*i+3];
			map[9*i+7] = map[9*i+4];
			map[9*i+8] = map[9*i+5];
		}
		for(int i=0; i<9;i++)
		{
			map[9*i+3] = map_tmp[9*i+6];
			map[9*i+4] = map_tmp[9*i+7];
			map[9*i+5] = map_tmp[9*i+8];
		}
	}
}
//----------------------------------------
void Sudoku::rotate(int n)
{
	if(n==0 || n%4==0)
	{
	
	}
	else
	{
		int k=1;
		while(k<=n)
		{
			for(int i=0; i<sudokuSize;i++)
			{
				map_tmp[i] = map[i];
				map[i] = 0;
			}
			for(int i=0; i<Size;i++)
			{
				for(int j=8; j>=0;j--)
					map[9*i+j] = map_tmp[i+(8-j)*9];
			}
			k++;
		}
	}
			
}
//----------------------------------------
void Sudoku::flip(int n)
{
	for(int i=0; i<sudokuSize;i++)
	{
		map_tmp[i] = map[i];
	}
	if (n==1)
	{
		for(int i=0; i<Size;i++)
		{
			map[9*i+8] = map[9*i];
			map[9*i+7] = map[9*i+1];
			map[9*i+6] = map[9*i+2];
			map[9*i+5] = map[9*i+3];
		}
		for(int i=0; i<Size;i++)
		{
			map[9*i] = map_tmp[9*i+8];
			map[9*i+1] = map_tmp[9*i+7];
			map[9*i+2] = map_tmp[9*i+6];
			map[9*i+3] = map_tmp[9*i+5];
		}
	}
	else // n==0
	{
		for(int i=0; i<Size;i++)
		{
			map[i] = map[i+9*8];
			map[i+9] = map[i+9*7];
			map[i+9*2] = map[i+9*6];
			map[i+9*3] = map[i+9*5];
		}
		for(int i=0; i<Size;i++)
		{
			map[i+9*8] = map_tmp[i];
			map[i+9*7] = map_tmp[i+9];
			map[i+9*6] = map_tmp[i+9*2];
			map[i+9*5] = map_tmp[i+9*3];
		}
	}
}
//--------------------------------------------
void Sudoku::printOut()
{
	for(int i=0; i<sudokuSize; i++)
	{			
		if(map[i]==0)
		{
			cout <<"0"<< ' ';
		}
		else{
			cout << map[i] << ' ';
		}
		if ((i+1)%9 ==0)
		{
			cout << endl;
		}
	}
}
