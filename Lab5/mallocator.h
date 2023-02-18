#include <iostream>
#include <cassert>


template<class T, size_t TotalElems>
class Mollocator {
private:
    struct Header {
        Header *next;
    };
    union Chunk {
        Header *header;
        T data;
    };

    std::size_t m_chunkAmount{TotalElems};
    std::size_t m_chunkSize = sizeof(T);

    Chunk *m_memory{nullptr};
    Chunk *m_start{nullptr};
    Chunk *m_end{nullptr};

    Header *m_stackTop{nullptr};

public:
    //TYPE DEFINITIONS
    typedef std::size_t size_type;
    typedef T *pointer;
    typedef T value_type;


    template<class U>
    struct rebind {
        typedef Mollocator<U, TotalElems> other;
    };

    Mollocator() {
        m_memory = (Chunk *) malloc(m_chunkSize * m_chunkAmount);
        m_start = m_memory + 0;

        m_end = m_start + m_chunkAmount;
        m_end->header = nullptr;
        m_stackTop = reinterpret_cast<Header *>(m_start);
        m_stackTop->next = nullptr;
    }


    Mollocator(const Mollocator &copy) {
        m_chunkAmount = copy.m_chunkAmount;
        m_chunkSize = copy.m_chunkSize;
        m_memory = (Chunk *) malloc(m_chunkSize * m_chunkAmount);
        m_start = copy.m_start;
        m_end = copy.m_end;
        m_stackTop = copy.m_stackTop;
        m_stackTop->next = nullptr;
    }

    /*   ~Mollocator() {
           free(m_memory);
       }*/


    [[nodiscard]] pointer allocate(const std::size_t n) {
        assert(n != 0 && "n cannot be zero!");
        pointer freePosition = nullptr;

        assert(m_stackTop != nullptr && "The pool allocator is full");
        assert(n <= m_chunkAmount && "Can't allocate more than planned");
        freePosition = reinterpret_cast<pointer>(m_stackTop);



        Chunk *nextChunk = reinterpret_cast<Chunk *>(m_stackTop) + 1;
        Header *nextHead = reinterpret_cast<Header *>(nextChunk);


        if (m_end > nextChunk) {
            m_stackTop->next = nextHead;
            nextHead->next = nullptr;}

        return freePosition;
    }


    void deallocate(pointer ptr, size_type n) {
        auto *blockToFree = (Chunk *) ptr;

        assert(m_start <= blockToFree && "Pointer does not refer to this allocator");
        assert((blockToFree + n) <= m_end && "Pointer does not refer to this allocator");

        Chunk *freeBlock = blockToFree++;
        auto *newHead = reinterpret_cast<Header *>(freeBlock);
        newHead->next = m_stackTop;
        m_stackTop = newHead;

    }


};



