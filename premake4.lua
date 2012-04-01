solution "Program1"

	configurations {"Debug", "Release"}
	defines {"_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE",
			 "_SCL_SECURE_NO_WARNINGS"}

	configuration "windows"
		defines {"WIN32"}
	
	configuration "linux"
		defines {"LOAD_X11"}

	configuration "macosx"
		defines {"_NIX"}

	-- May need to clear configuration here

	project "Program1"
		language "C++"
		
		files {"src/*.cpp", "src/*.h"}
		
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
			links {"GL", "GLU"}

		configuration "macosx"
			links {"OpenGL.framework", "GLUT.framework"}
