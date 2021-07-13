#include "phonebook.hpp"

using namespace std;

int main(){

    phonebook pbook(5);

    pbook.addContact("john", "666-666-6666", "john@gmail.com");

    phonebook copypbook = pbook;

    copypbook.print();

    return 0;
}
