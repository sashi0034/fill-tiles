//
// Created by sashi0034 on 2022/07/19.
//

#ifndef FILL_TILES_UPPINGFLAG_H
#define FILL_TILES_UPPINGFLAG_H


namespace inGame
{
    class UppingFlag
    {
    public:
        UppingFlag() = default;
        bool IsUpping() const;
        void DownFlag();
        void operator=(UppingFlag) = delete;
    private:
        bool isUpping = true;
    };
}


#endif //FILL_TILES_UPPINGFLAG_H
