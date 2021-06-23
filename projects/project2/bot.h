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

    void printAllData();

    std::string readCode(int i);

    std::string readInstructor(int i);

    void printData(int i);
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

    std::string readCommandArg();

    std::string readTime();
};

struct adminName{
    std::string name;
};

class groupList{
public:
    std::string name;
    int numOfAdmin;
    adminName *adminList;

    groupList();

    adminName * admin(int numOfAdmin);
};

class groupData{
private:
    int numOfGroup;
    std::string detailedList;
    groupList *group;

public:
    groupData(int numofGroup, std::string detailedListDir);

    void loadData(std::ifstream &fileList);

    void loadDetailedAdmin();

    std::string readGroupName(int i);

    void printData();
};

