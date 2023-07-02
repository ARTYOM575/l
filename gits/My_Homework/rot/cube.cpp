#include <iostream>
#include <queue>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

std::string rotate_left (std::string& word) {
    char temp = word[0];
    word[0] = word[1];
    word[1] = word[5];
    word[5] = word[4];
    word[4] = temp;
    temp = word[2];
    word[2] = word[6];
    word[6] = word[7];
    word[7] = word[3];
    word[3] = temp;
    return word;
}

std::string rotate_right (std::string& word) { 
    char temp = word[0];
    word[0] = word[4];
    word[4] = word[5];
    word[5] = word[1];
    word[1] = temp;
    temp = word[2];
    word[2] = word[3];
    word[3] = word[7];
    word[7] = word[6];
    word[6] = temp;
    return word;
}

std::string rotate_down (std::string& word) {
    char temp = word[0];
    word[0] = word[4];
    word[4] = word[7];
    word[7] = word[3];
    word[3] = temp;
    temp = word[1];
    word[1] = word[5];
    word[5] = word[6];
    word[6] = word[2];
    word[2] = temp;
    return word;
}

std::string rotate_up (std::string& word) {
    char temp = word[0];
    word[0] = word[3];
    word[3] = word[7];
    word[7] = word[4];
    word[4] = temp;
    temp = word[1];
    word[1] = word[2];
    word[2] = word[6];
    word[6] = word[5];
    word[5] = temp;
    return word;
}

std::string substr(char* str,int ind_beg = 0,int ind_end = 0) {
    std::string ret(ind_end - ind_beg,' ');
    for (int i = ind_beg;i < ind_end; ++i) {
        ret[i] = (*str);
        ++str;
    }
    return ret;
}

std::string* split_string(const std::string& input,const int& size) {
    std::string* words = new std::string[size + 1];
    int wordIndex = 0;
    std::string word;
    for (char c : input) {
        if (c != ' ') {
            word += c;
        } else {
            words[wordIndex++] = word;
            word.clear();
        }
    }
    words[wordIndex] = word;
    return words;
}

int padding_count (const std::string& str,char pad) {
    int i = 0;
    int count = 0;
    while (str[i] != '\0') {
        if (str[i] == pad)
            ++count;
        ++i;
    }
    return count;
}

int find_back_space_from_end (const char* beg,const char* end) {
    int back_space_ind = 0;
    while (beg <= end) {
        if (*end == ' ')
            return back_space_ind;
        --end;
        ++back_space_ind;
    }
    return -1;
}

int find_front_space_form_begin (const char* beg,const char* end) {
    int back_space_ind = 0;
    while (beg <= end) {
        if (*beg == ' ')
            return back_space_ind;
        ++beg;
        ++back_space_ind;
    }
    return -1;
}

std::string substr_e_s (const std::string& str) {
    int size = str.length();
    int index = find_back_space_from_end (&str[0],&str[size - 1]);
    std::string res = "";
    if (index == -1) {
        std::cout << "error" <<std::endl;
        exit(1);
    }
    while (index) {
        res += str[size - index];
        --index;
    }
    return res;
}

std::string substr_b_s (const std::string& str) {
    int size = str.length();
    int index = find_front_space_form_begin (&str[0],&str[size - 1]);
    std::string res = "";
    if (index == -1) {
        std::cout << "error" <<std::endl;
        exit(1);
    }
    ++index;
    while (index < size) {
        res += str[index];
        ++index;
    }
    return res;
}

void generate_key (std::string& key,const int& count) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int count_rot;
    int randomIndex;
    const int around_num = 9;
    const int around_count = 5;
    char chars[] = {'R', 'L', 'D', 'U'};

    for (int i = 0; i < count; ++i) {
        count_rot = std::rand() % around_count;
        for (int j = 0; j < count_rot; ++j) {
            randomIndex = std::rand() % 4;
            key += chars[randomIndex];
            key += std::to_string(std::rand() % around_num);
            key += ",";
        }
        key += ":";
    }
}

std::string rotate(std::string& key,const std::string& word) {
    if (word == "") {
        std::cout << "!!!!!is empty!!!!!" << std::endl;
        exit(1);
    }
    std::string words = word;
    char action;
    std::vector<std::string> cubs;
    const char padding_ch = '.';
    int index_cube = 0;
    int count_cube;
    int length_words = words.length();
    int index_key = 0;
    int count_rot;
    const int cube_length = 8;
    
    if (length_words % 8 != 0) {
        count_cube = length_words / 8 + 1;
    } else {
        count_cube = length_words / 8;
    }
    generate_key (key, count_cube);
    int diferent = count_cube * 8 - length_words;
    while (diferent) {
        words += padding_ch;
        --diferent;
    }
    for (int i = 0; i < count_cube; ++i) {
        cubs.push_back(substr(&words[0] + i*cube_length,0,cube_length));
    }
    while (key[index_key] != '\0') {
        if (key[index_key] == ':') {
            ++index_cube;
            ++index_key;
            continue;
        }
        if (key[index_key] == ',') {
            ++index_key;
            continue;
        }
        action = key[index_key];
        if (action == 'R' || action == 'L' || action == 'D' || action == 'U') {
            count_rot = std::stoi(&key[index_key] + 1);
        } else {
            ++index_key;
            continue;
        }
        ++index_key;
        if (count_rot >= 4) {
            count_rot %= 4;
        }
        if (count_rot > 2) {
            if (action == 'R') {
                action = 'L';
            } else if (action == 'L') {
                action = 'R';
            } else if (action == 'D') {
                action = 'U';
            } else if (action == 'U') {
                action = 'D';
            }
            count_rot = 4 - count_rot;
            
        }
        for (int c = 0; c < count_rot; ++c) {
            if (action == 'R') {
                rotate_right(cubs[index_cube]);
            } else if (action == 'L') {
                rotate_left(cubs[index_cube]);
            } else if (action == 'D') {
                rotate_down(cubs[index_cube]);
            } else if (action == 'U') {
                rotate_up(cubs[index_cube]);
            }
        }
    }
    words.clear();
    for (int i = 0; i < cubs.size(); ++i) {
        words += cubs[i];
    }
    return words;
}

int main() {
    //const std::string ruch_key = "L1:";
    const char padding_ch = '.';
    const int cube_length = 8;
    std::string key = "";
    std::vector<std::string> cubs;
    std::vector<int> word_count;
    std::queue <std::string> result;
    std::string sentence;
    std::string temp_sentence;
    std::string line;
    std::string word;
    std::string* str_arr;
    std::ifstream file_read("words_alpha_.txt");
    int cube_count;
    int size_queue;
    int pad_ch_count;
    int space_so_far = 0;
    bool is_word_bool;
    std::cout << "input sentence    "; 
    std::getline(std::cin, sentence);
    std::cout << "sentence                              {" << sentence <<"}"<<std::endl;
    sentence = rotate (key,sentence);
    // = rotate (ruch_key,sentence)
    std::cout << "sentence  was transformed  this key   {" << key<<"}" << std::endl;
    std::cout << "it became                             {" << sentence << "}" <<std::endl;
    cube_count = sentence.length() / 8;
    if (!file_read) {
        std::cout << "file is'nt open\n";
        exit(1);
    }
    for (int i = 0; i < cube_count; ++i) {
        cubs.push_back(substr(&sentence[0] + i*cube_length,0,cube_length));
        word_count.push_back(0);
        for (int j = 0; j < cubs[i].size(); ++j) {
            if (cubs[i][j] == ' ') {
                ++(word_count[i]);
            }
        }
    }
    if (cube_count == 0) {
        std::cout << "Invalid input sentence";
        exit(1);
    }

    if (cube_count > 1) {
        if (word_count[0] == 0) {
            for (int rot_up = 0; rot_up < 4; ++rot_up) {
                rotate_up(cubs[0]);
                for (int rot_left = 0; rot_left < 4; ++rot_left) {
                    rotate_left(cubs[0]);
                    result.push(cubs[0]);
                }
            }
        } else {
            space_so_far += word_count[0];
            for (int rot_up = 0; rot_up < 4; ++rot_up) {
                rotate_up(cubs[0]);
                for (int rot_left = 0; rot_left < 4; ++rot_left) {
                    rotate_left(cubs[0]);
                    str_arr = split_string(cubs[0],word_count[0]);
                    for (int wc = 0; wc < word_count[0]; ++wc) {
                        file_read.clear();
                        file_read.seekg(0, std::ios::beg);
                        is_word_bool = false;
                        while (getline(file_read,line)) {
                            if(line == str_arr[wc]) {
                                is_word_bool = true;
                                break;
                            }
                        }
                        if (is_word_bool == false)
                            break;
                    }
                    delete[] str_arr;
                    if (is_word_bool == true) {
                        result.push(cubs[0]);
                    }
                }
            }
        }
    }
    for (int i = 1; i < cube_count - 1; ++i) {
        
        size_queue = result.size();
        while (size_queue) {
            temp_sentence.clear();
            temp_sentence = result.front(); 
            result.pop();
            for (int rot_up = 0; rot_up < 4; ++rot_up) {
                rotate_up(cubs[i]);
                for (int rot_left = 0; rot_left < 4; ++rot_left) {
                    rotate_left(cubs[i]);
                    if (word_count[i] == 0) {
                        result.push(temp_sentence + cubs[i]);
                        continue;
                    }
                    word.clear();
                    if (space_so_far > 0) 
                        word = substr_e_s (temp_sentence);
                    else 
                        word = temp_sentence;
                    word += cubs[i];
                    str_arr = split_string(word,word_count[i]);
                    for (int wc = 0; wc < word_count[i]; ++wc) {
                        file_read.clear();
                        file_read.seekg(0, std::ios::beg);
                        is_word_bool = false;
                        while (getline(file_read,line)) {
                            if(line == str_arr[wc]) {
                                is_word_bool = true;
                                break;
                            }
                        }
                        if (is_word_bool == false)
                            break;
                    }
                    delete[] str_arr;
                    if (is_word_bool == true) 
                        result.push(temp_sentence + cubs[i]);
                }
            }
            --size_queue;
        }
        space_so_far += word_count[i];
    }
    if (cube_count == 1) {
        result.push("");
    }
    size_queue = result.size();
    pad_ch_count = padding_count (cubs[cube_count - 1],padding_ch);
    while (size_queue) {
        temp_sentence.clear();
        temp_sentence = result.front();
        result.pop();
        for (int rot_up = 0; rot_up < 4; ++rot_up) {
            rotate_up(cubs[cube_count - 1]);
            for (int rot_left = 0; rot_left < 4; ++rot_left) {
                rotate_left(cubs[cube_count - 1]);
                is_word_bool = true;
                for (int i = 1; i <= pad_ch_count; ++i) {
                    if (cubs[cube_count - 1][cube_length - i] != padding_ch) {
                        is_word_bool = false;
                        break;
                    }
                }
                if (is_word_bool) {
                    word.clear();
                    if (space_so_far > 0) 
                        word = substr_e_s (temp_sentence);
                    else 
                        word = temp_sentence;
                    word += substr (&cubs[cube_count - 1][0],0,cube_length - pad_ch_count);
                    str_arr = split_string(word,word_count[cube_count - 1]);
                    for (int wc = 0; wc <= word_count[cube_count - 1]; ++wc) {
                        file_read.clear();
                        file_read.seekg(0, std::ios::beg);
                        is_word_bool = false;
                        while (getline(file_read,line)) {
                            
                            if(line == str_arr[wc]) {
                                is_word_bool = true;
                                break;
                            }
                        }
                        if (is_word_bool == false)
                            break;
                    }
                    delete[] str_arr;
                    if (is_word_bool == true) 
                        result.push(temp_sentence + substr (&cubs[cube_count - 1][0],0,cube_length - pad_ch_count));
                }
            }
        }
        --size_queue;
    }
    size_queue = result.size();
    for (int i = 0; i < size_queue; ++i) {
        std::cout << result.front() << std::endl;
        result.pop();
    }
}