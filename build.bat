cl /c /Zi /EHsc /std:c++latest src/*.cpp src/system/*.cpp src/math/*.cpp src/graphics/*.cpp /Iinclude/ /Foobj/ /Febin\jadeli.lib
:: xcopy src\ export\include\jadel\ /exclude:excludedfileslist.txt /E
:: DEL export\include\jadel\*.cpp /S