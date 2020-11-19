Requirement:
latest Vscode with c++ ms plugin,
mingw latest with GCC V10.2

required windows libs for command line args:
user32
gdi32
opengl32
gdiplus
Shlwapi
stdc++fs

put both .cpp and .h file in same directory.
navigato to that directory in vscode terminal,
and run following command.
change the .cpp file with file name.

g++ -static-libgcc -std=c++17 olcExampleProgram.cpp -luser32 -lgdi32 -lgdiplus -lopengl32 -lShlwapi -lstdc++fs

Done!

Actual O/P:
========================
PS D:\ADesktop\vsCppWorkSpace\cppexperiments\pge> g++ -static-libgcc -std=c++17 olcExampleProgram.cpp -luser32 -lgdi32 -lgdiplus -lopengl32 -lShlwapi -ldwmapi -lstdc++fs                                                                                                   ngl32 -lShlwapi -ldwmapi -lstdc++fs
PS D:\ADesktop\vsCppWorkSpace\cppexperiments\pge> ./a.exe


=========== task.json ======
copy past this and while .cpp active press "ctrl+shft+b".

{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: g++.exe build active file",
			"command": "C:\\mingw64\\bin\\g++.exe",
			"args": [
				"-g",
				"-std=c++17",
				"${file}",
				"-o",
				"${fileDirname}\\${fileBasenameNoExtension}.exe",				
				"-lpthread",				
				"-luser32",
				"-lgdi32",
				"-lgdiplus",
				"-lopengl32",
				"-lShlwapi",
				"-ldwmapi",
				"-lstdc++fs"
			],
			"options": {
				"cwd": "C:\\mingw64\\bin"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "compiler: C:\\mingw64\\bin\\g++.exe"
		}
	]
}