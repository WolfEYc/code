#include <bits/stdc++.h>
using namespace std;

class Avatar{
private:
    string name;
    int XP, HP;
public:
    Avatar(string n, int x, int h){
        name = n;
        XP = x;
        HP = h;
    }
    virtual void print(){
        cout << name << " is level " << XP << " with " << HP << " HP" << endl;
    }
    void damage(int dmg){
        HP -= dmg;
    }
    string getName(){
        return name;
    }
};

class Fighter : public Avatar{
private:
    int atk;
public:
    Fighter(string n, int x, int h, int a) : Avatar(n,x,h){
        atk = a;
    }
    void attack(Avatar& a){
        a.damage(atk);
        cout << getName() << " attacks " << a.getName()
         << " and deals "<< atk <<" damage!" << endl;
    }

    void print() {
        Avatar::print();
        cout << getName() << " has an attack power of " << atk << endl;
    }

};

int main(){
    Avatar George("George",15,25);
    Fighter Billy("Billy",12,35,5);

    cout << endl << "Displaying Original Objects:" << endl;
    George.print();
    Billy.print();
    cout << endl;

    cout << "Test attack() function:" << endl;
    Billy.attack(George);
    cout << "Result of Attack:" << endl;
    George.print();
    cout << endl;
    
    cout << "Test attack() function:" << endl;
    Billy.attack(Billy);
    cout << "Result of Attack:" << endl;
    Billy.print();
    cout << endl;

    return 0;
}
