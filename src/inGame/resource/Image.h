//
// Created by sashi0034 on 2022/05/27.
//

#ifndef FILL_TILES_IMAGE_H
#define FILL_TILES_IMAGE_H

#include "../../gameEngine/gameEngine.h"

#define REGISTER_RESOURCE_PNG(fileName) const unique_ptr<Graph> fileName = loadPng(#fileName)

namespace inGame::resource
{
    class Image
    {
        unique_ptr<Graph> loadPng(const std::string& fileName);
        IAppState* m_AppStatePtr = nullptr;
    public:
        REGISTER_RESOURCE_PNG(kisaragi_32x32);
        REGISTER_RESOURCE_PNG(dango_wolf_24x24);
        REGISTER_RESOURCE_PNG(test_room_floor_32x32);
        REGISTER_RESOURCE_PNG(high_plateau_16x16);
        REGISTER_RESOURCE_PNG(normal_plain_16x16);
        REGISTER_RESOURCE_PNG(tree_16x16);
        REGISTER_RESOURCE_PNG(tree_48x48);
        REGISTER_RESOURCE_PNG(low_basin_16x16);
        REGISTER_RESOURCE_PNG(grow_bamboo_16x16);
        REGISTER_RESOURCE_PNG(mine_flower_16x16);
        REGISTER_RESOURCE_PNG(folder_16x16);
        REGISTER_RESOURCE_PNG(ui_white_rounnd_rect);
        REGISTER_RESOURCE_PNG(ui_black_window);

        explicit Image(IAppState* appState);
    private:


    };
}


#endif //FILL_TILES_IMAGE_H
