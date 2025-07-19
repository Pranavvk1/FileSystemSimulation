#include "Directory.cpp"

class Parser {
    private:
        Directory currDirectory;
        Directory root;
    
    public:
        Parser() {
            currDirectory = Directory("root");
            this->root = currDirectory;
        }

        bool changeToChildDir(std::string dir) {
            Directory nextDir = currDirectory.getDirectory(dir);
            if(nextDir.getName() == "-1") {
                std::cout << dir << ": no such directory";
                return false;
            }
            currDirectory = nextDir;
            return true;
        }

        void changeToParentDir() {
            currDirectory = *(currDirectory.getParent());
        }

        std::string followPath(std::string path, bool shouldReturnToOriginalDir) {
            Directory originalDir = currDirectory;
            currDirectory = root;
            path = path.substr(5); // the length of the string "root/" is 5
            bool dirIsFound = true;
            while(path.find_first_of('/') != std::string::npos && dirIsFound) {
                std::string nextDir = path.substr(0, path.find_first_of('/'));
                dirIsFound = changeToChildDir(nextDir);
                path = path.substr(path.find_first_of('/') + 1);
            }
            if(shouldReturnToOriginalDir) {
                currDirectory = originalDir;
            }
            return path;
        }

        void changeDir(std::string path) {
            bool isInDirectory = true;
            if(path.find_first_of("/") != std::string::npos) {
                isInDirectory = false;
            }

            if(isInDirectory) {
                changeToChildDir(path);
                return;
            }
            
            std::string finalDir = followPath(path, false);
            changeToChildDir(finalDir);
        }

        void echoIntoFile(std::string instruction) {
            
        }

        void run() {
            std::string input;
            std::cout << currDirectory.getName() << " $";
            std::cin >> input;

            while(input != "q") {
                std::string instruction = input.substr(0, input.find_first_of(" "));
                std::string argument = input.substr(input.find_first_of(" ") + 1);
                if(instruction == "echo") {

                } else if (instruction == "mkdir") {
                    currDirectory.addDirectory(Directory(argument, &root));
                }
                std::cout << currDirectory.getName() << " $";
                std::cin >> input;
            }

        }

};