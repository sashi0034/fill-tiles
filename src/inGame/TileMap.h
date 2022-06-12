//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_TILEMAP_H
#define FILL_TILES_TILEMAP_H

#include "../gameEngine/gameEngine.h"
#include <boost/tokenizer.hpp>

namespace inGame
{
    class TileMap
    {
    public:
        TileMap();
    private:
        template <typename T> static std::vector<T> parseCsv(const std::string& source);
        void testXml();
        static void loadFile(const std::string& fileName);
    };
}


#endif //FILL_TILES_TILEMAP_H
