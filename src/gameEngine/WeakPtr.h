
// 参考: 弱参照クラスを自作する by shinya (id:shinya_game_app)
// https://flat-leon.hatenablog.com/entry/cpp_impl_weak_ref

#ifndef FILL_TILES_WEAKPTR_H
#define FILL_TILES_WEAKPTR_H

#include <assert.h>
#include <type_traits>

namespace gameEngine
{
    class PtrInfo
    {
    public:
        void *m_Ptr = nullptr;
        int m_RefCount = 0;

        PtrInfo(void *ptr) : m_Ptr(ptr)
        {}

        void Inc(void)
        { ++m_RefCount; }

        static void Dec(PtrInfo *&p_info)
        {
            if (!p_info)
            { return; }
            --p_info->m_RefCount;
            if (p_info->m_RefCount == 0)
            {
                delete p_info;
                p_info = nullptr;
            }
        }

        bool IsNull(void) const
        { return m_Ptr == nullptr; }

        template<class T>
        T *GetPtr(void) const
        { return reinterpret_cast<T *>(m_Ptr); }

        int GetRefCount(void) const
        { return m_RefCount; }
    };

    template<class T>
    class WeakPtrController;

#define nonvirtual

    template<class T>
    class WeakPtr
    {
        friend class WeakPtrController<T>;

        gameEngine::PtrInfo *m_pPtrInfo = nullptr;
    public:
        nonvirtual ~WeakPtr()
        {
            gameEngine::PtrInfo::Dec(m_pPtrInfo);
        }

        WeakPtr()
        {
        }

        explicit WeakPtr(gameEngine::PtrInfo *p_ptrInfo) : m_pPtrInfo(p_ptrInfo)
        {
            if (m_pPtrInfo)
            {
                m_pPtrInfo->Inc();
            }
        }

        WeakPtr(const WeakPtr &other) : m_pPtrInfo(other.m_pPtrInfo)
        {
            if (m_pPtrInfo)
            {
                m_pPtrInfo->Inc();
            }
        }

        WeakPtr &operator=(const WeakPtr &other)
        {
            gameEngine::PtrInfo::Dec(m_pPtrInfo);
            m_pPtrInfo = other.m_pPtrInfo;
            if (m_pPtrInfo)
            {
                m_pPtrInfo->Inc();
            }
            return *this;
        }

        void Clear(void)
        {
            gameEngine::PtrInfo::Dec(m_pPtrInfo);
            m_pPtrInfo = nullptr;
        }

        template<class U>
        WeakPtr<U> GetUpcasted(void)
        {
            static_assert(std::is_base_of<U, T>::value, ""); // U が T の基底クラスである必要がある
            return WeakPtr<U>(m_pPtrInfo);
        }

        template<class U>
        WeakPtr<U> GetDowncasted(void)
        {
            //static_assert(std::is_base_of<T, U>::value, ""); // U は T の派生クラスである必要がある
            if (dynamic_cast<U *>( GetPtr())) // ポインタが実際に U型 インスタンスであるかどうかをチェック
            {
                return WeakPtr<U>(m_pPtrInfo);
            }
            return WeakPtr<U>(nullptr); // ダウンキャストに失敗したらNULLポインタ(のWeakPtr)を返す
        }

        bool IsNull(void) const
        { return !m_pPtrInfo || m_pPtrInfo->IsNull(); }

        T *GetPtr(void) const
        { return m_pPtrInfo ? m_pPtrInfo->GetPtr<T>() : nullptr; }

        T &operator*() const
        {
            assert(!IsNull());
            return *GetPtr();
        }

        T *operator->() const
        {
            assert(!IsNull());
            return GetPtr();
        }

        operator T *() const
        { return GetPtr(); }

        int GetRefCount(void) const
        { return m_pPtrInfo ? m_pPtrInfo->GetRefCount() : 0; }
    };

    template<class T>
    class WeakPtrController
    {
        WeakPtr<T> m_WeakPtr;
    public:
        nonvirtual ~WeakPtrController()
        {
            if (m_WeakPtr.m_pPtrInfo)
            {
                m_WeakPtr.m_pPtrInfo->m_Ptr = nullptr;
            }
        }

        explicit WeakPtrController(T *ptr) : m_WeakPtr(new gameEngine::PtrInfo(ptr))
        {}

        WeakPtrController() = delete;

        WeakPtrController(const WeakPtrController &other) = default;

        WeakPtrController &operator=(const WeakPtrController &other) = default;

        template<class U>
        WeakPtr<U> GetDowncasted_unsafe(U *p_this)
        {
            (void) p_this;
            static_assert(std::is_base_of<T, U>::value, "");
            return WeakPtr<U>(m_WeakPtr.m_pPtrInfo);
        }

        WeakPtr<T> GetWeakPtr()
        { return m_WeakPtr; }
    };
}

#define DEF_WEAK_CONTROLLER(type_) \
    public:  WeakPtr<type_> GetWeakPtr( void ){ return m_WeakPtrController.GetWeakPtr(); } \
    protected: WeakPtrController<type_> m_WeakPtrController{this}

#define DEF_WEAK_GET(type_) public: WeakPtr<type_> GetWeakPtr( void ){ return m_WeakPtrController.GetDowncasted_unsafe( this ); }class{}


#endif //FILL_TILES_WEAKPTR_H
