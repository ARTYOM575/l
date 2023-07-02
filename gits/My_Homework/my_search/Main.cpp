#include "Text.h"

int main() {
    Text obj("1.txt");
    obj.split();
    obj.clean();
    //obj.print();
    obj.search("words_alpha.txt");
}