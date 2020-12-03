# Running oipExpress 


## Prerequisites: 

- download boost, unzip
- install CMake
- install git
- install VisualStudio and a C++ environment

## Create the oipExpress.exe

oipExpress.exe is the parser that converts a given EXP file into suitable Cpp code. 

1. clone the repo: 
    https://github.com/Vertexwahn/oipExpress 

2. open the CMakeLists.txt file and update the path to your boost directory. Change the version number accordingly

3. run CMake -> you will get a Visual Studio Solution *sln. Open it

4. Run the `ALL-BUILD` project

5. Open the Debug Folder and check if `oipExpress.exe` got created. 


## Run the parsing process

`oipExpress.exe` is a command line application. It takes an exp file as input and outputs suitable Cpp and hpp files to the stated output directory

Use `oipExpress --help` to get help in setting up the correct input and output parameters. 

Run the exe with your exp file. It will generate all classes and another CMake file. 


## Compile the EarlyBindingLibrary

Move to the recently generated CMake file and run the CMake process. 
This will generate another Visual Studio Project that contains all IFC classes. 
Compile it and you are ready to go. 
