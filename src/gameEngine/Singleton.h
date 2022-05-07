//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_SINGLETON_H
#define FILL_TILES_SINGLETON_H

#include "log.h"

namespace gameEngine
{
    template <typename T>
    class ISingleton
    {
    public:
        static T* Instance;
    };
    template <typename T> T* ISingleton<T>::Instance = nullptr;


    template <typename T>
    class Singleton
    {
    public:
        Singleton()
        {
            if (Instance != nullptr)
            {
                LOG_CERR << "Singleton object is already exit." << std::endl;
                return;
            }
            Instance = static_cast<T*>(this);
        }
        virtual ~Singleton()
        {
            Instance = nullptr;
        }
        static T* Instance;
    };
    template <typename T> T* Singleton<T>::Instance = nullptr;
}

#endif //FILL_TILES_SINGLETON_H
