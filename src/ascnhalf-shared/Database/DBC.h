/* AscNHalf */

#ifndef __DBC_H
#define __DBC_H

#include "../Common.h"

enum DBCFmat
{
	F_STRING = 0,
	F_INT = 1,
	F_FLOAT = 2,
	F_NADA = 3
};

class DBC {
	int rows, cols, dblength,weird2; // Weird2 = most probably line length
	unsigned int* tbl;
	char* db,name[MAX_PATH];
	bool loaded;
	DBCFmat *format;
public:
	DBC();
	void Load(const char *filename);
	void CSV(char *filename, bool info = false);
	void GuessFormat();
	DBCFmat GuessFormat(int row, int col);
	void FormatCSV(const char *filename, bool info = false);
	void Lookup(char* out, int row, int col,char isstr=0,bool onlystr=false);
	void LookupFormat(char* out, int row, int col);
	void RowToStruct(void* out, int row);
	bool IsLoaded() { return loaded; }
	void* __fastcall GetRow(unsigned const int index) { return (void *)&tbl[index*cols]; }
	char* __fastcall LookupString(unsigned const int offset) { return db+offset; }
	int GetRows() { return rows; }
	int GetCols() { return cols; }
	int GetDBSize() { return dblength; }
	~DBC();
};
			
#endif
