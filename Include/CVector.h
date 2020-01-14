#pragma once

#include <assert.h>
#include <limits>
#include <xmemory>

template<typename T>
class vector_const_iterator
{
    template <typename T, typename Alloc>
    friend class CVector;

protected:
    T* _ptr = nullptr;

public:
    vector_const_iterator& operator++()
    {
        ++_ptr;
        return *this;
    }
    vector_const_iterator& operator--()
    {
        --_ptr;
        return *this;
    }
    vector_const_iterator operator +(size_t idx)
    {
        vector_const_iterator iter;
        iter._ptr = _ptr + idx;
        return iter;
    }
    vector_const_iterator operator -(size_t idx)
    {
        vector_const_iterator iter;
        iter._ptr = _ptr - idx;
        return iter;
    }
    void operator = (const vector_const_iterator& iter)
    {
        _ptr = iter._ptr;
    }
    bool operator==(const vector_const_iterator& iter) const
    {
        return _ptr == iter._ptr;
    }
    bool operator!=(const vector_const_iterator& iter) const
    {
        return _ptr != iter._ptr;
    }

public:
    const T& operator* ()
    {
        return *_ptr;
    }
};

template<typename T>
class vector_const_reverse_iterator
{
    template <typename T, typename Alloc>
    friend class CVector;

    using criter = vector_const_reverse_iterator<T>;

protected:
    T* _ptr = nullptr;

public:
    criter& operator++()
    {
        --_ptr;
        return *this;
    }
    criter& operator--()
    {
        ++_ptr;
        return *this;
    }
    criter operator +(size_t idx)
    {
        criter iter;
        iter._ptr = _ptr - idx;
        return iter;
    }
    criter operator -(size_t idx)
    {
        criter iter;
        iter._ptr = _ptr + idx;
        return iter;
    }
    void operator = (const criter& iter)
    {
        _ptr = iter._ptr;
    }
    bool operator==(const criter& iter) const
    {
        return _ptr == iter._ptr;
    }
    bool operator!=(const criter& iter) const
    {
        return _ptr != iter._ptr;
    }

public:
    const T& operator* ()
    {
        return *_ptr;
    }
};

template <typename T>
class vector_iterator : public vector_const_iterator<T>
{
    template <typename T, typename Alloc>
    friend class CVector;

    using Base = vector_const_iterator<T>;

public:
    vector_iterator& operator++()
    {
        Base::operator++();
        return *this;
    }
    vector_iterator& operator--()
    {
        Base::operator--();
        return *this;
    }
    vector_iterator operator +(size_t idx)
    {
        vector_iterator iter;
        iter._ptr = Base::_ptr +idx;
        return iter;
    }
    vector_iterator operator -(size_t idx)
    {
        vector_iterator iter;
        iter._ptr = Base::_ptr - idx;
        return iter;
    }
    void operator = (const vector_iterator& iter)
    {
        Base::operator=(iter);
    }
    bool operator==(const vector_iterator& iter) const
    {
        return Base::operator==(iter);
    }
    bool operator!=(const vector_iterator& iter) const
    {
        return Base::operator!=(iter);
    }

public:
    T& operator* ()
    {
        return *(Base::_ptr);
    }
};

template <typename T>
class vector_reverse_iterator : public vector_const_reverse_iterator<T>
{
    template <typename T, typename Alloc>
    friend class CVector;

    using Base = vector_const_reverse_iterator<T>;
    using riter = vector_reverse_iterator<T>;

public:
    riter& operator++()
    {
        Base::operator++();
        return *this;
    }
    riter& operator--()
    {
        Base::operator--();
        return *this;
    }
    riter operator +(size_t idx)
    {
        riter iter;
        iter._ptr = Base::_ptr - idx;
        return iter;
    }
    riter operator -(size_t idx)
    {
        vector_iterator iter;
        iter._ptr = Base::_ptr + idx;
        return iter;
    }
    void operator = (const riter& iter)
    {
        Base::operator=(iter);
    }
    bool operator==(const riter& iter) const
    {
        return Base::operator==(iter);
    }
    bool operator!=(const riter& iter) const
    {
        return Base::operator!=(iter);
    }

public:
    T& operator* ()
    {
        return *(Base::_ptr);
    }
};

template <typename T, typename Alloc = allocator<T>>
class CVector
{
private:
    static constexpr size_t DefaultCapacity = 0;
    static constexpr size_t Maxsize = std::numeric_limits<int>::max() / 2 - 1;
    static constexpr size_t Boundary = 2;
    static constexpr size_t BoundaryPad = 1;
    static constexpr size_t Empty = 0;
    static constexpr size_t GrowthSpeed = 2;

private:
    size_t m_iSize = 0;
    size_t m_iCapacity = DefaultCapacity;

    T *m_pArray = nullptr;

    /*
       begin                  end
        ก้                      ก้
    [.][0][2][3][10][5][12][8][.]
     ก่                      ก่
    rend                   rbegin
    */

public:
    CVector()
    {
        if (m_iCapacity != 0)
        {
            m_pArray = new T[DefaultCapacity + Boundary];
        }
    }
    CVector(size_t num, const T& val)
    {
        size_t volume = DefaultCapacity + Boundary;

        if (num > DefaultCapacity)
        {
            volume = num + Boundary;
        }

        m_pArray = new T[volume];
        for (int i = 0; i < num; ++i)
        {
            *(m_pArray + i + BoundaryPad) = val;
        }
        m_iSize = num;
    }
    CVector(const CVector& vec)
    {
        if (_is_empty_vector(vec))
        {
            _setempty();
        }
        else
        {
            _copy(vec);
        }
    }
    CVector(CVector&& vec)
    {
        _move(vec);
    }
    virtual ~CVector()
    {
        if (m_pArray)
        {
            delete[] m_pArray;
        }
        m_pArray = nullptr;
    }
    CVector& operator = (const CVector& vec)
    {
        if (_is_empty_vector(vec))
        {
            _setempty();
            return *this;
        }

        if (this == &vec)
        {
            return * this;
        }

        if (m_pArray)
        {
            delete[] m_pArray;
            m_pArray = nullptr;
        }

        _copy(vec);

        return *this;
    }
    CVector& operator = (CVector&& vec)
    {
        if (m_pArray)
        {
            delete[] m_pArray;
            m_pArray = nullptr;
        }
        _move(vec);

        return *this;
    }

private:
    void _reallocate(size_t iSize)
    {
        // need memory at least iSize
        assert(iSize < Maxsize);

        if (m_iCapacity * GrowthSpeed < Maxsize)
        {
            m_iCapacity *= GrowthSpeed;
        }

        if (iSize > m_iCapacity)
            m_iCapacity = iSize;

        T *m_pNewArray = new T[m_iCapacity + Boundary];
        if (m_pArray)
        {
            memmove(m_pNewArray, m_pArray, sizeof(T)*(m_iSize + Boundary));
            delete[] m_pArray;
            m_pArray = nullptr;
        }
        m_pArray = m_pNewArray;
    }
    bool _is_empty_vector(const CVector& vec)
    {
        if (vec.m_iCapacity == Empty)
        {
            if (vec.m_iSize != Empty || vec.m_pArray != nullptr)
            {
                assert(false && "capactiy is null but size != capacity || Array is not nullptr");
            }
            return true;
        }
        return false;
    }
    void _setempty()
    {
        m_iSize = Empty;
        m_iCapacity = Empty;
        if (m_pArray)
        {
            delete[] m_pArray;
        }
        m_pArray = nullptr;
    }
    void _copy(const CVector& vec)
    {
        m_iCapacity = vec.m_iCapacity;
        m_iSize = vec.m_iSize;
        m_pArray = new T[m_iCapacity + Boundary];
        memmove(m_pArray, vec.m_pArray, sizeof(T)*(m_iSize + Boundary));
    }
    void _move(CVector& vec)
    {
        m_iCapacity = vec.m_iCapacity;
        m_iSize = vec.m_iSize;
        m_pArray = vec.m_pArray;

        vec.m_pArray = nullptr;
    }

public:
    size_t size() const { return m_iSize; }
    size_t capacity() const { return m_iCapacity; }
    size_t max_size() { return Maxsize; }
    bool empty() const { return m_iSize == 0; }

    void reserve(size_t iCapacity)
    {
        assert(iCapacity < Maxsize);

        if (iCapacity <= m_iCapacity)
            return;

        m_iCapacity = iCapacity;

        T *m_pNewArray = new T[iCapacity];
        if (m_pArray)
        {
            memmove(m_pNewArray, m_pArray, sizeof(T)*m_iSize);
            delete[] m_pArray;
            m_pArray = nullptr;
        }
        m_pArray = m_pNewArray;
    }
    void resize(size_t iSize, T val = T())
    {
        if (iSize > m_iCapacity)
        {
            _reallocate(iSize);

            for (int i = m_iSize; i < iSize; ++i)
            {
                *(m_pArray + i + BoundaryPad) = val;
            }
        }
        m_iSize = iSize;
    }
    void shirink_to_fit()
    {
        if (m_iSize == m_iCapacity && m_iCapacity !=0)
            return;

        m_iCapacity = m_iSize;

        if (m_iCapacity == 0)
        {
            if (m_pArray)
            {
                delete[] m_pArray;
                m_pArray = nullptr;
            }
            return;
        }

        T *m_pNewArray = new T[m_iCapacity + Boundary];
        if (m_pArray)
        {
            memmove(m_pNewArray, m_pArray, sizeof(T)*(m_iCapacity + BoundaryPad));
            delete[] m_pArray;
            m_pArray = nullptr;
        }
        else
        {
            assert(false && "exist elements but nullptr array");
        }
        m_pArray = m_pNewArray;
    }

    // Element Access
public:
    T& operator[] (size_t index)
    {
        assert(index >= 0 && index < m_iSize && "invalid operator[]");
        return *(m_pArray + index + BoundaryPad);
    }
    const T& operator[] (size_t index) const
    {
        assert(index >= 0 && index < m_iSize && "invalid operator[]");
        return *(m_pArray + index + BoundaryPad);
    }
    T& at(size_t index)
    {
        assert(index >= 0 && index < m_iSize && "invalid index");
        return *(m_pArray + index + BoundaryPad);
    }
    const T& at(size_t index) const
    {
        assert(index >= 0 && index < m_iSize && "invalid index");
        return *(m_pArray + index + BoundaryPad);
    }
    T& front()
    {
        assert(!empty() && "front() called on empty vector");
        return *(m_pArray + BoundaryPad);
    }
    const T& front() const
    {
        assert(!empty() && "front() called on empty vector");
        return *(m_pArray + BoundaryPad);
    }
    T& back()
    {
        assert(!empty() && "back() called on empty vector");
        return *(m_pArray + m_iSize);
    }
    const T& back() const
    {
        assert(!empty() && "back() called on empty vector");
        return *(m_pArray + m_iSize);
    }
    T* data()
    {
        return m_pArray + BoundaryPad;
    }
    const T* data() const
    {
        return m_pArray + BoundaryPad;
    }

public:
    void Assign(size_t num, const T& val)
    {
        if (m_pArray)
        {
            delete[] m_pArray;
            m_pArray = nullptr;
        }

        size_t volume = DefaultCapacity + Boundary;

        if (num > DefaultCapacity)
        {
            volume = num + Boundary;
        }

        m_pArray = new T[volume];

        for (int i = 0; i < num; ++i)
        {
            *(m_pArray + i + BoundaryPad) = val;
        }

        m_iSize = num;
        m_iCapacity = DefaultCapacity;
    }
    void push_back(const T& val)
    {
        if (m_iSize >= m_iCapacity)
        {
            _reallocate(m_iSize + 1);
        }

        *(m_pArray + m_iSize + BoundaryPad) = val;
        ++m_iSize;
    }
    void pop_back()
    {
        assert(m_iSize > 0 && "vector empty before pop");
        --m_iSize;
    }
    void swap(CVector& other)
    {
        if (this == &other)
        {
            return;
        }

        T *pArray = other.m_pArray;
        size_t iSize = other.m_iSize;
        size_t iCapacity = other.m_iCapacity;

        other.m_pArray = m_pArray;
        other.m_iSize = m_iSize;
        other.m_iCapacity = m_iCapacity;

        m_pArray = pArray;
        m_iSize = iSize;
        m_iCapacity = iCapacity;
    }
    void clear() { m_iSize = 0; }

    void emplace_back(const T& val)
    {
        push_back(val);
    }

    using allocator_type = Alloc;

    allocator_type get_allocator() const
    {
        return allocator_type();
    }

    using iterator = vector_iterator<T>;
    using const_iterator = vector_const_iterator<T>;
    using reverse_iterator = vector_reverse_iterator<T>;
    using const_reverse_iterator = vector_const_reverse_iterator<T>;

    iterator emplace(iterator position, const T& val)
    {
        return _iterator_insert(position, val, 1);
    }
    iterator insert(iterator position, const T& val)
    {
        return _iterator_insert(position, val, 1);
    }
    iterator insert(iterator position, size_t n, const T& val)
    {
        return _iterator_insert(position, val, n);
    }
private:
    iterator _iterator_insert(iterator position, const T& val, size_t n)
    {
        size_t index = position._ptr - m_pArray - BoundaryPad;

        if (index > m_iSize || index < 0)
        {
            assert(false && "insertion invalid iterator");
        }

        if (m_iSize + n > m_iCapacity)
        {
            _reallocate(m_iSize + n);
        }

        position._ptr = m_pArray + index + BoundaryPad;

        iterator next = position + n;
        memmove(next._ptr, position._ptr, sizeof(T)*(m_iSize - index));

        for (int i = 0; i < n; ++i)
        {
            *(position._ptr + i) = val;
        }
        m_iSize += n;

        return position;
    }

public:
    iterator erase(iterator position)
    {
        size_t index = position._ptr - m_pArray - BoundaryPad;

        if (index >= m_iSize || index < 0)
        {
            assert(false && "invalid iterator out of vector range");
        }

        memmove(position._ptr, position._ptr + 1, sizeof(T)* (m_iSize - index -1 ));

        --m_iSize;

        return position;
    }
    iterator erase(iterator first, iterator end)
    {
        size_t firstidx = first._ptr - m_pArray - BoundaryPad;
        if (firstidx < 0)
        {
            assert(false && "cannot find iterator before begin");
        }

        size_t endidx = end._ptr - m_pArray - BoundaryPad;
        if (endidx > m_iSize)
        {
            assert(false && "cannot find iterator after end");
        }

        if (firstidx > endidx)
        {
            assert(false && "erase iterator first after end");
        }

        if (firstidx == endidx)
            return first;

        size_t num = end._ptr - first._ptr;

        if (num == m_iSize || endidx == m_iSize)
        {
            m_iSize -= num;
            return first;
        }

        memmove(first._ptr, end._ptr, sizeof(T)* (m_iSize - endidx));
        m_iSize -= num;

        return first;
    }
/* iteration begin/end */
public:
    iterator begin()
    {
        iterator iter;
        iter._ptr = m_pArray + BoundaryPad;
        return iter;
    }
    iterator end()
    {
        iterator iter;
        iter._ptr = m_pArray + m_iSize + BoundaryPad;
        return iter;
    }
    const_iterator cbegin()
    {
        const_iterator citer;
        citer._ptr = m_pArray + BoundaryPad;
        return citer;
    }
    const_iterator cend()
    {
        const_iterator citer;
        citer._ptr = m_pArray + m_iSize + BoundaryPad;
        return citer;
    }
    reverse_iterator rbegin()
    {
        reverse_iterator iter;
        iter._ptr = m_pArray + m_iSize;
        return iter;
    }
    reverse_iterator rend()
    {
        reverse_iterator iter;
        iter._ptr = m_pArray;
        return iter;
    }
    const_reverse_iterator crbegin()
    {
        const_reverse_iterator citer;
        citer._ptr = m_pArray + m_iSize;
        return citer;
    }
    const_reverse_iterator crend()
    {
        const_reverse_iterator citer;
        citer._ptr = m_pArray;
        return citer;
    }
};
