#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.maxsize = size;
		idtable.current_size = 0;
		idtable.table = new Entry[IDENT_MAX_ELEMENTS];
		if (size > IDENT_MAX_ELEMENTS) throw ERROR_THROW(128);
		return idtable;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n < idtable.maxsize && n >= 0)
			return idtable.table[n];
		else
			throw ERROR_THROW(128)
	}
	int GetProvVStr(IdTable& idtable, char prov[IDENT_STR_MAXSIZE - 1]) {
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (!strcmp(idtable.table[i].value.vstr->str, prov) && idtable.table[i].idtype == L && idtable.table[i].iddatatype == STR)
			{
				return i;
			}
		}
		return (int)LT_TI_NULLXDX;
	}

	int GetProvVInt(IdTable& idtable, int prov) {
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i].value.vint.value == prov && idtable.table[i].idtype == L && idtable.table[i].iddatatype == INT)
			{
				return i;
			}
		}
		return (int)LT_TI_NULLXDX;
	}
	int GetProvVlogic(IdTable& idtable, int prov) {
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i].value.vlogic == prov && idtable.table[i].idtype == L && idtable.table[i].iddatatype == BOO)
			{
				return i;
			}
		}
		return (int)LT_TI_NULLXDX;
	}
	char* GetLexemaName(IdTable& idtable)
	{
		char buffer[5]{};
		char numb[3]{};
		buffer[0] = 'L';
		_itoa_s(idtable.noname_count, numb, 10);
		strcat_s(buffer, 5, numb);
		idtable.noname_count++;
		return buffer;
	}
	char* GetLexemaNameFunc(char* token, char* func)
	{
		char tokenTemp[52] = { '\0' };
		int count = 0;
		for (int i = 0; func[i] != '\0'; i++) {
			tokenTemp[i] = func[i];
			count = i;
		}
		for (int i = 0; token[i] != '\0'; i++) {
			count++;
			tokenTemp[count] = token[i];
		}
		tokenTemp[++count] = '\0';
		return tokenTemp;

	}
	void Delete(IdTable& idtable)
	{
		delete idtable.table;
		idtable.table = nullptr;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (strlen(entry.id) > IDENT_MAX_SYMBOLS+20)
			throw ERROR_THROW(133);

		if (idtable.current_size < idtable.maxsize)
		{
			idtable.table[idtable.current_size] = entry;

			if (entry.iddatatype == IT::IDDATATYPE::INT)
				idtable.table[idtable.current_size].value.vint.value = IDENT_INT_DEFAULT;

			if (entry.iddatatype == IT::IDDATATYPE::STR)
			{
				idtable.table[idtable.current_size].value.vstr->str[0] = IDENT_STR_DEFAULT;
				idtable.table[idtable.current_size].value.vstr->len = 0;
			}

			if (entry.iddatatype == IT::IDDATATYPE::BOO)
				idtable.table[idtable.current_size].value.vlogic = IDENT_BOO_DEFAULT;

			idtable.current_size++;
		}
		else
			throw ERROR_THROW(125);
	}
	int IsId(IdTable& idtable, char id[IDENT_MAX_SYMBOLS], char parrent_function[IDENT_MAX_SYMBOLS])
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) &&
				!strcmp(idtable.table[i].parrent_block_name, parrent_function))
				return i;
		}
		return IDENT_NULLIDX;
	}

	int IsId(IdTable& idtable, char id[IDENT_MAX_SYMBOLS])
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return IDENT_NULLIDX;
	}
	int IsIdF(IdTable& idtable, char id[IDENT_MAX_SYMBOLS])
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0 && idtable.table[i].idtype == IT::IDTYPE::F)
				return i;
		}
		return IDENT_NULLIDX;
	}

	void PrintIdTable(IdTable& idtable, const wchar_t* in)
	{
		ofstream fout(in);

		if (fout.is_open())
		{
			fout << "Литералы: \n\n";

			fout << std::setw(15) << "Идентификатор:" << std::setw(17) << "Тип данных:" << std::setw(15) << "Длина строки:" << std::setw(20) << "Первое вхождение:"<<std::setw(15) << "Значение:" << std::endl;


			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::L)
				{
					std::cout.width(25);
					if (idtable.table[i].iddatatype == 1)
					{
						fout << "   " << idtable.table[i].id << "\t\t\t" << "INT "  << "      " << "-\t\t   " << idtable.table[i].idxLT << "\t\t\t    " << idtable.table[i].value.vint.value << std::endl;
						continue;
					}
					else if (idtable.table[i].iddatatype == 2)
					{
						fout << "   " << idtable.table[i].id << "\t\t\t" << "STR " <<  "      " << idtable.table[i].value.vstr->len << "\t\t   " << idtable.table[i].idxLT << "\t\t\t   " << idtable.table[i].value.vstr->str << std::endl;
						continue;
					}
					else
					{
						fout << "   " << idtable.table[i].id << "\t\t\t" << "BOO " <<  "      " << "-\t\t   " << idtable.table[i].idxLT << "\t\t\t    " << idtable.table[i].value.vlogic << std::endl;
						continue;
					}
				}
			}
			fout << "\n\n\n";
			fout << "Функции: \n\n";


			fout << std::setw(15) << "Идентификатор:" << std::setw(26) << "Тип данных возврата:" << std::setw(22) << "Первое вхождение:" << std::endl;


			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::F)
				{

					if (idtable.table[i].iddatatype == 1)
					{
						fout << "   " << idtable.table[i].id << std::setw(33 - strlen(idtable.table[i].id)) << "INT " << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else if (idtable.table[i].iddatatype == 2)
					{
						fout << "   " << idtable.table[i].id << std::setw(33 - strlen(idtable.table[i].id)) << "STR " << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else
					{
						fout << "   " << idtable.table[i].id << std::setw(33 - strlen(idtable.table[i].id)) << "BOO " << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}

				}

			}





			fout << "\n\n\n";

			fout << "Переменные: \n\n";

			fout << std::setw(25) << "Имя родительского блока:" << std::setw(20) << "Идентификатор:" << std::setw(16) << "Тип данных:" << std::setw(24) << "Тип идентификатора:" << std::setw(21) << "Первое вхождение:" << std::endl;

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::V)
				{
					if (idtable.table[i].iddatatype == 1)
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "INT " << std::setw(15) << "V" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else if (idtable.table[i].iddatatype == 2)
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "STR " << std::setw(15) << "V" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "BOO " << std::setw(15) << "V" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
				}

				if (idtable.table[i].idtype == IT::IDTYPE::P)
				{
					if (idtable.table[i].iddatatype == 1)
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "INT " << std::setw(15) << "P" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else if (idtable.table[i].iddatatype == 2)
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "STR " << std::setw(15) << "P" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "BOO " << std::setw(15) << "P" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
				}
				if (idtable.table[i].idtype == IT::IDTYPE::A)
				{
					if (idtable.table[i].iddatatype == 1)
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "INT " << std::setw(15) << "A" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else if (idtable.table[i].iddatatype == 2)
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "STR " << std::setw(15) << "A" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
					else
					{
						fout << "   " << idtable.table[i].parrent_block_name << std::setw(35 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << std::setw(20) << "BOO " << std::setw(15) << "A" << "\t\t\t" << idtable.table[i].idxLT << std::endl;
						continue;
					}
				}


			}
			fout << "\n\n\n";
		}
		else
			throw ERROR_THROW(127);
		fout.close();
	}
}

