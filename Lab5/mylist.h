#ifndef INC_5_LAB_MYLIST_H
#define INC_5_LAB_MYLIST_H

//template<class T>
class Stack {
public:
    struct Node {
//        T data;
        bool isFree = true;
        Node *next{nullptr};
    };

    Node *first = nullptr;
public:
    Stack() = default;

    [[nodiscard]] bool isEmpty() const {
        return first == nullptr;
    }

    Node *pop() {
        Node *top = first;
        first = first->next;
        return top;
    }

/*    void push(Node *newNode) {

        newNode->next = head;
        head = newNode;
        head->isFree = true;
        //head->next = nullptr;
    }*/
    void push(Node *newNode) {

        newNode->next = first;
        first = newNode;
        //head->next = nullptr;
    }


    Stack &operator=(const Stack &copy) = default;

    Node *operator[](int index) const {
        Node *search = first;
        for (int i = 0; i < index; i++) {
            search = search->next;
        }
        return search;
    }
};


#endif //INC_5_LAB_MYLIST_H
