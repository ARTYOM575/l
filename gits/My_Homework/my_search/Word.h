#include <iostream>
#include <vector>
#include <cstring>
class Word {
    std::string word;
    std::string get_word() const {return this->word;}
    void set_word(const std::string& word) {this->word = word;}
    Word(std::string word);
    Word(){};
    void clean();
public:
    friend class Text;
};

Word::Word(std::string word) {
    this->word = word;
}

void Word::clean () {
    char charter;
    std::string result;
    result.clear();
    int i = 0;
    while (this->word[i] != '\0') {
        charter = word[i];
        if (charter >= 65 && charter <=90) {
            charter += + 32;
        }
        if (charter >= 97 && charter <= 122) {
            result += charter;
        }
        ++i;
    }
    this->word = result;
}
