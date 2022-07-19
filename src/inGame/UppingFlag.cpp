//
// Created by sashi0034 on 2022/07/19.
//

#include "cassert"
#include "UppingFlag.h"

namespace inGame{

    bool UppingFlag::IsUpping() const
    {
        return isUpping;
    }

    void UppingFlag::DownFlag()
    {
        assert(isUpping);
        isUpping = false;
    }
}
