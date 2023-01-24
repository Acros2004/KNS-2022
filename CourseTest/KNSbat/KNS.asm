.586							; система команд (процессор Pentium)
.model flat, stdcall			; модель памяти, соглашение о вызовах
includelib kernel32.lib			; компановщику: компоновать с kernel32
includelib libucrt.lib			; для UCRT - universal C Run-Time library

ExitProcess PROTO: DWORD		; прототип функции для завершения процесса Windows

;-----------Standart functions-----------
includelib C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\Debug\StandartLibrary.lib
cat1 PROTO : DWORD, : DWORD
cat2 PROTO : DWORD, : DWORD, : DWORD
print PROTO : DWORD
printint PROTO : DWORD



printcurrenttime PROTO
printcurrentdate PROTO
printerror PROTO
;----------------------------------------

.stack 4096

;---------------Literals---------------
.const

L6	sdword	7	 ; int literal
L8	sdword	12	 ; int literal
L9	sdword	3	 ; int literal
L10	sdword	10	 ; int literal
L11	sdword	6	 ; int literal
L12	sdword	4	 ; int literal
L13	sdword	9	 ; int literal
L14	sdword	15	 ; int literal
L15	sdword	20	 ; int literal
L35	byte	"boo,", 0
L36	sdword	1	 ; int literal
L39	sdword	1	 ; bool literal
L40	sdword	0	 ; bool literal
L41	sdword	16	 ; int literal
L42	sdword	13	 ; int literal
L43	byte	"testtext1", 0
L44	byte	"testtext2", 0
L45	byte	"concat", 0
L46	byte	"bool op", 0
L47	byte	"firstofarray", 0
L48	sdword	0	 ; int literal
L49	byte	"maxofarray", 0
L52	byte	"date", 0
;--------------------------------------------


;----------------Variables-------------------
.data

x	sdword	0	 ; int variable
y	sdword	0	 ; int variable
z	sdword	0	 ; int variable
k	sdword	0	 ; int variable
m	sdword	0	 ; int variable
l	sdword	0	 ; int variable
sa	byte	255 dup(0)	 ; string variable
sb	byte	255 dup(0)	 ; string variable
sc	byte	255 dup(0)	 ; string variable
bfs	sdword	0	 ; bool variable
bte	sdword	0	 ; bool variable
boo	byte	255 dup(0)	 ; string variable
sadc	sdword	0	 ; int variable
myArray sdword 12, 3, 10, 6, 4, 9, 15, 20