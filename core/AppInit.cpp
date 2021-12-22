#include "AppInit.h"
#include "Board.h"
#include "GPIO.h"
#include "RtTaskDispatcher.h"
#include "Delay.h"

namespace core {

AppInit::AppInit()
{
    Board::initInstance();
    gpio::initialize();
    RtTaskDispatcher::getInstance().exec();
    RtTaskDispatcher::getInstance().scheduleTask(delay::createCalibrationTask());
}

AppInit::~AppInit()
{
    // Деинициализация
    RtTaskDispatcher::getInstance().scheduleEndTask();    
    system("shutdown -P now");
}

} // namespace core
