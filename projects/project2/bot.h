#include <string>

struct courseInfo{
    std::string code;
    std::string name;
    std::string instructor;
};

class courseData{
private:
    int num;
    courseInfo *course;

public:
    courseData(int num);

    int readNum();

    void loadData(std::ifstream &fileList);

    void printData();
};

struct messageInfo{
    std::string time;
    std::string group;
    std::string name;
    std::string command;
    std::string commandArg;
};

class queryData{
private:
    messageInfo message;

public:
    queryData();

    void loadData(std::istream & queryText);

    void printData();

    std::string readCommand();
};

