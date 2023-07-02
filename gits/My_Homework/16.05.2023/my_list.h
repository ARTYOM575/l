namespace ART {
    template <typename T> 
    class list {
        long size = 0;
        class Node {
            T value;
            Node* next = nullptr;
            Node* parent = nullptr;        
            Node();
            Node(T);
        public:
            friend class iterator_l;
            friend class list;
        };
        class iterator_l {
            Node* iter = nullptr;
        public:
            iterator_l() {};
            iterator_l(Node* node) :iter(node){}

            bool operator==(Node* ptr) const {
                return iter == ptr;
            }
            bool operator!=(Node* ptr) const {
                return !(iter == ptr);
            }
            T& operator*() const {
                if (iter != nullptr) 
                    return iter->value;
                else
                    exit(1);
            }
            T* operator->() const {
                return iter;
            }
            iterator_l operator++() {
                if (iter != nullptr) 
                    iter = iter->next;
                return iter;
            }
            iterator_l operator++(int) {
                iterator_l temp = *this;
                operator++();
                return temp;
            }
            iterator_l operator--() {
                if (iter != nullptr) 
                    iter = iter->parent;
                return iter;
            }
            iterator_l operator--(int) {
                iterator_l temp = *this;
                operator--();
                return temp;
            }
            iterator_l& operator=(Node* node) {
                iter = node;
                return *this;
            } 

            Node* get_node() const {return this->iter;}
            void next_();
            void previouse_();
        };
        Node* head = nullptr;
        Node* tail = nullptr;
    public:
        using iterator = iterator_l;
        list();
        list(T value);

        void push_back (T value);
        void pop_back ();
        void insert (const T& value, long int position);
        
        Node* search (T value);

        void set_value (Node* node, T value) {
            if(node != nullptr)
                node->value = value;
            else {
                std::cout << "Invalid Node" << std::endl;
                exit(1);
            }
        }

        T get_value (Node* node) {return node->value;}
        Node* get_head() {return this->head;}
        Node* get_tail() {return this->tail;}
        long get_size() {return this->size;}
        Node* begin() const {return this->head;}
        Node* end() const {return this->tail;}
    };

    template <typename T>
    list<T>::Node::Node() {
        next = nullptr;
        parent = nullptr;
    }

    template <typename T>
    list<T>::Node::Node(T value) {
        this->value = value;
        next = nullptr;
        parent = nullptr;
    }

    template <typename T> 
    void list<T>::iterator_l::next_() {
        if (iter == nullptr) {
            std::cout << "Next does not exist" <<std::endl;
            return;
        }
        iter = iter->next;
    }

    template <typename T>
    void list<T>::iterator_l::previouse_() {
        if (iter == nullptr) {
            std::cout << "Previose does not exist" <<std::endl;
            return;
        }
        iter = iter->parent;
    }

    template <typename T>
    list<T>::list() {
        ++size;
        head = new Node;
        tail = head;
    }

    template <typename T>
    list<T>::list(T value) {
        ++size;
        head = new Node(value);
        tail = head;
    }

    template <typename T>
    void list<T>::push_back(T value) {
        ++size;
        Node* temp = new Node(value);
        tail->next = temp;
        temp->parent = tail;
        this->tail = temp;
    }

    template <typename T> 
    void list<T>::insert(const T &value,long int position) {
        if (position < 0 || position >= size) {
            std::cout << "Invalid position" << std::endl;
            return;
        }
        if (position == 0) {
            Node* temp = new Node(value);
            temp->next = head;
            head->parent = temp;
            head = temp;
            return;
        }
        Node* temp;
        if (position <= (size - 1)/2) {
            temp = head;
            while (position) {
                temp = temp->next;
                --position;
            }   
        }
        else {
            temp = tail;
            position = (size - 1) - position;
            while (position) {
                temp = temp->parent;
                --position;
            }            
        }
        Node* temp2 = new Node(value);
        temp2->next = temp;
        temp2->parent = temp->parent;
        temp->parent->next = temp2;
        temp->parent = temp2;
        //list<T>::iterator it(head);
        //while (it != nullptr && position >= 0) {
        //    ++it;
        //    --position;
        //    if (!position) {
        //        Node* temp = new Node(value);
        //        if(it.get_node() == nullptr) {
        //            tail->next = temp;
        //            temp->parent = tail;
        //            tail = temp;
        //            return;
        //        } else {
        //            temp->next = it.get_node();
        //            temp->parent = it.get_node()->parent;
        //            it.get_node()->parent->next = temp;
        //            it.get_node()->parent = temp;
        //            return;
        //        }
        //    }
        //}
        //std::cout << "Invalid position  value is'nt added";
        //exit(1);
    }

    template<class T> 
    typename ART::list<T>::Node *ART::list<T>::search(T value) {
        list<T>::iterator it(head);
        while (it != nullptr) {
            if (it.get_node()->value == value) 
                return it.get_node();
            ++it;
        }
        std::cout << "element is missing"<< std::endl;
        exit(1);
    }

    template <typename T>
    void list<T>::pop_back() {
        if (this->tail == this->head) {
            --size;
            head->~Node();
            this->~list();
            return;
        }
        --size;
        Node* temp = this->tail;
        this->tail = this->tail->parent;
        temp->~Node();
    }
}