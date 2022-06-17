//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_ZINDEX_H
#define FILL_TILES_ZINDEX_H


namespace inGame
{
    class ZIndex
    {
    public:
        virtual double GetZ() = 0;
    };

    class ZIndexBackGround : public ZIndex
    {
    public:
        ZIndexBackGround();

        double GetZ() override;

    };

}


#endif //FILL_TILES_ZINDEX_H
