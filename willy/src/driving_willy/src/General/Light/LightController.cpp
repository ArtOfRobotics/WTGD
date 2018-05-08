#include "../../include.h"

using namespace std;

std_msgs::Bool sirenValueOn;
std_msgs::Bool sirenValueOff;

LightController::LightController()
{
    printf("Er is een nieuwe Light controller aangemaakt!\n");
}

void LightController::LightCallback(const std_msgs::Char &msg)
{
    sirenValueOn.data = true;
    sirenValueOff.data = false;
    std::cout << "Hey, listen!" << std::endl;

    if (input.data == 'o')
    {
        printf("Turn siren on\n");
        GeneralController::GetSirenPublisher().publish(sirenValueOn);
    }

    if (input.data == 'p')
    {
        printf("Turn siren off\n");
        GeneralController::GetSirenPublisher().publish(sirenValueOff);
    }
}