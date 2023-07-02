#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

void Merge(u_int32_t *a, int low, int high, int mid)
{
	int i, j, k, temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
	while (i <= mid && j <= high) {
		if (a[i] < a[j]) {
			temp[k] = a[i];
			k++;
			i++;
		}
		else {
			temp[k] = a[j];
			k++;
			j++;
		}
	}
	while (i <= mid) {
		temp[k] = a[i];
		k++;
		i++;
	}
	while (j <= high) {
		temp[k] = a[j];
		k++;
		j++;
	}
	for (i = low; i <= high; i++) {
		a[i] = temp[i-low];
	}
}

void MergeSort(u_int32_t *a, int low, int high) {
	int mid;
	if (low < high) {
		mid=(low+high)/2;
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);
		Merge(a, low, high, mid);
	}
}

void MergeTextFile (std::string symbhols1,std::string symbhols2, int part) {
    std::string name1;
    std::string name2;
    std::string create_name;
    std::ifstream file_read1;
    std::ifstream file_read2;
    std::ofstream create_file;
    std::string line1;
    std::string line2;
    bool t;
    int k = 0;
    std::string command_rm;
    for (int i = 1; i <= (part / 2) * 2;i += 2) {
        ++k;
        t = true;
        name1  = "sort" + symbhols1;
        name1 += std::to_string(i) + ".txt";
        name2 = "sort" + symbhols1;
        name2 += std::to_string(i+1) + ".txt";
        file_read1.open(name1);
        file_read2.open(name2);
        create_name = "sort" + symbhols2;
        create_name += std::to_string(k) + ".txt";
        create_file.open(create_name);
        if (!file_read1) {
            std::cout << name1 <<"  file is'nt open"  <<std::endl;
            exit(1);
        }
        if (!file_read2) {
            std::cout << name2 <<"  file is'nt open"  <<std::endl;
            exit(1);
        }
        if (!create_file) {
            std::cout << create_name << "  file is'nt create"  <<std::endl;
            exit(1);
        }
        getline(file_read1,line1);
        getline(file_read2,line2);
        if(std::stol(line1) < std::stol(line2)) {
            create_file << line1;
            getline(file_read1,line1);
        } else {
            create_file << line2;
            getline(file_read2,line2);
        }
        while (t) {
            if(std::stol(line1) < std::stol(line2)) {
                create_file << '\n' << line1 ;
                if (!getline(file_read1,line1)) {
                    t = false;
                }
            }
            else {
                create_file << '\n' << line2 ;
                if (!getline(file_read2,line2)) {
                    t = false;
                }
            }
        }
        
        if (std::stol(line1) >= std::stol(line2)) 
            create_file<< '\n' << line1 ;
        else
            create_file  << '\n'<< line2;
        while (getline(file_read2, line2)) {
            create_file << '\n' << line2;
        }
        while (getline(file_read1,line1)) {
            create_file  << '\n' << line1;
        }
        file_read1.close();
        file_read2.close();
        create_file.close();
        command_rm = "rm ";
        command_rm += name1 + " " + name2;
        system(command_rm.c_str());
    }
}

int main() {
    int counter;
    const int part = 64;
    const u_int32_t size_array = 625000;
    uint32_t num;
    const u_int32_t count = 40000000;
    std::ofstream file_write("numbers.txt");
    if (!file_write) {
        std::cout << "file is'nt open" << std::endl;
        exit(1);
    }
    srand((unsigned) time(NULL));
    file_write << rand();
    for (unsigned int i = 1; i < count; ++i) {
        file_write <<'\n' << rand();
    }
    file_write.close();
    u_int32_t arr[size_array];
    std::string name1;
    std::ofstream create_file;
    std::ifstream file_read1("numbers.txt");
    std::string line;
    if (!file_read1) {
        std::cout <<  "numbers.txt file is'nt open" <<std::endl;
        exit(1);
    }
    for (int i = 1; i <= part; ++i) {
        counter = 0;
        name1 = "sort_";
        name1 += std::to_string(i);
        name1 += ".txt";
        while (counter < size_array && getline(file_read1,line)) {
            arr[counter] = std::stol(line);
            ++counter;
        }
        MergeSort (arr,0,sizeof(arr)/sizeof(arr[0]));
        create_file.open(name1);
        create_file << arr[0];
        for (int j = 1; j < counter; ++j) {
            create_file << '\n'<< arr[j] ;
        }
        create_file.close();
    }
    file_read1.close();
    std::string takiGic = "_";
    for (short i = 0; i < log(part)/log(2); ++i) {
        MergeTextFile(takiGic,takiGic + "_",part / pow(2,i));
        takiGic += "_";
    }
    system("mv sort_______1.txt Ready.txt");
}