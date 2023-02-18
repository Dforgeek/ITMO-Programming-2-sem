#include <cassert>
#include <cmath>

template<class T>
class RingBuffer {
private:
    T *m_data, *m_front, *m_back;
    int m_capacity, m_length;

public:
    RingBuffer() {
        m_capacity = 0;
        m_data = nullptr;
        m_front = &m_data[0];
        m_back = &m_data[0];
        m_length = 0;
    }

    explicit RingBuffer(int length) {
        assert(length > 0 && "RingBuffer constructor error: length can't be negative");
        m_capacity = length;
        m_data = new T[length];
        m_front = &m_data[0];
        m_back = &m_data[0];
        m_length = 0;
    }

    ~RingBuffer() {
        delete[] m_data;
    }

    T &operator[](int index) {
        if (index >= 0) {
            return m_data[index % m_capacity];
        } else {
            return m_data[std::abs(m_capacity + index) % m_capacity];
        }
    }

    void push_back(T val) {
        *m_back = val;
        if (m_back == &m_data[m_capacity - 1]) {
            m_back = &m_data[0];
        } else {
            m_back++;
        }

        //pntr control
        if (m_length == m_capacity) {
            if (m_front == &m_data[m_capacity - 1]) {
                m_front = &m_data[0];
            } else {
                m_front++;
            }
        } else {
            m_length++;
        }

    }

    void pop_back() {
        //pntr control
        if (m_length == 0) {
            m_front = &m_data[0];
            m_back = &m_data[0];
            return;
        }


        if (m_back == &m_data[0]) {
            m_back = &m_data[m_capacity - 1];
        } else {
            m_back--;
        }
        *m_back = T();
        m_length--;
    }

    void push_front(T val) {
        if (m_front == &m_data[0]) {
            m_front = &m_data[m_capacity - 1];
        } else {
            m_front--;
        }
        *m_front = val;

        //pntr control
        if (m_length == m_capacity) {
            if (m_back == &m_data[0]) {
                m_back = &m_data[m_capacity - 1];
            } else {
                m_back--;
            }
        } else {
            m_length++;
        }
    }

    void pop_front() {
        //pntr control
        if (m_length == 0) {
            m_front = &m_data[0];
            m_back = &m_data[0];
            return;
        }


        *m_front = T();
        if (m_front == &m_data[m_capacity - 1]) {
            m_front = &m_data[0];
        } else {
            m_front++;
        }

        m_length--;
    }

    void changeCapacity(int newCap) {
        if (newCap > m_capacity) {
            T tempData = new T[newCap];
            memcpy(tempData, m_data, m_capacity);
            m_capacity = newCap;

        } else if (newCap < m_capacity) {
            T tempData = new T[newCap];
            if (m_back > newCap) {
                m_back = &m_data[m_capacity - 1];
            }
            if (m_front > newCap) {
                m_front = &m_data[m_capacity - 1];
            }
            memcpy(tempData, m_data, newCap);
            m_capacity = newCap;
        }
    }

    // итератор этого дряного буфера
    class Iter {
    private:
        T *m_value;
    public:
        explicit Iter(T *val) : m_value(val) {}

        Iter operator+(int i) {
            m_value += i;
            return *this;
        }

        Iter operator-(int i) {
            m_value -= i;
            return *this;
        }

        Iter &operator++() {
            ++m_value;
            return *this;
        }

        Iter operator--() {
            --m_value;
            return *this;
        }

        Iter &operator=(T *i) {
            m_value = i;
            return *this;
        }

        T &operator*() const {
            return *m_value;
        }

        T *operator->() const {
            return m_value;
        }

        bool operator==(const Iter &i) {
            return this->m_value = i.m_value;
        }

        bool operator!=(const Iter &i) {
            return this->m_value != i.m_value;
        }

        bool operator>(const Iter &i) {
            return this->m_value > i.m_value;
        }

        bool operator<(const Iter &i) {
            return this->m_value < i.m_value;
        }

        bool operator>=(const Iter &i) {
            return this->m_value >= i.m_value;
        }

        bool operator<=(const Iter &i) {
            return this->m_value <= i.m_value;
        }
    };

    Iter begin() {
        return Iter(m_data);
    }

    Iter end() {
        return Iter(m_data+m_capacity);
    }
};