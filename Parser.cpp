#include "Directory.cpp"

class Parser {
    private:
        Directory currDirectory;
        Directory parentDirectory;
        Directory root;
    
    public:
        Parser(Directory root, Directory parent) {
            currDirectory = root;
            this->root = root;
            parentDirectory = parent;
        }

        void changeToChildDir(std::string dir) {
            parentDirectory = currDirectory;
            currDirectory = currDirectory.getDirectory(dir);
        }

        void changeDir(std::string path) {
            std::string rootStr = "root";
            bool isIndirectory = true;
            for(int i = 0; i < 4; i++) {
                if(path.at(i) != rootStr.at(i)) {
                    isIndirectory = false;
                }
            }

            if(isIndirectory) {
                changeToChildDir(path);
                return;
            }
            
            currDirectory = root;
            path = path.substr(rootStr.length() + 1);
            while(path.find_first_of('/') != std::string::npos) {
                std::string nextDir = path.substr(0, path.find_first_of('/'));
                changeToChildDir(nextDir);
                path = path.substr(path.find_first_of('/') + 1);
            }
            changeToChildDir(path);
        }


};