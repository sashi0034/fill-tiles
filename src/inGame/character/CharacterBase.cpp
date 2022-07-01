//
// Created by sashi0034 on 2022/06/17.
//

#include "CharacterBase.h"
#include "../FieldManager.h"

namespace inGame::character
{
    CharacterBase::CharacterBase(IFieldManager *parentField)
    : ChildBase<CharacterBase>(parentField->GetCharacterPool())
    {}

    void CharacterBase::Destroy()
    {
        this->getBelongingPool()->Destroy(this);
    }
}
