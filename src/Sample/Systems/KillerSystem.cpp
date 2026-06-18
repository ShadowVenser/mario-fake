#include "KillerSystem.h"

void KillerSystem::OnInit()
{

}

void KillerSystem::OnUpdate(float)
{
    while (_clients.Count()){
        world.RemoveEntity(_clients.Entities()[0]);
    }
}
