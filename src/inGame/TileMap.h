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
        void LoadMapFile(const std::string &fileName);
        Vec2<int> GetMatSize() const;
        ITileMapMatElement * GetElementAt(const Vec2<int>& pos) const;
        Graph& GetTilesetImage() const;
    private:
        unique_ptr<Graph> m_TilesetImage{};
        std::unordered_map<int, TilePropertyChip> m_Tileset;
        Vec2<int> m_MatSize{};
        std::vector<std::vector<unique_ptr<TileMapMatElement>>> m_Mat{};

        void loadTilesetFile(const std::string &fileName);

        void readTileProperty(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &property,
                TilePropertyChip *propertyRef);

        void readLayerData(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeData);

        template<typename T>
        static std::vector<T> parseCsv(const std::string &source);

        void resizeMat(int mapWidth, int mapHeight);

        void readLayersAndObjects(
                boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> treeMap);

        void initMatElements();
    };
}


#endif //FILL_TILES_TILEMAP_H
