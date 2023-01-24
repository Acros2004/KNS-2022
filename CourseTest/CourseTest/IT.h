#pragma once


#define IDENT_MAX_SYMBOLS		32				// ������������ ���������� ������� � ��������������
#define IDENT_MAX_ELEMENTS		4096			// ������������ ���������� ��-�� � ������� ��������������� 
#define IDENT_INT_DEFAULT		0x00000000		// �������� �� ��������� ��� ���� integer 
#define IDENT_STR_DEFAULT		0x00			// �������� �� ��������� ��� ���� string 
#define IDENT_BOO_DEFAULT		0				// �������� �� ��������� ��� ���� bool
#define IDENT_NULLIDX			0xffffffff		// ��� �������� ������� ���������������
#define IDENT_STR_MAXSIZE		255				// ������������ ������ ������
#define IDENT_ARRAY_MAXSIZE		10				// ������������ ������ �������

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, BOO = 3 };				// ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, PF = 5, A = 6 };	// ���� ���������������: ����������, �������, ��������, �������, �������� �������, ������

	struct Entry		// ������ ������� ���������������
	{
		int				idxLT;
		char			parrent_block_name[IDENT_MAX_SYMBOLS];	// ��� ������������� �����
		char			id[IDENT_MAX_SYMBOLS+20];					// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE		iddatatype;						// ��� ������
		IDTYPE			idtype;							// ��� ��������������

		union
		{
			struct
			{
				int value;
				int array_size;
				int parm_count;
			}vint;						// �������� integer
			struct
			{
				int len;						// ��������� �������� � string
				char str[IDENT_STR_MAXSIZE - 1];	// ������� string
			} vstr[IDENT_STR_MAXSIZE];				// �������� string
			int vlogic;
		} value;								// �������� ��������������
	};

	struct IdTable // ��������� ������� ���������������
	{
		int noname_count = 0;
		int maxsize;				// ������� ������� ��������������� < IDENT_MAX_ELEMENTS
		int current_size;			// ������� ������ ������� ��������������� < maxsize
		Entry* table;				// ������ ����� ������� ���������������
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[IDENT_MAX_SYMBOLS]);
	int IsId(IdTable& idtable, char id[IDENT_MAX_SYMBOLS], char parrent_function[IDENT_MAX_SYMBOLS + 5]);
	int IsIdF(IdTable& idtable, char id[IDENT_MAX_SYMBOLS]);
	void Delete(IdTable& idtable);
	int GetProvVInt(IdTable& idtable, int prov);
	int GetProvVlogic(IdTable& idtable, int prov);
	int GetProvVStr(IdTable& idtable, char prov[IDENT_STR_MAXSIZE - 1]);
	char* GetLexemaName(IdTable& idtable);
	char* GetLexemaNameFunc(char* func, char* token);
	void PrintIdTable(IdTable& idtable, const wchar_t* in);
};