echo "KNS-2022"
timeout /t 2
start "" C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\Debug\CourseTest.exe -in:C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNSbat\in3.txt  m l i
timeout /t 30
echo (get-content -path C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNSbat\KNS.asm)[-1] | powershell -command -
echo "KNS-2022 asm"
start ""  C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNSbat\KNS.asm
call C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\KNSbat\asm.bat
pause