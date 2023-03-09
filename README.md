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
3) Make sure script is executable: 'chmod +x install.sh'  
4) Run script (might need sudo)  
5) It produces versioned debian package (FileManager.xxx.deb) and installes it (FileManager) into the 'home' folder (common.so library goes into the lib folder)


Instructions for build and test repo with cmake:  
1) Use git to checkout FileManger repo to your local machine  
2) Within the repo on your local mahine type:  
mkdir build  
cd build/  
cmake ..  
cmake --build .  
ctest  
3) output executable: build/app/filemanager  

Depends on the boost 1.74 libraries

