//
// Created by sashi0034 on 2022/05/14.
//

#include "log.h"
#include "GraphBlend.h"

namespace gameEngine
{
    GraphBlend::GraphBlend()
    = default;

    GraphBlend::GraphBlend(int pal)
    {
        SetPal(pal);
    }

    GraphBlend::GraphBlend(int mode, int pal)
    {
        m_Mode = mode;
        SetPal(pal);
    }

    void GraphBlend::GetMode(int mode)
    {
        m_Mode = mode;
    }

    int GraphBlend::GetMode() const
    {
        return m_Mode;
    }

    void GraphBlend::SetPal(int pal)
    {
#ifdef DEBUG_BUILD
        if (pal<0 || 255<pal)
        {
            LOG_CERR << "BlendPal: " << pal << " Is Out Of Range" << std::endl ;
        }
#endif
        m_Pal = std::max(0, std::min(255, pal));
    }

    int GraphBlend::GetPal() const
    {
        return m_Pal;
    }

}
