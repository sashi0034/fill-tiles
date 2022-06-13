//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_TILEMAP_H
#define FILL_TILES_TILEMAP_H

#include "../gameEngine/gameEngine.h"
#include "TileMapMatElement.h"
#include <boost/tokenizer.hpp>
#include <boost/property_tree/ptree.hpp>

namespace inGame
{
    class TileMap
    {
    private:
        static inline const std::string tileMapDirectory = "./assets/tilemaps/";
    public:
        TileMap();
    private:
        unique_ptr<Graph> m_TilesetImage{};
        std::unordered_map<int, TilePropertyChip> m_Tileset;
        Vec2<int> m_MatSize{};
        std::vector<std::vector<TileMapMatElement>> m_Mat{};

        void testXml();
        void loadMapFile(const std::string& fileName);
        void loadTilesetFile(const std::string& fileName);
        void readTileProperty(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &property,
                TilePropertyChip *propertyRef);

        void readLayerData(const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeData);

        template <typename T> static std::vector<T> parseCsv(const std::string& source);
    };
}


#endif //FILL_TILES_TILEMAP_H
