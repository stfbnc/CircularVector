#ifndef __CIRCULAR_VECTOR_H__
#define __CIRCULAR_VECTOR_H__

#include <vector>
#include <algorithm>

template<class T>
class CircularVector
{
public:
    explicit CircularVector(size_t size)
    {
        buffer_size = size;
        buffer.reserve(size);
    }

    virtual ~CircularVector() {}

    // check for elements destruction if pointers
    void push_back(const T& value)
    {
        current_idx = ((current_idx + 1) % buffer_size);
        if(current_size < buffer_size)
        {
            buffer.push_back(value);
            current_size++;
        }
        else
        {
            buffer.at(current_idx) = value;
        }
    }
    
    T& back()
    {
        return buffer.at(current_idx);
    }

    const T& back() const
    {
        return buffer.at(current_idx);
    }

    T& front()
    {
        return at(0);
    }

    const T& front() const
    {
        return at(0);
    }

    T& at(size_t idx)
    {
        if(((current_size < buffer_size) && (idx > current_idx)) || (idx >= buffer_size))
        {
            throw std::out_of_range(std::string("Trying to get element at index ") + std::to_string(idx) + std::string(", but vector has size ") + std::to_string(current_size));
        }

        size_t circ_idx = seq_id_to_circ_id(idx);
        return buffer.at(circ_idx);
    }

    const T& at(size_t idx) const
    {
        if(((current_size < buffer_size) && (idx > current_idx)) || (idx >= buffer_size))
        {
            throw std::out_of_range(std::string("Trying to get element at index ") + std::to_string(idx) + std::string(", but vector has size ") + std::to_string(current_size));
        }

        size_t circ_idx = seq_id_to_circ_id(idx);
        return buffer.at(circ_idx);
    }

    size_t size() const
    {
        if(current_size < buffer_size)
        {
            return current_size;
        }
        else
        {
            return buffer_size;
        }
    }

    size_t capacity() const
    {
        return buffer_size;
    }

    bool empty() const
    {
        return (current_size == 0);
    }

    bool is_full() const
    {
        return (current_size == buffer_size);
    }

    // user should delete first if it is a pointer
    void clear()
    {
        buffer.clear();
        current_idx = -1;
        current_size = 0;
    }

    size_t find(const T& value) const
    {
        size_t id = std::find(buffer.begin(), buffer.begin() + size(), value) - buffer.begin();
        if(id >= size())
        {
            return size();
        }
        else
        {
            return circ_id_to_seq_id(id);
        }
    }

    size_t find_nearest(const T& value) const
    {
        size_t id = size();
        for(size_t i = 0; i < current_size; i++)
        {
            if(at(i) > value)
            {
                id = i;
                break;
            }
        }

        return id;
    }

    // check for elements destruction if pointers
    bool insert(size_t idx, const T& value)
    {
        if(idx > current_size)
        {
            throw std::out_of_range(std::string("Trying to insert an element at index ") + std::to_string(idx) + std::string(", but vector has size ") + std::to_string(current_size));
        }

        bool inserted = false;

        // if the buffer is still not full, do a classical insert
        if(current_size < buffer_size)
        {
            buffer.insert(buffer.begin() + idx, value);
            current_size++;
            current_idx = ((current_idx + 1) % buffer_size);
            inserted = true;
        }
        else
        {
            // if the new value is to be inserted before the first element of the buffer, skip it
            if(idx != 0)
            {
                // if idx is equal to buffer_size, overwrite the first element of the buffer
                if(idx == buffer_size)
                {
                    current_idx = ((current_idx + 1) % buffer_size);
                    buffer.at(current_idx) = value;
                }
                else
                {
                    size_t circ_idx = seq_id_to_circ_id(idx);
                    if(circ_idx <= current_idx)
                    {
                        // move the elements from circ_idx to current_idx one place to the right
                        for(int i = current_idx; i >= static_cast<int>(circ_idx); i--)
                        {
                            buffer.at((i + 1) % buffer_size) = buffer.at(i);
                        }
                        buffer.at(circ_idx) = value;
                        current_idx = ((current_idx + 1) % buffer_size);
                    }
                    else
                    {
                        // move the elements from current_idx + 2 to circ_idx - 1 one place to the left
                        for(int i = (current_idx + 2); i <= (static_cast<int>(circ_idx) - 1); i++)
                        {
                            buffer.at(i - 1) = buffer.at(i);
                        }
                        buffer.at(circ_idx - 1) = value;
                    }
                }

                inserted = true;
            }
        }

        return inserted;
    }

    // user should delete first if it is a pointer
    bool erase(size_t idx)
    {
        
    }

    // user should delete first if it is a pointer
    bool erase(const T& value)
    {
        if(find(value) == size())
        {
            return false;
        }


    }

    T& operator[](size_t idx)
    {
        return at(idx);
    }

    const T& operator[](size_t idx) const
    {
        return at(idx);
    }

    // user should delete first if it is a pointer
    CircularVector<T>& operator=(const CircularVector<T>& vec)
    {
        if(capacity() != vec.capacity())
        {
            throw std::range_error(std::string("Trying to compare two vectors with different capacities"));
        }

        clear();
        for(size_t i = 0; i < vec.size(); i++)
        {
            push_back(vec.at(i));
        }

        return *this;
    }

    bool operator==(const CircularVector<T>& vec)
    {
        if(size() != vec.size())
        {
            throw std::range_error(std::string("Trying to compare two vectors with different sizes"));
        }

        bool equals = true;
        for(size_t i = 0; i < size(); i++)
        {
            if(at(i) != vec.at(i))
            {
                equals = false;
                break;
            }
        }

        return equals;
    }

    bool operator!=(const CircularVector<T>& vec)
    {
        if(size() != vec.size())
        {
            throw std::range_error(std::string("Trying to compare two vectors with different sizes"));
        }

        bool not_equals = false;
        for(size_t i = 0; i < size(); i++)
        {
            if(at(i) != vec.at(i))
            {
                not_equals = true;
                break;
            }
        }

        return not_equals;
    }
private:
    std::vector<T> buffer;
    size_t buffer_size {0};
    int current_idx {-1};
    size_t current_size {0};

    size_t circ_id_to_seq_id(size_t circ_id) const
    {
        if(current_size < buffer_size)
        {
            return circ_id;
        }
        else
        {
            return ((buffer_size - (current_idx + 1 - circ_id)) % buffer_size);
        }
    }

    size_t seq_id_to_circ_id(size_t seq_id) const
    {
        if(current_size < buffer_size)
        {
            return seq_id;
        }
        else
        {
            return ((current_idx + 1 + seq_id) % buffer_size);
        }
    }
};

#endif