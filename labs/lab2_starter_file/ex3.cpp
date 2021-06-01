#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    // TODO: complete struct
    char name[16] = {};
    int score[3] = {0};
    int totalScore(){
        int total = 0;
        for (int i = 0; i < 3 ; i++){
            total = total + score[i];
        }
        return total;
    }
} Soldier;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    if ((*(Soldier*)p1).totalScore() < (*(Soldier*)p2).totalScore()) {
        return 1;
    }
    else if ((*(Soldier*)p1).totalScore() ==  (*(Soldier*)p2).totalScore()) {
        return 0;
    }
    else
        return -1;
}

int main() {
    // TODO: read input
    int size;
    cin >> size;
    Soldier rank[size];
    for (int i = 0; i < size; i++){
        cin >> rank[i].name;
        for (int j = 0; j < 3; j ++) {
            cin >> rank[i].score[j];
        }
    }
    // TODO: sort array with qsort()
    qsort(rank, size, sizeof(Soldier), compare);
    // TODO: print result
    for (int i = 0; i < size; i++){
        cout << rank[i].name << " ";
        for (int j = 0; j < 3; j ++){
            cout << rank[i].score[j] << " ";
        }
        cout << endl;
    }
    return 0;
}