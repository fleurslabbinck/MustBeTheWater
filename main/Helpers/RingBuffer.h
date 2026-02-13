#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <optional>

namespace gg
{
    template<typename DataType, size_t Size>
    class RingBuffer
    {
        static_assert(Size > 0, "Size must be greater than 0");
        
    public:
        RingBuffer() = default;
        ~RingBuffer() = default;
        RingBuffer(const RingBuffer&) = delete;
        RingBuffer(RingBuffer&&) = delete;
        RingBuffer& operator=(const RingBuffer&) = delete;
        RingBuffer& operator=(RingBuffer&&) = delete;

        // Enqueue new item to the back
        void Push(const DataType& item)
        {
            // Pop oldest item if buffer is full
            if (IsFull())
            {
                // Essentially pop oldest value
                IncrementIndex(m_TailIdx);
            }

            // Add item at head index
            m_Buffer[m_HeadIdx] = item;

            // Move head index to next position
            IncrementIndex(m_HeadIdx);
        }

        // Dequeue the oldest item from the front
        std::optional<DataType> Pop()
        {
            // Make sure there are items in buffer
            if (IsEmpty())
            {
                return std::nullopt;
            }

            // Move item at tail index
            DataType item = std::move(m_Buffer[m_TailIdx]);

            // Move tail index to next position
            IncrementIndex(m_TailIdx);

            return item;
        }

        // View buffer item at given index
        std::optional<DataType> ViewAtIndex(size_t index) const
        {
            if (index >= SizeUsed())
            {
                return std::nullopt;
            }

            // Find index relevant to buffer start and return item
            return m_Buffer[IndexWrappedBySize(m_TailIdx + index)];
        }

        bool IsEmpty() const
        {
            return m_HeadIdx == m_TailIdx;
        }

        bool IsFull() const
        {
            return IndexWrappedBySize(m_HeadIdx +1) == m_TailIdx;
        }

        size_t SizeUsed() const
        {
            return IndexWrappedBySize(m_HeadIdx + m_ActualSize - m_TailIdx);
        }

    private:
        static constexpr size_t m_ActualSize{Size + 1};
        size_t m_HeadIdx{};
        size_t m_TailIdx{};
        DataType m_Buffer[m_ActualSize]{};

        size_t IndexWrappedBySize(size_t value) const
        {
            return value % m_ActualSize;
        }

        // Increment index while staying within array bounds
        void IncrementIndex(size_t& index)
        {
            index = IndexWrappedBySize(index + 1);
        }
    };
}
#endif