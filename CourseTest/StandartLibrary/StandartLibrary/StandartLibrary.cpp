#pragma warning(disable : 4996)
#include <iostream>
#include <time.h>
#include <windows.h>


// TODO: Это пример библиотечной функции.
extern "C"
{
	void __stdcall print(char* value)
	{
		std::cout << value << "\n";
	}

	void __stdcall printint(int value)
	{
		std::cout << value << "\n";
	}

	void __stdcall printcurrenttime()
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		std::cout << st.wHour << "." << st.wMinute << "." << st.wSecond << "\n";
	}

	void __stdcall printcurrentdate()
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		std::cout << st.wYear << "." << st.wMonth << "." << st.wDay << "\n";
	}

	void __stdcall printerror()
	{
		std::cout << "The result of the calculation turned out to be less than zero\n";
	}

	void __stdcall cat1(char* dest, char* par1)
	{
		int k = 0;
		for (int i = 0; par1[i] != '\0'; i++)
			dest[k++] = par1[i];

		dest[k] = '\0';
	}

	void __stdcall cat2(char* destination, char* left_operand, char* right_operand)
	{
		int k = 0;
		for (int i = 0; right_operand[i] != '\0'; i++)
			destination[k++] = right_operand[i];

		for (int i = 0; left_operand[i] != '\0'; i++)
			destination[k++] = left_operand[i];

		destination[k] = '\0';
	}
}