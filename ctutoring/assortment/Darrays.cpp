#include <iostream>
using namespace std;

class Client{
private:
    float checkings, savings;
public:
    Client(){
        checkings = 0, savings = 0;
    }
    Client(float c,float s){
        checkings = c, savings = s;
    }
    void showData(){
        cout << "Checking Balance: ";
        printf("%.2f",checkings);
        cout << "\nSavings Balance ";
        printf("%.2f",savings);
        cout << endl;
    }
};

class Bank{
private:
    int size;
    Client* clients;
public:
    Bank(){
        size = 0;
        clients = new Client[1];
    }
    ~Bank(){
        size = 0;
        clients = nullptr;
    }
    void addClient(Client c){
        size++;//iterates size by 1
        Client templist[size+1]; //creates a temporary list with size one larger than the current list

        for(int i = 0; i < size; i++) // copies client list into templist
            templist[i] = clients[i];        

        templist[size-1] = c; //adds the new client to "end" of templist

        clients = new Client[size+1]; //resizes client list (deleting whats inside of it in the process)

        for(int i = 0; i< size; i++) //copies templist into client list
            clients[i] = templist[i];
    }
    void showData(){
        for(int i = 0; i<size;i++){
            cout << "Client " << i+1 << ":\n";
            clients[i].showData();
            cout << endl;
        }
    }

};



int main(){
    Bank chase;
    
    Client one(2010.71,9876.33);

    Client two(13.71,0);

    Client three(500,600);

    Client four(9622,20000);

    chase.addClient(one);

    cout << "After adding client 1:" << endl;

    chase.showData();

    chase.addClient(two);

    cout << "After adding client 2:" << endl;

    chase.showData();

    chase.addClient(three);

    cout << "After adding client 3:" << endl;

    chase.showData();

    chase.addClient(four);

    cout << "After adding client 4:" << endl;

    chase.showData();

    chase.~Bank();

    return 0;

}