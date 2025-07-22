
class File {
    private:
        std::string name;
        std::string contents;
    
    public:
        File(std::string name) {
            this->name = name;
            contents = "";
        }

        File(std::string name, std::string contents) {
            this->name = name;
            this->contents = contents;
        }

        std::string getName() {
            return name;
        }

        void printContents(){
            std::cout << contents << '\n';
        }

        void setContents(std::string newContents) {
            contents = newContents;
        }
};