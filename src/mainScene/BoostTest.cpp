//
// Created by sashi0034 on 2022/05/05.
//
#include <boost/coroutine2/coroutine.hpp>
#include <iostream>
#include <boost/version.hpp>
#include "BoostTest.h"

typedef boost::coroutines2::coroutine<int> coro_t;

namespace mainScene
{

    BoostTest::BoostTest()
    {

    }

    void func(coro_t::push_type& yield)
    {
        std::cout << 2 << " ";
        yield(3); // {3}をメインコンテキストに戻す
        std::cout << 5 << " ";
        yield(6); // {6}をメインコンテキストに戻す
    }


    void BoostTest::Update()
    {
        m_T += 1;
        if (m_T==5)
        {
            coro_t::pull_type source(func);

            if (source) //プルコルーチンが有効かどうかをテストする
                std::cout << source.get() << " "; // データ値にアクセス

            std::cout << 4 << " ";

            if (source) {
                source(); // コンテキストスイッチ
                std::cout << source.get() << " "; // データ値にアクセス
            }

            std::cout << "boost version:" << BOOST_VERSION << std::endl;
            std::cout << "boost lib version:" << BOOST_LIB_VERSION << std::endl;

            printf("sample1 end.\n");
        }
    }

}
