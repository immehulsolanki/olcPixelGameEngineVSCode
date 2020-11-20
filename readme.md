[![Generic badge](https://img.shields.io/badge/status-beta-red.svg)](https://github.com/immehulsolanki/olcPixelGameEngineVSCode/blob/master/README.md) [![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/immehulsolanki/olcPixelGameEngineVSCode) [![made-with-c++17](https://img.shields.io/badge/Made%20with-C++17-1f425f.svg)](https://isocpp.org/) 

# What is olcPixelGameEngine?

The official distribution of olcPixelGameEngine, a tool used in user javidx9's C++ tutorial YouTube videos and projects.
You only need the one file - olcPixelGameEngine.h - included in your project!
Provides a fast, richly featured, cross platform pixel drawing and user interface framework for
- The development of games
- Visualization of algorithms
- Prototyping and experimentation
- Education
- Handcrafted C++ GUI

Source: https://github.com/OneLoneCoder/olcPixelGameEngine

# olcPixelGameEngine with VSCode [Windows10]:
**Requirement:**
1. Latest VSCode for Windows [ [Download](https://code.visualstudio.com/) ]
2. Latest MinGW from Winlibs with atleast **GCC version 10.2.x** [ [Download](http://winlibs.com/) ]

Note: This setup is tested with "GCC 10.2.0 + LLVM/Clang/LLD/LLDB 11.0.0 + MinGW-w64 8.0.0 - release 3" on Windows10 machine updated as on 18 November 2020.

It is assumed that the version of mingw you are using has the following Windows libs included:
- user32 
- gdi32 
- opengl32 
- gdiplus 
- Shlwapi 
- dwmapi 
- stdc++fs

You are not supposed to find this libs manually it comes with the compiler it self, So dont worry about it yet!

**Configuration Steps:**

- **step1**: Install VSCode as normal software installtion, no special steps required.
- **step2**: Open VSCode and press **ctrl+shft+x** and install *C/C++ extension by Microsoft*.

![olcPixelGameEngineVSCode](./resources/img3.JPG)

- **step2**: Winlibs Mingw comes with compressed file type, its stand alone prebuilt binary within single folder. No installation required, just copy and past it.
- **step3**: Extract xxmingwxx.7z and you will get **mingw** folder along with all the necessory files, so now copy **mingw** folder to **C:/** drive manually.

![olcPixelGameEngineVSCode](./resources/img4.jpg)

- **step4**: Set windows environment variable path which points compiler as "C:\mingw64\bin"

![olcPixelGameEngineVSCode](./resources/img1.jpg)

- **step5**: Restart PC.
- **step6**: open widows terminal and type **gcc --version** it should give ouput as its installed version no.

![olcPixelGameEngineVSCode](./resources/img2.JPG)


**Compiling Steps:**

- **step1**: Make one new folder anywhere or preferably on your desktop. Example: "pge_test".

![olcPixelGameEngineVSCode](./resources/img6.jpg)

- **step2**: Clone/Download **official OLC PGE repository** [ [Download](https://github.com/OneLoneCoder/olcPixelGameEngine) ], 
And get two files named:
1. *olcExampleProgram.cpp*
2. *olcPixelGameEngine.h*

![olcPixelGameEngineVSCode](./resources/img11.JPG)
![olcPixelGameEngineVSCode](./resources/img12.JPG)

- **step3**: Similarly get .vscode folder from **this** repository.

![olcPixelGameEngineVSCode](./resources/img5.JPG)

- **step4**: Verify that you got **.vscode** folder with cloned or downloaded from THIS repository contents.
- **step5**: Now inside your "pge_test" folder, put this .vscode folder and two files downloaded in step1.

![olcPixelGameEngineVSCode](./resources/img7.jpg)

- **step6**: Open VScode
- **step7**: In VScode **Home** select File > Open Folder > and select your "pge_test" folder.

![olcPixelGameEngineVSCode](./resources/img8.JPG)

- **step8**: Now verify in VSCode IDE that folder and files are recognized and listed properly.

![olcPixelGameEngineVSCode](./resources/img9.JPG)

- **step9**: Open olcExampleProgram.cpp file with double click on it.
- **step6**: press "ctrl+shft+b"

![olcPixelGameEngineVSCode](./resources/img10.JPG)

- **step7**: You will get **.exe** named olcExampleProgram.exe in same directory
- **step8**: Run it in terminal with **./olcExampleProgram.exe** command, it should run.
Done!

If you are already experianced with VSCode IDE, then simply copy and past contents from:
1_c_cpp_properties.txt
2_tasks.txt
files and modify it as per your convenience.

## Manually with Terminal:
You can also compile PGE in MS terminal as well as VSCode terminal by following method.
You must place both
olcExampleProgram.cpp
olcPixelGameEngine.h
in **same folder** and run following command in MS Terminal or VScode Terminal:

```g++ -std=c++17 olcExampleProgram.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs```

You will get the following O/P:

```
D:\ADesktop\vsCppWorkSpace\cpppge>g++ -std=c++17 olcExampleProgram.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs

D:\ADesktop\vsCppWorkSpace\cpppge>a.exe
```
You should now able to see the output of sample program.
Done!