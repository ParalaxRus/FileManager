# FileManager
Sample task

FileManager CLI tool. 

Provides following API:
- Create text file: filemanager --create [src] [data]
- Copy file: filemanager --copy [src] [dst]
- Combine two text file: filemanager --combine [first] [second] [dst]
- Delete file: filemanager --delete [src]  

Example:  
./filemanager --create a.txt text  
or in case if elevated privileges needed  
sudo ./filemanager --create a.txt text  

Restrictions:  
- Supports only one command at a time for now
- Supports create and combine of the text files (binary streams are not tested) 

Project structure:  
app - file manager CLI executable, parser and commands execution  
common - shared library with the file manipulation logic  
script - installation script mimicking CI pipeline  (might need 'sudo')  
tests - unit tests  

Build and run unit tests with the cmake tool:  
a) use git to checkout to your local machine  
b) on your local machine within the repo typo  
mkdir build  
cd build/  
cmake ..  
cmake --build .
ctest  
c) output executable: build/app/filemanager  

Depends on the boost 1.74 libraries

