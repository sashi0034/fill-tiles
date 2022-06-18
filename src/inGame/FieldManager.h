//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_FIELDMANAGER_H
#define FILL_TILES_FIELDMANAGER_H

#include "ActorBase.h"
#include "field/TileMap.h"
#include "field/TileMapMatElement.h"
#include "resource/Image.h"
#include "field/FieldRenderer.h"
#include "MatPos.h"
#include "character/CharacterBase.h"

namespace inGame
{
    namespace character{
        class CharacterBase;
    }

    class IMainScene;

    class IFieldManager
    {
    public:
        virtual bool CanMoveTo(const MatPos& pos) = 0;
        virtual IChildrenPool<character::CharacterBase>* GetCharacterPool() = 0;
        virtual ITextureAnimator* GetCharacterAnimator() = 0;
    };

    class FieldManager : public IFieldManager, public ActorBase
    {
    public:
        IChildrenPool<character::CharacterBase> *GetCharacterPool() override;

        explicit FieldManager(IChildrenPool<ActorBase> *belonging, IMainScene *parentalScene);

        ITextureAnimator* GetCharacterAnimator() override;

        void Init() override;
        void Update(IAppState* app) override;

        bool CanMoveTo(const MatPos& pos) override;

        static inline const int PixelPerMat = 16;
        static inline const Vec2<int> MatPixelSize = {PixelPerMat, PixelPerMat};
        static inline const Vec2<double> CharacterPadding{0, -PixelPerMat/4};
        const Vec2<int> ScreenMatSize;

    private:
        void renderTileMap(IAppState *appState);
        void renderChip(const field::TilePropertyChip *chip, field::FieldRenderer &renderer, IAppState *appState,
                        const Vec2<int> &screenPos);
        IMainScene* m_ParentalScene;
        field::TileMap m_TileMap;
        shared_ptr<SpriteTexture> m_Texture;
        ChildrenPool<character::CharacterBase> m_ChildrenPool{};
        TextureAnimator m_CharacterAnimator{};
    };
}


#endif //FILL_TILES_FIELDMANAGER_H
