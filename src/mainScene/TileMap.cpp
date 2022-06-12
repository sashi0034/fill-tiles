//
// Created by sashi0034 on 2022/06/11.
//

#include "TileMap.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include "regex"


namespace mainScene{

    TileMap::TileMap()
    {
        testXml();
    }

    void TileMap::testXml()
    {
        loadFile("./assets/tilemaps/field_01.tmx");
    }


    void TileMap::loadFile(const std::string& fileName)
    {
        using namespace boost::property_tree;

        {
            ptree pt;
            read_xml(fileName, pt);

            if (boost::optional<std::string> str = pt.get_optional<std::string>("map.layer.<xmlattr>.name"))
            {
                std::cout << str.get() << std::endl;
            } else
            {
                std::cout << "data is nothing" << std::endl;
            }

            boost::optional<std::string> str = pt.get_optional<std::string>("map.layer.data");
            std::cout << str.get() << std::endl;
            auto test = parseCsv<int>(str.get());

        }

//        {
//            ptree pt;
//            read_xml("./assets/tilemaps/test.xml", pt);
//
//            if (boost::optional<std::string> str = pt.get_optional<std::string>("root.str")) {
//                std::cout << str.get() << std::endl;
//            }
//            else {
//                std::cout << "root.str is nothing" << std::endl;
//            }
//
//            for (auto &iter : pt.get_child("root.values")){
//                const int value = boost::lexical_cast<int>(iter.second.data());
//               std::cout << value << std::endl;
//            }
//        }

    }

    template <typename T> std::vector<T> TileMap::parseCsv(const std::string& source)
    {
        auto result =  std::vector<T>{};

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
                if (str=="") continue;
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


}

