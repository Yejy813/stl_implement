#ifndef __SHARE_PTR_H__
#define __SHARE_PTR_H__

#include <iostream>
#include "smart_ptr_define.h"

_SMART_PTR_BEGIN

// 前向申明
template <typename T> class weak_ptr;

template <class T >
class shared_ptr
{
public:
    template <class S>
    friend class shared_ptr;

    template <typename S>
    friend class weak_ptr;

    typedef shared_ptr<T> SHARE_PTR;

    shared_ptr()
    {
        m_ptr = NULL;
        m_iRefCount = NULL;
    }

    explicit shared_ptr(T* ptr)
    {
        if (ptr != NULL)
        {
            m_ptr = ptr;
            RefCountInit();
        }
    }

    shared_ptr(const weak_ptr<T> & wk_ptr)
     : m_ptr(wk_ptr.m_ptr), m_iRefCount(wk_ptr.m_iWeakRefCount)
    {
        //RefCountIncrease();
    }

    //拷贝构造
    shared_ptr(const SHARE_PTR& sh_ptr) 
    {
        if (sh_ptr.m_ptr != NULL)
        {
            m_ptr = sh_ptr.m_ptr;
            m_iRefCount = sh_ptr.m_iRefCount;

            RefCountIncrease();
        }
    }

    //赋值运算符
    SHARE_PTR& operator = (const SHARE_PTR& sh_ptr)
    {
        if (this != &sh_ptr)
        {
            RefCountDecrease();

            if (sh_ptr.m_ptr != NULL)
            {
                m_ptr = sh_ptr.m_ptr;
                m_iRefCount = sh_ptr.m_iRefCount;

                RefCountIncrease();
            }
        }

        return (*this);
    }

    ~shared_ptr()
    {
        RefCountDecrease();
    }

public:
    //提领操作
    T& operator*()
    {
        PTR_ASSERT(m_ptr != NULL);
        return *(m_ptr);
    }

    //原始指针操作
    T* operator->()
    {
        PTR_ASSERT(m_ptr != NULL);
        return m_ptr;
    }

    operator bool() const
    {
        return m_ptr != NULL;
    }

    //取得原始指针
    T* getPointer()
    {
        PTR_ASSERT(m_ptr != NULL);
        return m_ptr;
    }

    //获得引用计数
    int getRefCount()
    {
        PTR_ASSERT(m_iRefCount != NULL);
        return *m_iRefCount;
    }

private:
    void RefCountInit()
    {
        m_iRefCount = new int(1);
    }

    void RefCountIncrease()
    {
        if (m_iRefCount != NULL)
        {
            ++(*m_iRefCount);
        }
    }

    void RefCountDecrease()
    {
        if (m_iRefCount != NULL && --(*m_iRefCount) == 0)
        {
            delete m_ptr;
            delete m_iRefCount;
            m_ptr = NULL;
            m_iRefCount = NULL;
        }
    }

private:
    int* m_iRefCount; //引用计数

    T*  m_ptr; //对象指针
};


template <class T>
class weak_ptr
{
public:
    template <class S>
    friend class weak_ptr;

    template <class S>
    friend class shared_ptr;

    constexpr weak_ptr() noexcept : m_iWeakRefCount(nullptr), m_ptr(nullptr) { }

    weak_ptr( const weak_ptr<T>& rhs ) noexcept : m_iWeakRefCount(rhs.m_iWeakRefCount)
    {
        m_ptr = rhs.lock().getPointer();
    }
 
    weak_ptr( const shared_ptr<T>& rhs ) noexcept
     : m_iWeakRefCount(rhs.m_iRefCount), m_ptr(rhs.m_ptr) { }

    template <typename S>
    weak_ptr & operator=(const shared_ptr<S> & rhs)
    {
        m_ptr = dynamic_cast<T *>(rhs.m_ptr);
        m_iWeakRefCount = rhs.m_iRefCount;
        return *this;
    }

    template <typename S>
    weak_ptr & operator=(const weak_ptr<S> & rhs)
    {
        m_ptr = dynamic_cast<T *>(rhs.m_ptr);
        m_iWeakRefCount = rhs.m_iWeakRefCount;
        return *this;
    }

    weak_ptr& operator=( const weak_ptr& rhs ) noexcept
    {
        m_iWeakRefCount = rhs.m_iWeakRefCount;
        m_ptr = rhs.m_ptr;

        return *this;
    }

    weak_ptr& operator=( const shared_ptr<T>& rhs ) noexcept
    {
        m_iWeakRefCount = rhs.m_iRefCount;
        m_ptr = rhs.m_ptr;

        return *this;
    }

    shared_ptr<T> lock() const noexcept
    {
        shared_ptr<T> tmp;
        if(m_iWeakRefCount && *m_iWeakRefCount > 0)
        {
            tmp.m_iRefCount = m_iWeakRefCount;
            tmp.m_ptr = m_ptr;

            if(tmp.m_iRefCount)
            {
                ++(*tmp.m_iRefCount);
            }
        }

        return tmp;
    }

    int use_count()
    {
        return *m_iWeakRefCount;
    }

    bool expired() const noexcept
    { 
        return *m_iWeakRefCount == 0;
    }

    void Reset()
    {
        m_ptr = NULL;
        m_iWeakRefCount = NULL;
    }

private:
    int * m_iWeakRefCount; 

    T* m_ptr;
};


template<class T> 
class enable_shared_from_this
{
protected:
    enable_shared_from_this()
    {}

    enable_shared_from_this(enable_shared_from_this const &)
    {}

    enable_shared_from_this & operator=(enable_shared_from_this const &)
    {
        return *this;
    }

    ~enable_shared_from_this()
    {}

public:
    shared_ptr<T> shared_from_this()
    {
        return weak_this_.lock();
    }

    weak_ptr<T> weak_from_this()
    {
        return weak_this_;
    }

private:
    mutable weak_ptr<T> weak_this_;
};

_SMART_PTR_END
#endif // !__SHARE_PTR_H__