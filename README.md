# FileManager
Sample task

FileManager CLI tool. 

Provides following API:
- Create text file: filemanager --create [src] [data]
- Copy file: filemanager --copy [src] [dst]
- Combine file: filemanager --combine [first] [second] [dst]
- Delete file: filemanager --delete [src]

1. Project structure  
App - file manager CLI executable, parser and commands execution  
Common - shared library with the file manipulation logic  
Tests - unit tests  

2. Build and run unit tests with the cmake tool  
a) use git to checkout to your local machine  
b) on your local machine within the repo typo  
mkdir build  
cd build/  
cmake ..  
make  
make test  
3) output cli tool should be in build/app/filemanager   

3. Depends on the boost 1.74 libraries

