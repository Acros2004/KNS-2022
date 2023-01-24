#include "stdafx.h"

namespace LT
{
	LexTable Create(int size)
	{
		LT::LexTable lextable;
		lextable.maxsize = size;
		lextable.current_size = 0;
		lextable.table = new LT::Entry[size];
		if (size > LT_MAXSIZE) throw ERROR_THROW(122);
		return lextable;

	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.current_size < lextable.maxsize)
		{
			lextable.table[lextable.current_size] = entry;
			lextable.current_size++;
		}
		else
			throw ERROR_THROW(122);
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n < lextable.maxsize && n >= 0)
			return lextable.table[n];
		else
			throw ERROR_THROW(122);
	}

	void Delete(LexTable& lextable)
	{
		delete lextable.table;
		lextable.table = nullptr;
	}

	/*void LexTablePrint(LexTable& lextable)
	{
		ofstream fout("TableOfLexems.txt");
		int current_string = 0;
		fout << current_string + 1 << '\t';
		for (int i = 0; i < lextable.current_size; i++)
		{
			if (current_string != lextable.table[i].sn)
			{
				current_string = lextable.table[i].sn;
				fout << endl << lextable.table[i].sn + 1 << '\t';
			}
			fout << lextable.table[i].lexema;
		}
		fout.close();
	}*/
	void PrintLexTable(LexTable& lextable, IT::IdTable& idtable, const wchar_t* in)
	{

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(in);
		(*lex_stream) << "##########################################################################################################################" << std::endl;
		(*lex_stream) << "--------- Лексемы ---------" << endl;;

		if (lex_stream->is_open())
		{
			int num_string = 0;
			
			for (int i = 0; i < lextable.current_size;)
			{
				if (num_string == lextable.table[i].sn + 1)
					(*lex_stream) << lextable.table[i++].lexema;
				else
				{
					num_string++;
					if (lextable.table[i].sn + 1 != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << ".\t";

					if (num_string == lextable.table[i].sn + 1)
						(*lex_stream) << lextable.table[i++].lexema;
				}
			}
			(*lex_stream) << "\n--------- Таблица лексем ---------" << std::endl;
			(*lex_stream) << "Лексема:" << "   " << "Номер строки:" << "   " << "Позиция в таблице лексем" << "   " << "Позиция в таблице индетификаторов:" << "   " << "Имя по таблице индитификаторов:"<< std::endl;
			for (int i = 0; i < lextable.current_size; i++) {
				if (lextable.table[i].lexema >= '0' && lextable.table[i].lexema <= '9') {
					(*lex_stream) << lextable.table[i].lexema << std::setw((11 - 1) + (sizeof(lextable.table[i].sn) / sizeof(int))) << lextable.table[i].sn << std::setw(16 - (sizeof(lextable.table[i].sn) / sizeof(int)) + sizeof(i) / sizeof(int)) << i << std::endl;
				}
				else if (lextable.table[i].idxTI != (int)LT_TI_NULLXDX)
					(*lex_stream) << lextable.table[i].lexema << std::setw((11 - 1) + (sizeof(lextable.table[i].sn) / sizeof(int))) << lextable.table[i].sn << std::setw(16 - (sizeof(lextable.table[i].sn) / sizeof(int)) + sizeof(i) / sizeof(int)) << i << std::setw(27 - (sizeof(i) / sizeof(int)) + (sizeof(lextable.table[i].idxTI) / sizeof(int))) << lextable.table[i].idxTI << std::setw(37 - (sizeof(lextable.table[i].idxTI) / sizeof(int)) + std::strlen(IT::GetEntry(idtable, lextable.table[i].idxTI).id)) << IT::GetEntry(idtable, lextable.table[i].idxTI).id << std::endl;
				else (*lex_stream) << lextable.table[i].lexema << std::setw((11 - 1) + (sizeof(lextable.table[i].sn) / sizeof(int))) << lextable.table[i].sn << std::setw(16 - (sizeof(lextable.table[i].sn) / sizeof(int)) + sizeof(i) / sizeof(int)) << i << std::endl;
			}

		}
		else
			throw ERROR_THROW(131);
		lex_stream->close();
		delete lex_stream;

	}
}


