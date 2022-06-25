//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_TILEMAP_H
#define FILL_TILES_TILEMAP_H

#include "../../gameEngine/gameEngine.h"
#include "TileMapMatElement.h"
#include <boost/tokenizer.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../Boolean.h"
#include "StaticTileset.h"
#include "../MatPos.h"

namespace inGame{
    class IMainScene;
    class IFieldManager;
}

namespace inGame::field
{
    class ITileMap
    {
    public:
        virtual Boolean HasChipAt(const Vec2<int> &pos, ETileKind checkingKind) = 0;
        virtual Vec2<int> GetMatSize() const = 0;
    };

    class TileMap : public ITileMap
    {
    public:
        TileMap(IMainScene *mainScene);
        void LoadMapFile(const std::string &fileName);
        Vec2<int> GetMatSize() const override;
        ITileMapMatElement * GetElementAt(const Vec2<int>& pos);
        bool IsInRange(const Vec2<int>& pos) const;
        Boolean HasChipAt(const Vec2<int> &pos, ETileKind checkingKind) override;
        Graph& GetTilesetImage() const;

        static inline const std::string TileMapDirectory = "./assets/tilemaps/";
    private:
        IMainScene* m_MainScene;
        unique_ptr<Graph> m_TilesetImage{};
        std::unordered_map<int, TilePropertyChip> m_Tileset;
        std::unordered_map<ETileKind, TilePropertyChip*> m_TilesetByKind{};
        const StaticTileset staticTileset{};
        Vec2<int> m_MatSize{};
        std::vector<TileMapMatElement> m_Mat{};

        void loadTilesetFile(const std::string &fileName);

        void readTileProperty(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &property,
                TilePropertyChip *propertyRef);

        void readLayerData(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeData);
        void readObjectGroup(const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeObjectGroup);
        void readObjectInObjectGroup(const std::string& objectType, const std::string& objectName,
                                     const Vec2<int>& pos, std::unordered_map<std::string, std::string>& objectProperty);

        template<typename T>
        static std::vector<T> parseCsv(const std::string &source);

        void resizeMat(int mapWidth, int mapHeight);

        void readLayersAndObjects(
                boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> treeMap);

        TileMapMatElement* getElementAt(const Vec2<int>& pos);

        bool summonCharacterByChip(const Vec2<int> &pos, ETileKind kind);

        void initMatElementsAfterLoaded();

        void checkCliff(const Vec2<int> &pos);
        void checkCliffShade(const Vec2<int> &pos);

        void
        checkCliffShadeOf(const Vec2<int> &pos, ETileKind upperKind, ETileKind upperCliffKind, TilePropertyChip *lowerChip,
                          TilePropertyChip *lowerShadeFace, TilePropertyChip *lowerShadeEdge);
        void checkCliffFlagOf(const Vec2<int> &pos, ETileKind checkingKind, ETileKind cliffKind);
    };
}


#endif //FILL_TILES_TILEMAP_H
