solution "SDProject"

	configurations {"Debug", "Release"}
	defines {"_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE",
			 "_SCL_SECURE_NO_WARNINGS"}

	configuration "windows"
		defines {"WIN32"}
	
	configuration "linux"
		defines {"_NIX"}

	configuration "macosx"
		defines {"MACOSX"}

	-- May need to clear configuration here

	project "SDProject"
		language "C++"
		
		files {"src/**.h", "src/**.c", "src/**.cc", "src/**.cpp"}
		
		targetdir "bin"
		objdir "obj"

		includedirs {"inc"}
		libdirs {"lib"}

		configuration "Debug"
			kind "ConsoleApp"
			defines {"DEBUG", "DEBUG_SHADERS"}
			flags {"Symbols"}
			targetsuffix "D"

		configuration "Release"
			kind "WindowedApp"
			defines {"RELEASE"}
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings",
				   "NoEditAndContinue"}

		configuration "windows"
			links {"glu32", "opengl32", "gdi32", "winmm", "user32"}

		configuration "linux"
			links {"GLEW", "GL", "GLU", "sfml-graphics", "sfml-window",
				   "sfml-audio", "sfml-system", "sfml-graphics"}

		configuration "macosx"
			links {"OpenGL.framework","SFML.framework",
				   "SFML-window.framework", "SFML-audio.framework",
			"SFML-system.framework", "SFML-graphics.framework", "Carbon.framework"}
