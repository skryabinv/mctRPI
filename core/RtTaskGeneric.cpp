#include "RtTaskGeneric.h"

namespace core {

bool RtTaskGeneric::runImpl()
{
    return mTask(*this);
}

}
