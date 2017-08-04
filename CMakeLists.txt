cmake_minimum_required (VERSION 2.6)
project (UE4)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

include("/Users/wrose/dev/unreal/BuildingEscape/Intermediate/ProjectFiles/IncludeDirectories.cmake")
include("/Users/wrose/dev/unreal/BuildingEscape/Intermediate/ProjectFiles/Definitions.cmake")
include("/Users/wrose/dev/unreal/BuildingEscape/Intermediate/ProjectFiles/BuildingEscapeEditor.cmake")

set(MONO_ROOT_PATH "/Applications/UE_4.16/Engine/Binaries/DotNET")
set(BUILD cd "${MONO_ROOT_PATH}")

# Custom target for BuildingEscapeEditor project, Development configuration
add_custom_target(BuildingEscapeEditor-Development ${BUILD} && mono UnrealBuildTool.exe BuildingEscapeEditor Mac Development -project="/Users/wrose/dev/unreal/BuildingEscape/BuildingEscape.uproject" -game -progress)
add_custom_target(BuildingEscapeEditor-Development-CLEAN ${BUILD} && mono UnrealBuildTool.exe BuildingEscapeEditor Mac Development -project="/Users/wrose/dev/unreal/BuildingEscape/BuildingEscape.uproject" -clean)

add_executable(PleaseIgnoreMe ${BuildingEscapeEditor_FILES})