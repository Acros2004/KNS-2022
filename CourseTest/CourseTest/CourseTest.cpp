
#include "stdafx.h"




using namespace std;

int wmain(int argc, _TCHAR* argv[])
{
	Log::LOG	log = Log::INITLOG;

	
	setlocale(LC_ALL, "ru");
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);//считываем параметры
		log = Log::getlog(parm.log);
		Log::WriteLine(log, (char*)"Тест:", (char*)"без ошибок", (char*)"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getIn(parm.in, parm.out);
		Log::WriteIn(log, in);
		LexTable lexTable = LT::Create(LT_MAXSIZE - 1);
		IdTable	idTable = IT::Create(IDENT_MAX_ELEMENTS - 1);
		LA::LexAnalysis(in, lexTable, idTable);
	LT::PrintLexTable(lexTable,idTable, L"C:\\Users\\noname\\Desktop\\123\\KPO2course\\course_project\\CourseTest\\tableOfLexem.txt");
	IT::PrintIdTable(idTable, L"C:\\Users\\noname\\Desktop\\123\\KPO2course\\course_project\\CourseTest\\tableOfID.txt");
		MFST_TRACE_START
			MFST::Mfst mfst(lexTable, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printRules();

		SemAnalysis(lexTable, idTable);

		PolishNotation(lexTable, idTable);
		Log::Close(log);
		
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);//и зачем я это всё писал?
		cout << "\nОшибка " << e.id << ": " << e.message << ", строка " << e.inext.line + 1 << " символ " << e.inext.col << endl;
	}
	system("pause");
	return 0;




	/*cout << "тест Error::geterror" << endl;
	try { throw ERROR_THROW(100); }
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl;
	};
	cout << "тест Error::geterrorin" << endl;
	try { throw ERROR_THROW_IN(111,7,7); }
	catch (Error::ERROR e) {
		cout << "Ошибка" << e.id << ": " << e.message << ", строка " << e.inext.line << ",позиция " << e.inext.col << endl;
	}*/



	/*cout << " test In::getin" << endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		cout << in.text << endl;
		cout << "Всего символов " << in.size << endl;
		cout << "Всего строк " << in.lines << endl;
		cout << "Пропущено " << in.ignor << endl;
	}
	catch (Error::ERROR e) {
		cout << "Ошибка " << e.id << ": " << e.message << endl;
		cout << "строка " << e.inext.line << " позиция " << e.inext.col << endl;
	}*/


	/*cout << "тест Parm::getparm " << endl;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		wcout << "-in: " << parm.in << ", -out: " << parm.out << ", -log: " << parm.log << endl;
	}
	catch (Error::ERROR e) {
		cout << "Ошибка " << e.id << ": " << e.message << endl;
	};*/
}