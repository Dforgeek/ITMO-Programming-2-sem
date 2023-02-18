#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdexcept>
#include <variant>

template <std::size_t BlocksAmount = 4096>
struct Pool {
    template <typename T>
    class Allocator {
    private:
        struct Header {
            Header* next;
        };
        union Block {
            Header* header;
            T data;
        };

    public:
        using value_type							 = T;
        using size_type								 = std::size_t;
        using difference_type						 = std::ptrdiff_t;
        using propagate_on_container_move_assignment = std::true_type;

        Allocator() {
            m_pool_memory = (Block*) ::malloc(m_block_size * m_blocks_amount);
            m_pool_start  = m_pool_memory + 0;
            m_pool_end	  = m_pool_start + m_blocks_amount;
            m_stack_top	  = reinterpret_cast<Header*>(m_pool_start);
            m_stack_top->next = nullptr;
        }

        template <class U>
        constexpr Allocator(const Allocator<U>&) noexcept {
        }

        ~Allocator() {
            ::free(m_pool_memory);
        }
        [[nodiscard]] T* allocate(const std::size_t n = 1) {
            T* result = nullptr;
            for (std::size_t i = 0; i < n; ++i) {
                if (m_stack_top == nullptr || n > m_blocks_amount) {
                    throw std::bad_alloc{};
                }
                if (i == 0) {
                    result = reinterpret_cast<T*>(m_stack_top);
                }
                if (m_stack_top->next == nullptr) {
                    Block* next_block =
                        reinterpret_cast<Block*>(m_stack_top) + 1;
                    Header* next_header = reinterpret_cast<Header*>(next_block);
                    next_header->next	= nullptr;

                    if (m_pool_end > next_block) {
                        m_stack_top->next = next_header;
                    }
                }
            }

            return result;
        }
        void deallocate(T* p, std::size_t n) {
            Block* block_to_free = (Block*) p;

            if (m_pool_start > block_to_free ||
                (block_to_free + n) > m_pool_end) {

                throw std::invalid_argument(
                    "Pointer does not refer to this allocator");
            }
            for (std::size_t i = 0; i < n; ++i) {
                Block* freed_block = block_to_free++;
                Header* new_header = reinterpret_cast<Header*>(freed_block);

                new_header->next = m_stack_top;
                m_stack_top		 = new_header;
            }
        }
        template <class U>
        using other = Allocator<U>;

        template <class U>
        bool operator==(const Allocator<U>& t_alloc) {
            return (m_pool_start == t_alloc.m_pool_start &&
                    m_pool_end == t_alloc.m_pool_end);
        }

        template <class U>
        bool operator!=(const Allocator<U>& t_alloc) {
            return !(*this == t_alloc);
        }

    private:
        static constexpr std::size_t npos{static_cast<std::size_t>(-1)};

        std::size_t m_blocks_amount{BlocksAmount};
        std::size_t m_block_size{sizeof(Block)};

        Block* m_pool_memory{nullptr};

        Block* m_pool_start{nullptr};
        Block* m_pool_end{nullptr};

        Header* m_stack_top{nullptr};
    };
};

#endif // ALLOCATOR_H