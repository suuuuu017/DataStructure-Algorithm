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
};

