#include <iostream>
#include "Parser.cpp"

int main() {
    Directory currDirectory("root");
    std::string fileNames[] = {"file1", "file2", "file3", "file4", "file5"};
    for(std::string name: fileNames) {
        currDirectory.addFile(File(name));
    }
    currDirectory.listContents();

    currDirectory.removeFile("file3");

    Directory newDir("newDir");
    currDirectory.addDirectory(newDir);
    currDirectory.listContents();

}