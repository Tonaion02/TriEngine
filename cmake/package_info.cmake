set(PACKAGE_NAME "triEngine")
set(PACKAGE_EXE_NAME "triengine")
set(PACKAGE_VENDOR "Tonaion")
set(PACKAGE_COPYRIGHT "Copyright ©2019-2020 ${PACKAGE_VENDOR}")
set(PACKAGE_DESCRIPTION "TriEngine")
set(PACKAGE_HOMEPAGE "https://ncine.github.io")
set(PACKAGE_REVERSE_DNS "io.github.ncine.nctemplate")

set(PACKAGE_INCLUDE_DIRS src)

set(PACKAGE_SOURCES
	src/main.h
	src/main.cpp

	src/PrecompiledHeaders.h	
	src/PrecompiledHeaders.cpp	
	src/AddonsString.h
	src/AddonsString.cpp
	src/Image.cpp
	src/Image.h
	src/Player.cpp
	src/Player.h
	src/StaticImage.h
	src/StaticImage.cpp
	
	src/vendor/stdbimage.cpp
	
	src/Animation/Animation.h
	src/Animation/Animation.cpp
	
	src/Input/CoolDownCommand.h
	src/Input/Input.h
	src/Input/Input.cpp
	
	src/Item/Item.h
	src/Item/Item.cpp

	src/Menu/Menu.h
	src/Menu/Menu.cpp

	src/Renderer/Camera.h
	src/Renderer/Camera.cpp
	src/Renderer/DebugLayer.h
	src/Renderer/DebugLayer.cpp
	src/Renderer/Options.h
	src/Renderer/Options.cpp
	src/Renderer/Renderer.h
	src/Renderer/Renderer.cpp	

	src/world/Level.h
	src/world/Level.cpp
	src/world/LogicTile.h
	src/world/LogicTile.cpp
	src/world/Matrix.h
	src/world/Matrix.cpp
	src/world/World.h
	src/world/World.cpp

)

function(callback_end)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	file(GLOB ANIMATION_FILES "src/Animation/*.h" "src/Animation/*.cpp")
	source_group("Animation" FILES ${ANIMATION_FILES})

	file(GLOB INPUT_FILES "src/Input/*.h" "src/Input/*.cpp")
	source_group("Input" FILES ${INPUT_FILES})

	file(GLOB ITEM_FILES "src/item/*.h" "src/item/*.cpp")
	source_group("item" FILES ${ITEM_FILES})

	file(GLOB MENU_FILES "src/Menu/*.h" "src/Menu/*.cpp")
	source_group("Menu" FILES ${MENU_FILES})

	file(GLOB RENDERER_FILES "src/Renderer/*.h" "src/Renderer/*.cpp")
	source_group("Renderer" FILES ${RENDERER_FILES})

	file(GLOB VFX_FILES "src/vfx/*.h" "src/vfx/*.cpp")
	source_group("vfx" FILES ${VFX_FILES})

	file(GLOB WORLD_FILES "src/world/*.h" "src/world/*.cpp")
	source_group("world" FILES ${WORLD_FILES})
endfunction()