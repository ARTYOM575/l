namespace Art {
    template <typename T>
    struct d_arr {
        T* array = nullptr;
        int size = 0;
        d_arr(int size) {
            this->size = size;
            array = new T[size];
        }
        ~d_arr() {
            delete []array;
        }

        T& operator[](int index) {
            return this->array[index];
        }
        T& operator*() {
            return *array;
        }
        T& operator+(int a) {
            return this + a;
        }
        T& operator++() {
            return this + sizeof(T);
        }
    };

    template <typename T>
    d_arr<T>* contact (T* array1, T* array2,int size1, int size2) {
        d_arr<T>* ret_arr = new d_arr<T>[size1 + size2];
        int i = 0;
        for ( ;i < size1; ++i) {
            (*ret_arr)[i] = array1[i];
        }
        for (int j = 0;j < size2; ++j) {
            (*ret_arr)[i] = array2[j];
            ++i;
        }
        return ret_arr;
    }
    
    template <typename T, typename Func>
    bool every(T* array, int size,Func func) {
        for (int i = 0; i < size; ++i) {
            if (!func(array[i]))  
                return false;
        }
        return true;
    }

    template <typename T, typename Func>
    d_arr<T>* filter(T* array, int size,Func func) {
        std::vector<int> index;
        for (int i = 0; i < size; ++i) {
            if (func(array[i])) {
                index.push_back(i);
            }
        }
        size = index.size();
        d_arr<T>* ret = new d_arr<T>(size);
        for (int i = 0; i < size; ++i) {
            (*ret)[i] = array[index[i]];
        }
        return ret;
    }
    
    template <typename T, typename Func>
    d_arr<T>* forEach(T* array, int size, Func func) {
        d_arr<T>* ret = new d_arr<T>(size);
        for (int i = 0; i < size; ++i) {
            (*ret)[i] = func(array[i]);
        }
        return ret;
    }
}