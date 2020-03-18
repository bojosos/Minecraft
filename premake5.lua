workspace "Minecraft"
	architecture "x86_64"
	startproject "Minecraft"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Minecraft/vendor/GLFW/include"
IncludeDir["Glad"] = "Minecraft/vendor/Glad/include"
IncludeDir["freetypegl"] = "Minecraft/vendor/freetype-gl"
IncludeDir["glm"] = "Minecraft/vendor/glm"
IncludeDir["stb_image"] = "Minecraft/vendor/stb_image"
IncludeDir["lua"] = "Minecraft/vendor/lua/include"
IncludeDir["sol"] = "Minecraft/vendor/sol"

group "Dependencies"
	include "Minecraft/vendor/GLFW"
	include "Minecraft/vendor/Glad"
	include "Minecraft/vendor/FreeType"
	include "Minecraft/vendor/freetype-gl"
	include "Minecraft/vendor/lua"

group ""

project "Minecraft"
	location "Minecraft"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mcpch.h"
	pchsource "Minecraft/src/mcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/freetype-gl/freetype-gl.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/sol/sol.hpp",
		"%{prj.name}/res/**",
		"%{prj.name}/lua/**"
	}

	defines
	{
		"_CRT_NONSTDC_NO_DEPRECATE",
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.freetypegl}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.lua}",
		"%{IncludeDir.sol}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"lua",
		"freetype-gl",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MC_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"MC_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MC_RELEASE"
		runtime "Release"
		optimize "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Minecraft/vendor/spdlog/include",
		"Minecraft/src",
		"Minecraft/vendor",
		"%{IncludeDir.glm}"
	}
