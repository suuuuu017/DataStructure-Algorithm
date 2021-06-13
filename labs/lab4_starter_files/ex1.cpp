#include <iostream>
#include <cstdlib>
using namespace std;

// Classes for exception types. They are just dummy types for you to use when
// handling expections.
// TODO: Define needed classes for exception.
struct costumeNeeded{
    int costume;
};

struct gunNeeded{
    int gun;
};

struct bulletNeeded{
    int bullet;
};

struct closeO{
};

struct closeY{
};

costumeNeeded costumeN;
gunNeeded gunN;
bulletNeeded bulletN;

// EFFECTS: Check whether there are enough costumes in Omori's Costume Store. If not, throw
//          a exception.
void buy_costumes(int num_scenes, int costume_remain)
{
    // TODO:
    int cmp = costume_remain - num_scenes;
    if(cmp < 0){
        costumeN.costume = cmp * (-1);
        throw costumeN;
    }
}

// EFFECTS: Check whether there are enough guns in Yamazaki's Model Shop. If not, throw
//          a exception
void buy_guns(int num_scenes, int guns_remain)
{
    // TODO:
    int cmp = guns_remain - 2 * num_scenes;
    if(cmp < 0){
        gunN.gun = cmp * (-1);
        throw gunN;
    }
}

// EFFECTS: Check whether there are enough bullets in Yamazaki's Model Shop. If not, throw
//          a exception.
void buy_bullets(int num_scenes, int bullets_remain)
{
    // TODO:
    int cmp = bullets_remain - 100 * num_scenes;
    if(cmp < 0){
        bulletN.bullet = cmp * (-1);
        throw bulletN;
    }
}
// EFFECTS: Check if Omori's Costume Store is open. If it is open, then go on to buy flour 
//          and eggs. If it is closed, throw a exception.
void visit_Omori(bool Omori_status, int num_scenes, int costume_remain)
{
    // TODO:
    if(!Omori_status){
        closeO close;
        throw close;
    }
    else{
        buy_costumes(num_scenes, costume_remain);
    }
}

// EFFECTS: Check if Yamazaki's Model Shop is open. If it is open, then go on to buy guns.
//          If it is closed, throw a exception.
void visit_Yamazaki(bool Yamazaki_status, int num_scenes, int guns_remain, int bullets_remain)
{
    // TODO:
    if(!Yamazaki_status){
        closeY close;
        throw close;
    }
    else{
        buy_guns(num_scenes, guns_remain);
        buy_bullets(num_scenes, bullets_remain);
    }
}



int main(int argc, char* argv[])
{
    int num_scenes;           // number of scenes Haruhi wants to make.
    bool Omori_status;    // whether Omori is open or closed. 1 for open and 0 for closed.
    bool Yamazaki_status;    // whether Yamazaki is open or closed. 1 for open and 0 for closed.
    int costume_remain;        // number of costumes remaining in Omori's Costume Store.
    int guns_remain;      // number of guns remaining in Yamazaki's Model Shop.
    int bullets_remain;     // number of bullets remaining in Yamazaki's Model Shop.
    
    //TODO: 
    // Read all the above parameters from the program arguments
    if(argc == 7){
        num_scenes = atoi(argv[1]);
        Omori_status = atoi(argv[2]);
        Yamazaki_status = atoi(argv[3]);
        costume_remain = atoi(argv[4]);
        guns_remain = atoi(argv[5]);
        bullets_remain = atoi(argv[6]);
    }
    else{
        return 1;
    }
    
    // If any expception happens, flag will be changed to 0.
    bool flag = 1;

    // They will first visit Omori and then visit Yamazaki. If any exception happens, 
    // their buying process will end.
    cout << "We visit Omori's Costume Store first..." << endl;
    try 
    {
        // TODO: 
        visit_Omori(Omori_status, num_scenes, costume_remain);
        cout << "We've bought enough costumes! I can't wait before Miss Asahina wears them! Then we visit Yamazaki's Model Shop..." << endl;
        try
        {
            // TODO: 
            visit_Yamazaki(Yamazaki_status, num_scenes, guns_remain, bullets_remain);
            cout << "We've also bought enough guns and bullets! We can start the movies now! But Miss Asahina's nightmare is coming." << endl;
        }
        catch( closeY )
        {
            cout << "Yamazaki's Model Shop is closed!" << endl;
            flag = 0;
        }
        catch(struct gunNeeded)
        {
            cout << "Guns in Yamazaki's Model Shop are not enough. We still need " << gunN.gun << " more." << endl;
            flag = 0;
        }
        catch(struct bulletNeeded )
        {
            cout << "Bullets in Yamazaki's Model Shop are not enough. We still need " << bulletN.bullet << " more." << endl;
            flag = 0;
        }  
    }
    catch( closeO )
    {
        cout << "Omori's Costume Store is closed!" << endl;
        flag = 0;
    }
    catch(struct costumeNeeded )
    {
        cout << "Costumes in Omori's Costume Store are not enough. We still need " <<  costumeN.costume  << " more." << endl;
        flag = 0;
    }

    if (!flag)
        cout << "We have to wait longer before we get started. Fortunately, Miss Asahina can have more peaceful days." << endl;

    return 0;
}
