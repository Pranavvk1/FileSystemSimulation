#include "Directory.cpp"

class Parser {
    private:
        Directory *currDirectory;
        Directory root;
    
    public:
        Parser() {
            root = Directory("root");
            currDirectory = &root;
        }

        bool changeToChildDir(std::string dir) {
            Directory *nextDir = currDirectory->getDirectory(dir);
            if(nextDir == nullptr) {
                std::cout << dir << ": no such directory";
                return false;
            }
            currDirectory = nextDir;
            return true;
        }

        void changeToParentDir() {
            currDirectory = currDirectory->getParent();
        }

        std::string followPath(std::string path, bool shouldReturnToOriginalDir) {
            Directory *originalDir = currDirectory;
            currDirectory = &root;
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
            //instruction should look like ""content" > filePath"
            int indexOfArrow = instruction.find_first_of(">"); 
            std::string content = instruction.substr(1, indexOfArrow - 3); 
            std::string filePath = instruction.substr(indexOfArrow + 2);

            if(filePath.substr(0, 4) == "root") {
                filePath = followPath(filePath, true);
            }

            File targetFile = currDirectory->getFile(filePath);
            if(targetFile.getName() == "-1") {
                currDirectory->addFile(File(filePath, content));
            } else {
                targetFile.setContents(content);
            }
        }

        void run() {
            std::string input;
            std::cout << currDirectory->getName() << " $ ";
            std::cin >> input;

            while(input != "q") {
                std::string instruction = input.substr(0, input.find_first_of("_"));
                std::string argument = input.substr(input.find_first_of("_") + 1);
                if(instruction == "echo") {
                    if(argument.find_first_of(">") == std::string::npos) {
                        std::cout << argument << '\n';
                    } else {
                        echoIntoFile(argument);
                    }
                } else if (instruction == "mkdir") {
                    Directory newDirectory = Directory(argument, currDirectory);
                    currDirectory->addDirectory(newDirectory);
                } else if(instruction == "mk") {
                    currDirectory->addFile(File(argument));
                } else if(instruction == "rmdir") {
                    currDirectory->removeDirectory(argument);
                } else if(instruction == "cd") {
                    if(argument == "..") {
                        changeToParentDir();
                    } else {
                        changeDir(argument);
                    }
                } else if(instruction == "ls"){
                    if(argument == "parent") {
                        Directory parent = *(currDirectory->getParent());
                        std::cout << parent.getName() << '\n';
                    } else {
                        currDirectory->listContents();
                    }
                }
                std::cout << currDirectory->getName() << " $ ";
                std::cin >> input;
            }

        }

};