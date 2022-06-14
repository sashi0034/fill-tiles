//
// Created by sashi0034 on 2022/06/11.
//

#include "TileMap.h"
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <regex>
#include "magic_enum.h"
#include "GameRoot.h"


namespace inGame
{

    TileMap::TileMap()
    {}


    template<typename T>
    std::vector<T> TileMap::parseCsv(const std::string &source)
    {
        auto result = std::vector<T>{};

        const auto crlf = std::regex("\r?\n");
        const std::string lf = "\n";
        const auto sourceLf = std::regex_replace(source, crlf, lf);

        std::stringstream stream(sourceLf);
        std::string line{};

        while (std::getline(stream, line))
        {
            boost::tokenizer<boost::escaped_list_separator<char> > tokenList(line);
            for (const std::string &str: tokenList)
            {
                if (str == "") continue;
                try
                {
                    T parsedValue = boost::lexical_cast<T>(str);
                    result.push_back(parsedValue);
                }
                catch (boost::bad_lexical_cast &)
                {
                    assert(false);
                    result.push_back(0);
                }
            }
        }
        return result;
    }

    /*
     *  Main Process Of Loading Map File.
     */
    void TileMap::LoadMapFile(const std::string &fileName)
    {
        using namespace boost::property_tree;

        const std::string filePath = tileMapDirectory + fileName;
        ptree xmlMap;
        read_xml(filePath, xmlMap);

        const auto treeMap = xmlMap.get_child("map");
        const auto treeTileset = treeMap.get_child("tileset");
        const std::string tilesetFileName = treeTileset.get<std::string>("<xmlattr>.source");
        loadTilesetFile(tilesetFileName);

        const int mapWidth = boost::lexical_cast<int>(treeMap.get<std::string>("<xmlattr>.width"));
        const int mapHeight = boost::lexical_cast<int>(treeMap.get<std::string>("<xmlattr>.height"));

        resizeMat(mapWidth, mapHeight);

        readLayersAndObjects(treeMap);

        initMatElements();
    }

    void TileMap::readLayersAndObjects(
            boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> treeMap)
    {
        for (const auto &treeLayer: treeMap.get_child("layer"))
        {
            if (treeLayer.first != "data") continue;
            readLayerData(treeLayer.second);
        }
    }

    void TileMap::resizeMat(const int mapWidth, const int mapHeight)
    {
        m_MatSize = Vec2{mapWidth, mapHeight};
        m_Mat.resize(mapWidth, std::vector<unique_ptr<TileMapMatElement>>(mapHeight, unique_ptr<TileMapMatElement>(
                nullptr)));
        for (auto &row: m_Mat)
            for (auto &ele: row)
                ele = std::make_unique<TileMapMatElement>();
    }


    void TileMap::initMatElements()
    {
        for (int x = 0; x < m_MatSize.X; ++x)
            for (int y = 0; y < m_MatSize.Y; ++y)
                m_Mat[x][y]->UpdateChipList();

        // @todo: 崖などの情報を登録する
    }


    void TileMap::readLayerData(
            const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeData)
    {
        using namespace boost::property_tree;

        const auto data = treeData.get_value<std::string>();
        const auto parsedData = parseCsv<int>(data);
        const int dataSize = parsedData.size();
        assert(dataSize == m_MatSize.X * m_MatSize.Y);

        for (int y = 0; y < m_MatSize.Y; ++y)
        {
            for (int x = 0; x < m_MatSize.X; ++x)
            {
                const int index = x + y * m_MatSize.X;

                // Tiledのレイヤー要素のマップタイルIDは+1加算されているので、-1が必要
                const int chipId = parsedData[index] - 1;

                if (chipId == -1) continue;

                if (m_Tileset.count(chipId) != 0)
                {
                    TilePropertyChip *chipPtr = &m_Tileset[chipId];
                    m_Mat[x][y]->AddChip(chipPtr);
                } else
                {
                    assert(false);
                }
            }
        }
    }


    void TileMap::loadTilesetFile(const std::string &fileName)
    {
        using namespace boost::property_tree;

        const std::string filePath = tileMapDirectory + fileName;
        ptree xmlTileset;
        read_xml(filePath, xmlTileset);

        const auto treeTileset = xmlTileset.get_child("tileset");
        const int numColumns = boost::lexical_cast<int>(treeTileset.get<std::string>("<xmlattr>.columns"));
        const int tileWidth = boost::lexical_cast<int>(treeTileset.get<std::string>("<xmlattr>.tilewidth"));
        const int tileHeight = boost::lexical_cast<int>(treeTileset.get<std::string>("<xmlattr>.tileheight"));
        const std::string imageName = treeTileset.get<std::string>("image.<xmlattr>.source");

        m_TilesetImage.reset(Graph::CreateFromFilePath(GameRoot::GetInstance().GetAppState()->GetRenderer(),
                                                       tileMapDirectory + imageName));

        for (const auto &tile: treeTileset)
        {
            if (tile.first != "tile") continue;

            const int id = boost::lexical_cast<int>(tile.second.get<std::string>("<xmlattr>.id"));

            auto newTile = TilePropertyChip{};
            newTile.SrcPoint = Vec2{(id % numColumns) * tileWidth, (id / numColumns) * tileHeight};

            for (const auto &property: tile.second.get_child("properties"))
            {
                readTileProperty(property.second, &newTile);
            }

            assert(newTile.Kind != ETileKind::none);

            m_Tileset[id] = newTile;
        }


    }

    void
    TileMap::readTileProperty(
            const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &property,
            TilePropertyChip *propertyRef)
    {
        const auto propertyName = property.get<std::string>("<xmlattr>.name");
        const auto value = property.get<std::string>("<xmlattr>.value");

        if (propertyName == "kind")
        {
            ETileKind kind = magic_enum::enum_cast<ETileKind>(value).value_or(ETileKind::none);
            propertyRef->Kind = kind;
        } else
        {
            assert(false);
        }
    }

    Vec2<int> TileMap::GetMatSize() const
    {
        return m_MatSize;
    }

    ITileMapMatElement *TileMap::GetElementAt(const Vec2<int> &pos) const
    {
        assert(Range<int>(0, m_MatSize.X-1).IsBetween(pos.X));
        assert(Range<int>(0, m_MatSize.Y-1).IsBetween(pos.Y));

        return m_Mat[pos.X][pos.Y].get();
    }

    Graph &TileMap::GetTilesetImage() const
    {
        return *m_TilesetImage;
    }


}

