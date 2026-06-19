set(TARGET_NAME mario_fake)
set(SOURCES 
        main.cpp

        GameEngine/Input/InputManager.cpp
        GameEngine/Input/InputAction.cpp
        GameEngine/GameEngine.cpp
        GameEngine/Scene.cpp
        GameEngine/Assets/AssetManager.cpp
        GameEngine/Assets/Animation.cpp

        Sample/Components/KillMeComponent.h
        Sample/Components/SpriteComponent.h

        Sample/Scenes/MenuScene.cpp

        Sample/Systems/DrawSystem.cpp
        Sample/Systems/KillerSystem.cpp
        Sample/Systems/MenuInitSystem.cpp
        Sample/Systems/AnimationSystem.cpp
        Sample/Systems/ButtonStateSystem.cpp
        Sample/Systems/MenuInitSystem.cpp

        Sample/ButtonEvents.cpp
)

add_subdirectory(Ecs)

add_executable(${TARGET_NAME} 
    ${SOURCES})

target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(${TARGET_NAME} PRIVATE -g3 -O0)
# target_compile_options(${TARGET_NAME} PRIVATE -Ofast)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC ${ECS_LIB_NAME})
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(${TARGET_NAME} PUBLIC nlohmann_json::nlohmann_json)