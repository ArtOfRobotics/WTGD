#include "../../include.h"

using namespace std;

std_msgs::ColorRGBA ledValue;

LedController::LedController()
{
    printf("Er is een nieuwe Led controller aangemaakt!\n");
}

void LedController::LedCallback(const std_msgs::Char input)
{
    std::cout << "Hey, listen!" << std::endl;

    if (input.data == 'r')
    {
        ledValue.r = 255;
        ledValue.g = 0;
        ledValue.b = 0;
        ledValue.a = 255;
        printf("Turn led red\n");
        GeneralController::GetLedPublisher().publish(ledValue);
    }

    if (input.data == 'g')
    {
        ledValue.r = 0;
        ledValue.g = 255;
        ledValue.b = 0;
        ledValue.a = 255;
        printf("Turn led green\n");
        GeneralController::GetLedPublisher().publish(ledValue);
    }

    if (input.data == 'b')
    {
        ledValue.r = 0;
        ledValue.g = 0;
        ledValue.b = 255;
        ledValue.a = 255;
        printf("Turn led blue\n");
        GeneralController::GetLedPublisher().publish(ledValue);
    }

    if (input.data == 'y')
    {
        ledValue.r = 0;
        ledValue.g = 0;
        ledValue.b = 0;
        ledValue.a = 0;
        printf("Turn everything off\n");
        GeneralController::GetLedPublisher().publish(ledValue);
    }
}