call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
ml /c /coff  C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNS-2022_asm\KNS.asm
link /OPT:NOREF /DEBUG C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNSbat\KNS.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:library
call C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNSbat\KNS.exe
pause