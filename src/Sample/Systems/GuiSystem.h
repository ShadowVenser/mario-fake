#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"


class GuiSystem final : public ISystem {
private:
    GameEngine& _engine;
    std::string _GetDemangleNameById(int storageId);

    bool& _isDrawShown;
    bool& _isGridShown;
    bool& _isBoxShown;
public:
    GuiSystem(World &world, GameEngine& engine, bool& isDS, bool& isGS, bool& isBS): 
        ISystem(world),
        _engine(engine), 
        _isDrawShown(isDS),
        _isGridShown(isGS),
        _isBoxShown(isBS)
    {  }

    void OnInit() override { }

    void OnUpdate(float) override;
};
