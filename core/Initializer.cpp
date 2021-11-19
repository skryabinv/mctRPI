#include "Initializer.h"
#include "Board.h"
#include "GPIO.h"

namespace core {

Initializer::Initializer()
{
    Board::initInstance();
    gpio::initialize();
}

Initializer::~Initializer()
{
    // Деинициализация
}

} // namespace core
