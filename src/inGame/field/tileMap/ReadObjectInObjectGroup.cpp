//
// Created by sashi0034 on 2022/08/06.
//

#include <boost/lexical_cast.hpp>
#include "ReadObjectInObjectGroup.h"
#include "../../Player.h"
#include "../../character/PuniCat.h"
#include "../../character/Fairy.h"


void inGame::field::tileMap::ReadObjectInObjectGroup(inGame::IMainScene *mainScene, const std::string &objectType,
                                                     const std::string &objectName, const Vec2<int> &pos,
                                                     std::unordered_map<std::string, std::string> &objectProperty)
{
    auto field = mainScene->GetFieldManager();
    auto characterPool = field->GetCharacterPool();
    auto matPos = MatPos(pos / FieldManager::PixelPerMat);

    if (objectType=="restart")
    {
        int level = boost::lexical_cast<int>(objectProperty["level"]);

        field->GetMineFlowerManager()->GetMineFlowerClassByLevel(level)->SetRespawnMatPos(matPos);

        if (level == 1)
        {
            auto player = mainScene->GetPlayer();
            if (player!= nullptr) player->SetPos(pos.CastTo<double>());
        }
    }
    else if (objectType=="fairy")
    {
        characterPool->Birth(new character::Fairy(mainScene, matPos, objectProperty["talk"]));
    }
    else if (objectType=="catfish")
    {
        characterPool->Birth(new character::Catfish(mainScene, matPos));
    }
    else if (objectType=="punicat")
    {
        characterPool->Birth(new character::PuniCat(mainScene, matPos));
    }
    else if (objectType=="test")
    {
        std::cout << pos.ToString() << std::endl;
    }
    else
    {
        assert(!"Invalid Object Exits In objectgroup.");
    }
    (void)objectName;
    (void)objectProperty;
}