#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#define maxRows 40
#define maxCols 80

void loadArray(ifstream& rdr, int PrisonMap[][maxCols], int& rows, int& cols)
{
	rdr >> rows >> cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			rdr >> PrisonMap[r][c];
		}

	}
}
void printArray(const char MSG[], int PrisonMap[][maxCols], int rows, int cols)
{
	cout << endl << endl << MSG << endl;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			cout << setw(2) << PrisonMap[r][c];
		}
		cout << endl;
	}
}
bool isPrisonBreakable(int PrisonMap[][maxCols], int rectangleStartRow, int rectangleStartCol, int rectangleEndRow, int rectangleEndCol)
{
	for (int cl = rectangleStartCol; cl <= rectangleEndCol; cl++)
	{
		if (PrisonMap[rectangleStartRow][cl] == 0 || PrisonMap[rectangleEndRow][cl] == 0)
			return true; 
	}
	for (int rw = rectangleStartRow; rw <= rectangleEndRow; rw++)
	{
		if (PrisonMap[rw][rectangleStartCol] == 0 || PrisonMap[rw][rectangleEndCol] == 0)
			return true;
	}
	return false;
}
void findPrisonerLocation(int PrisonMap[][maxCols], int rows, int cols, int& PrisonerRow, int& PrisonerCol)
{
	for (int rw = 0; rw < rows; rw++)
	{
		for (int cl = 0; cl < cols; cl++)
		{
			if (PrisonMap[rw][cl] == 2)
			{
				PrisonerRow = rw;
				PrisonerCol = cl;
				return;
			}
		}
	}
}
bool isPrisonerAlreadyFree(int rectangleStartRow, int rectangleStartCol, int rectangleEndRow, int rectangleEndCol, int prisonerRow, int prisonerCol)
{

	if (prisonerRow > rectangleStartRow && prisonerRow < rectangleEndRow && prisonerCol > rectangleStartCol && prisonerCol < rectangleEndCol)
		return false;
	else
		return true;
}
void findWallBoundary(int PrisonMap[][maxCols], int rows, int cols, int& rectangleStartRow, int& rectangleStartCol, int& rectangleEndRow, int& rectangleEndCol)
{
		int r, c;
		for (int r = 0; r < rows; r++)
		{
			bool found = false;
			for (int c = 0; c < cols; c++)
			{
				if (PrisonMap[r][c] == 1)
				{
					rectangleStartRow = r;
					rectangleStartCol = c;
					found = true;          
					break;
				}
			}
			if (found)     
				break;   
		}
		for (int r = rows - 1; r >= 0; r--)
		{
			for (int c = cols - 1; c >= 0; c--)
			{
				if (PrisonMap[r][c] == 1)
				{
					rectangleEndRow = r;
					rectangleEndCol = c;
					return;
				}
			}
		}
	
}
void prison_BreakSolver(int PrisonMap[][maxCols], int rows, int cols)
{
	int rectangleStartRow, rectangleStartCol, rectangleEndRow, rectangleEndCol, PrisonerRow, PrisonerCol;
	bool Free, Breakable;
	findWallBoundary(PrisonMap, rows, cols, rectangleStartRow, rectangleStartCol, rectangleEndRow, rectangleEndCol);
	findPrisonerLocation(PrisonMap, rows, cols, PrisonerRow, PrisonerCol);
	Free = isPrisonerAlreadyFree(rectangleStartRow, rectangleStartCol, rectangleEndRow, rectangleEndRow, PrisonerRow, PrisonerCol);
	Breakable = isPrisonBreakable(PrisonMap, rectangleStartRow, rectangleStartCol, rectangleEndRow, rectangleEndCol);
	if (Free == 1)
		cout << "The prisoner is already free.";
	else if (!Free && !Breakable)
		cout << "The prisoner is imprisoned for life.";
	else if (!Free && Breakable)
		cout << "The prisoner is inside the prison but can break free.";
}
int main()
{

	int PrisonMap[maxRows][maxCols], rows, cols;
	ifstream Rdr("Maps1.txt");
	int noOfMps;
	Rdr >> noOfMps;
	for (int ci = 1; ci <= noOfMps; ci++)
	{
		loadArray(Rdr, PrisonMap, rows, cols);
		printArray(("Prison " + to_string(ci) + ": ").c_str(), PrisonMap, rows, cols);
		prison_BreakSolver(PrisonMap, rows, cols);

		cout << endl;
	}
	return 0;
}


