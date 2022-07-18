//
// Created by sashi0034 on 2022/07/18.
//

#ifndef FILL_TILES_PLAYERACTIONDATA_H
#define FILL_TILES_PLAYERACTIONDATA_H

namespace inGame
{

    class PlayerActionData
    {
    public:
        virtual ~PlayerActionData() = default;
    };

    class PlayerActionPushCatfish : public PlayerActionData
    {};

} // inGame

#endif //FILL_TILES_PLAYERACTIONDATA_H
