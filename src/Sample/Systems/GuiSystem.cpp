#include "GuiSystem.h"
#include <bit>
#include <cxxabi.h>
#include "imgui.h"

std::string GuiSystem::_GetDemangleNameById(int storageId)
{
    static int status {0};
    auto ptr = world.GetStorageById(storageId).get();
    auto mangleName = typeid(*ptr).name();
    char* name = abi::__cxa_demangle(mangleName, 0, 0, &status);
    std::string output { status ? mangleName : name };
    free(name);
    return output;
}


void GuiSystem::OnUpdate(float)
{
    ImGui::Begin("Rin's Gui");

    if (ImGui::TreeNode("Entities"))
    {
        for (const auto& entity: world.GetEntities())
        {
            if (world.IsEntityAlive(entity.Id))
            {
                ImGui::PushID(entity.Id);
                if (ImGui::TreeNode("", "Entity #%d", entity.Id))
                {
                    auto components = entity.Components();
                    while (components)
                    {
                        auto storageId = std::countr_zero(components);
                        components &= components - 1;
                        ImGui::BulletText("%s", _GetDemangleNameById(storageId).c_str());
                    }
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        }
        ImGui::TreePop();
    }

    ImGui::Checkbox("Show graphics", &_isDrawShown);
    ImGui::Checkbox("Show grid", &_isGridShown);
    ImGui::Checkbox("Show colliders", &_isBoxShown);

    ImGui::End();
}