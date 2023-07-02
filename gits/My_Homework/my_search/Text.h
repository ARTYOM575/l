#include "Word.h"
#include <fstream>

class Text {
    std::string file_name;
    std::vector <Word*> words;
    bool file_exists(std::string);
    std::string liken_word(std::string ,std::ifstream& , std::ofstream &);
public:
    Text(const std::string &file_name);
    Text(){this->file_name = "lorem.txt";}
    bool split ();
    void clean();
    void print();
    void search(std::string filename);
    
};

void Text::print() {
    for (int i = 0; i < words.size() ;++i)
        std::cout << words[i]->get_word() << std::endl;
}

Text::Text(const std::string &file_name){
    this->file_name = file_name;
}

bool Text::split () {
    std::string word;
    int i = 0;
    std::ifstream file_read (this->file_name.c_str());
    if (!file_read) {
        std::cout << "Invalid name" << std::endl;
        return false;
    }
    while (file_read >> word) {
        this->words.push_back(new Word(word));
        word.clear();
    }
    file_read.close();
    return true;
}

void Text::clean() {
    for(std::vector<Word*>::iterator i  = this->words.begin(); i < this->words.end(); ++i) {
        (*i)->clean();
        if ((*i)->get_word() == "") {
            delete *i;
            this->words.erase(i);
        }
    }
}

bool Text::file_exists(std::string fileName) {
    std::ifstream file(fileName.c_str());
    if (file) {
        file.close();
        return true;
    }
    file.close();
    return false;
}

std::string Text::liken_word(std::string word,std::ifstream& file_read, std::ofstream & file_write) {
    return "";
}

void Text::search (std::string filename = "words_alpha.txt") {
    bool is_exsist;
    std::string close_word;
    std::string temp2;
    std::string temp_word;
    temp_word.clear();
    std::ifstream file_read(filename.c_str());
    std::ofstream file_write("db.txt");
    if (!file_read) {
        std::cout << "Invalid filename" << std::endl;
        return;
    }
    if (!file_write) {
        std::cout << "Don't create file error" << std::endl;
        return;
    }
    for (int i = 0; i < this->words.size(); ++i) {
        is_exsist = false;
        while (getline (file_read,temp_word)) {
            temp2 = this->words[i]->get_word();
            if (temp2 == temp_word) {
                is_exsist = true;
                //std::cout << words[i]->get_word();
                file_write << temp_word << ":" << "1" << "\n";
                temp_word.clear();
                break;
            }
            //file_write << this->words[i]->get_word() << "  " << temp_word << std::endl;
            //std::cout << temp_word;
            temp_word.clear();
        }
        if (!is_exsist) {
            close_word = liken_word(this->words[i]->get_word(),file_read,file_write);
            file_write << close_word << ":" << "1" << "\n";
        }
        //file_read.close();
        //file_read.open(filename.c_str());
        file_read.clear();
        file_read.seekg(0);
    }
    file_read.close(); 
    file_write.close();  
}
