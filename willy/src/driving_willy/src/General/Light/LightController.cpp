#include "../../include.h"

using namespace std;

LightController::LightController()
{
    printf("Er is een nieuwe Light controller aangemaakt!\n");
}

void LightController::LightCallback(const std_msgs::Char &msg)
{
    std::cout << "Hey, listen!" << std::endl;

    if (input.data == 'o')
    {
        printf("Turn siren on\n");
        GeneralController::GetSirenPublisher().publish(true);
    }

    if (input.data == 'p')
    {
        printf("Turn siren off\n");
        GeneralController::GetSirenPublisher().publish(false);
    }
}