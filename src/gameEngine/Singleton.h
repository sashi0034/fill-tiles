//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_SINGLETON_H
#define FILL_TILES_SINGLETON_H

#include "log.h"
#include <memory>

using std::unique_ptr;

namespace gameEngine
{
    template <typename T>
    class Singleton
    {
    private:
        static unique_ptr<T> instance;
    public:
        Singleton()
        {
            if (instance != nullptr)
            {
                LOG_CERR << "Singleton Object Is Already Exit." << std::endl;
                return;
            }
            instance = unique_ptr<T>(static_cast<T*>(this));
        }
        virtual ~Singleton()
        {
            instance = nullptr;
        }
        static const T& GetInstance()
        {
            return *instance;
        }
    };
    template <typename T> unique_ptr<T> Singleton<T>::instance = nullptr;
}

#endif //FILL_TILES_SINGLETON_H
