//
// Created by sashi0034 on 2022/06/17.
//

#include "ZIndex.h"
#include "CharacterViewModel.h"

namespace inGame{


    ZIndexBackGround::ZIndexBackGround(SpriteTexture *texture)
    : m_Texture(texture)
    {}

    void ZIndexBackGround::ApplyZ()
    {
        m_Texture->SetZ(baseBackGroundZ);
    }

    ZIndexCharacter::ZIndexCharacter(CharacterViewModel &character)
    : m_Character(character)
    {}

    void ZIndexCharacter::ApplyZ()
    {
        double modelY = m_Character.GetModel()->GetPosition().Y;

        double normalizedZ = Range(infinityMinus, infinity)
                .Normalize(-modelY, Range(baseCharacterZ, baseCharacterZ + baseRange));

        m_Character.GetView()->SetZ(normalizedZ);
    }
}