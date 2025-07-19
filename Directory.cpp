#include <vector>
#include "File.cpp"

class Directory {
    private:
        std::vector<File> files;
        std::vector<Directory> directories;
        Directory *parent;
        std::string name;

    public:
        Directory() {}

        Directory(std::string name) {
            this->name = name;
        }

        Directory(std::string name, Directory *parent) {
            this->name = name;
            this->parent = parent;
        }

        std::string getName() {
            return name;
        }

        Directory *getParent() {
            return parent;
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

        void removeDirectory(std::string target) {
            std::vector<Directory> newDirectories;
            for(Directory directory: directories) {
                if(directory.getName() != target) {
                    newDirectories.push_back(directory);
                }
            }
            directories = newDirectories;
        }

        void addFile(File file) {
            files.push_back(file);
        }

        void addDirectory(Directory directory) {
            directories.push_back(directory);
        }

        void listContents() {
            for(File file: files) {
                std::cout << file.getName() << " ";
            }
            for(Directory directory: directories){
                std::cout << directory.getName() << " ";
            }
            std::cout << '\n';
        }
};