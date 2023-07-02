namespace ART {
    template <typename T> 
class vector {
private:
    T* head = nullptr;
    long int size = 0;
    long int capacity = 0;
    
    class iterator_v {
        T* iter = nullptr;
    public:
        iterator_v() {};
        iterator_v(T* node) :iter(node){}
        bool operator==(T* ptr) const {
            return iter == ptr;
        }
        bool operator!=(T* ptr) const {
            return !(iter == ptr);
        }
        T& operator*() const {
            if (iter != nullptr) 
                return *iter;
            else
                exit(1);
        }
        T* operator->() const {
            return iter;
        }
        iterator_v operator++() {
            ++iter;
            return *this;
        }
        iterator_v operator++(int) {
            iterator_v temp = *this;
            operator++();
            return temp;
        }
        iterator_v operator--() {
            --iter;
            return iter;
        }
        iterator_v operator--(int) {
            iterator_v temp = *this;
            operator--();
            return temp;
        }
        iterator_v& operator=(T* node) {
            iter = node;
            return *this;
        } 
        T* get_node() const {return this->iter;}
        void next_();
        void previouse_();
        
    };
    
    void increase_space();
public:
    friend  class iterator_v;
    using iterator = iterator_v;
    vector ();
    vector (long int size);
    vector(T* array,long int size);
    

    void push_back (T value);
    void pop_back (){--(this->size);}
    void pop (long int position);
    void insert (const T &value, long int position);

    T* begin() const {return head;}
    T* end() const {return (head + size - 1);}
    void resize (long int size);
    long int get_size () const{return this->size;}
    void print();
    T &operator[](long int i);
    ~vector() {delete[] this->head;}
};

template <typename T>
vector <T>::vector(T* array,long int size) {
    this->size = size;
    this->capacity = size * 2;
    this->head = new T[this->capacity];
    for (int i = 0;i < size; ++i) {
        head[i] = array[i];
    }
}

template <typename T> 
vector <T>::vector(long int size) {
    this->size = size;
    this->capacity = size * 2;
    this->head = new T[this->capacity];
}

template <typename T>
vector <T>::vector() {
    capacity = 100;
    head = new T[capacity];
    size = 0;
}

template <typename T>
void vector <T>::increase_space() {
    this->capacity += this->capacity * 2;
    T * temp_head = new T[this->capacity];
    for (long int i = 0; i < this->size; ++i) {
        temp_head[i] = this->head[i];
    }
    delete[] (this->head);
    this->head = temp_head;
}

template <typename T>
void vector<T>::push_back(T number) {
    if (size < capacity) {
            head[size] = number;
            ++(this->size);
        }
        else {
            increase_space();
            head[this->size] = number;
            ++(this->size);
        }
}

template <typename T> 
void vector<T>::pop(long int position) {
    if (position >= this->size || position < 0) {
        std::cout << "Invalid position  "<<position<<
        "  there is no such position" << std::endl;
        return;
        // exit(1);
    }
    for (long int i = position;i < this->size; ++i) {
        this->head[i] = this->head[i + 1];
    }
    --(this->size);
}

template <typename T> 
void vector <T>::insert (const T &number,long int position) {
    if (position >= this->size || position < 0) {
        std::cout << "Invalid position  "<<number<<
        "  element is'nt added" << std::endl;
        return;
        // exit(1);
    }
    if (size >= capacity) 
        increase_space();
    const int count_for = size-position;
    for (long int i = 0; i < count_for;++i) {
        this->head[this->size - i] = this->head[this->size - i - 1];
    }
    this->head[position] = number;
    ++(this->size);
}

template <typename T> 
void vector <T>::resize (long int size) {
    const int plus_size = 1000;
    if (size <= this->capacity) {
        this->size = size;
        return;
    }
    this->capacity = size + plus_size;
    T* temp = new T[this->capacity];
    for (int i = 0;i < this->size;++i) {
        temp[i] = this->head[i];
    }
    this->size = size;
    delete[] (this->head);
    this->head = temp;
}

template <typename T>
T &vector<T>::operator[](long int i) {
    try {
        if (i < 0 || i >= this->size) 
            throw "Invalid index";
    } catch(const char* messing) {
        std::cerr << messing << '\n';
        exit(1);
    }
    return this->head[i];
}

template <typename T>
void vector <T>::print() {
    for (int i = 0; i < size; ++i) {
        std::cout << head[i] << "  ";
    }
}

template <typename T> 
void vector <T>::iterator_v::next_() {
    if (iter != nullptr && (iter - head) >= 0 && (iter - head) < size) {
        ++iter;
    } else 
        iter = nullptr;
}

template <typename T> 
void vector <T>::iterator_v::previouse_() {
    if (iter != nullptr && (iter - head) > 0 && (iter - head) < size) {
        --iter;
    } else 
        iter = nullptr;
}
}
