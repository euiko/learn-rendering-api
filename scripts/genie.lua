solution "LearnRenderingApi_sln"

	configurations {
		"Debug",
		"Release",
	}
	platforms {
		"x64",
		"x32",
		"native",
	}

	language "C++"
	-- flags {
	-- 	"RTTI",
	-- }


PROJECT_DIR = path.getabsolute("..")
BUILD_DIR = path.join(PROJECT_DIR, "build")
LRA_3RDPARTY = path.join(PROJECT_DIR, "3rdparty")

dofile "options.lua"
dofile "toolchain.lua"
toolchain(BUILD_DIR, LRA_3RDPARTY)
dofile "utils/module.lua"

group "bin"
dofile "learn-opengl.lua"

