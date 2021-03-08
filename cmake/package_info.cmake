set(PACKAGE_NAME "triEngine")
set(PACKAGE_EXE_NAME "triengine")
set(PACKAGE_VENDOR "Tonaion")
set(PACKAGE_COPYRIGHT "Copyright ©2019-2020 ${PACKAGE_VENDOR}")
set(PACKAGE_DESCRIPTION "TriEngine")
set(PACKAGE_HOMEPAGE "https://ncine.github.io")
set(PACKAGE_REVERSE_DNS "io.github.ncine.nctemplate")

set(PACKAGE_INCLUDE_DIRS include src)

set(PACKAGE_SOURCES
	include/main.h
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
