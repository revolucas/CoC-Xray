## XRAY 16 Engine Modifications
## Open X-Ray Call of Chernobyl Edition
----
This repository contains XRAY Engine sources based on version 1.6.02 for specific use with the Call of Chernobyl modification.
The original engine is used in S.T.A.L.K.E.R. Call of Pripyat game released by GSC Game World and any changes to this engine are allowed for ***non-commercial*** use only (see [License.txt](https://github.com/avoitishin/xray-16/blob/master/License.txt) for details).

## Build Instructions
This project is maintained under Visual Studio 2013.
You need https://developer.microsoft.com/en-us/windows/downloads/windows-8-1-sdk
You need these SDK libraries: https://drive.google.com/file/d/0B0zCaycrwhLHX09kaXdSeWNhWVE/view?usp=sharing

1. In Windows Advanced System Settings, create two new Environment variables.
2. `XRAY_16X_GAME` should be the location where binary files are output. ex. E:\STALKER\Games\
3. `XRAY_16X_LIBS` should be the folder in which you extracted the needed SDK libraries. ex. E:\STALKER\X-Ray Source\xray-16-libraries\
4. After building the solution copy lua51.dll from `src\3rd party\luajit-2\bin\x86` into your XRAY_16X_GAME folder.
5. If you are not using CoC, then you need the minimal changes foud in `res\gamedata`

* Notes: Currently only Release/Win32 will build
* If you find a bug or have an enhancement request, file an [Issue](https://github.com/revolucas/xray-16/issues).
* Please go to our [Wiki](https://github.com/avoitishin/xray-16/wiki) pages for detailed description of changes and other useful information.   

