const int MAX_SIZE = 100; // Maximum capacity of the queue

template<typename T>
class Queue {
private:
    T data[MAX_SIZE];
    int front;
    int rear;
    int size;

public:
    Queue() {
        front = 0; // Initialize the front index
        rear = -1; // Initialize the rear index
        size = 0; // Initialize the queue with size 0
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == MAX_SIZE;
    }

    void enqueue(const T& value) {
        if (isFull()) {
            // Handle queue overflow condition
            cout << "Queue overflow!" << endl;
            return;
        }

        rear = (rear + 1) % MAX_SIZE; // Increment rear index circularly
        data[rear] = value; // Add element to the rear of the queue
        size++; // Increment the size
    }

    T dequeue() {
        if (isEmpty()) {
            // Handle queue underflow condition
            cout << "Queue underflow!" << endl;
            return T(); // Return a default value of type T
        }

        T frontElement = data[front]; // Get the front element of the queue
        front = (front + 1) % MAX_SIZE; // Increment front index circularly
        size--; // Decrement the size

        return frontElement;
    }

    T frontValue() {
        if (isEmpty()) {
            // Handle empty queue condition
            cout << "Queue is empty!" << endl;
            return T(); // Return a default value of type T
        }

        return data[front]; // Return the front element of the queue
    }
};
int main() {
    Queue<int> queu;
    queu.enqueue(20);
}