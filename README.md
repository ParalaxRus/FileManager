# FileManager
FileManager CLI tool. 

Provides following API:
- Create text file: filemanager --create [src] [data]
- Copy file: filemanager --copy [src] [dst]
- Combine two text file: filemanager --combine [first] [second] [dst]
- Delete file: filemanager --delete [src]  
Restrictions:  
- Supports only one command at a time for now
- Supports create and combine of the text files (binary streams are not tested) 
Project structure:  
app - file manager CLI executable, parser and commands execution  
common - shared library with the file manipulation logic  
script - installation script mimicking CI pipeline  (might need 'sudo')  
tests - unit tests  


Instructions for a bash script file which simulates CI and produces versioned debian package:  
1) Make sure your OS is uptodate (sudo apt update)  
2) Download installation script (FileManager/script/install.sh) to your local machine  
3) Make sure script is executable: 'chmod x install.sh'  
4) Run script (might need sudo)  
5) Generated debian package should be located in the 'home' folder


Build and test repo with cmake (if need be):  
a) use git to checkout FileManger repo to your local machine  
b) on your local machine within the repo typo  
mkdir build  
cd build/  
cmake ..  
cmake --build .
ctest  
c) output executable: build/app/filemanager  

Depends on the boost 1.74 libraries

