#pragma once

#include "stdafx.h"

using namespace In;
using namespace LT;
using namespace IT;

namespace LA
{
	struct TypeOfVariable
	{
		int LT_position = -1;
		enum
		{
			UNDEF = -1,
			INT = 1,
			STRING = 2,
			BOOL = 3,
			ARRAY = 4
		} type_of_variable;
	};

	void LexAnalysis(const IN& source, LexTable& lexTable, IdTable& idTable);
	bool TokenAnalysis(char* token, int strNumber, LexTable& lexTable, IdTable& idTable, int colinstring, bool& flagOFsourse);
	bool IdentificatorAnalysis(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVariable& type, int colinstring, bool sourseFlag);
}
