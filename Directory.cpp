#include <iostream>
#include <vector>
#include "File.cpp"

class Directory {
    private:
        std::vector<File> files;
        std::vector<Directory> directories;
        std::string name;

    public:
        Directory(std::string name) {
            this->name = name;
        }

        std::string getName() {
            return name;
        }

        File getFile(std::string target) {
            for(File file : files) {
                if(file.getName() == target) {
                    return file;
                }
            }
            return File("-1");
        }

        Directory getDirectory(std::string target) {
            for(Directory directory: directories) {
                if(directory.getName() == target) {
                    return directory;
                }
            }
            return Directory("-1");
        }

        void removeFile(std::string target) {
            std::vector<File> newFiles;
            for(File file: files) {
                if(file.getName() != target) {
                    newFiles.push_back(file);
                }
            }
            files = newFiles;
        } 



};