require 'utils/inspect'
group "3rdparty"
-- dofile "3rdparty/cereal.lua"
-- dofile "3rdparty/pstl.lua"
project "learn-opengl"
  	language "C++"
    kind     "ConsoleApp"

    LOPENGL_SRC_DIR = path.join(PROJECT_DIR, "src/learn-opengl")
    LOPENGL_INC_DIR = path.join(PROJECT_DIR, "include")

    includedirs {
        "/usr/include",
        LOPENGL_SRC_DIR,
    }

    files {
        path.join(LOPENGL_SRC_DIR, "*.cpp"),
    }

    matches = os.matchdirs(path.join(LOPENGL_SRC_DIR, "*"))
    -- printtable("halo", matches)
    for _,dir in ipairs(matches) do
        name = path.getrelative(LOPENGL_SRC_DIR, dir)
        exampleProject(LOPENGL_SRC_DIR, "learn-opengl", name);
        links {
            "X11",
            "GL",
            "pthread",
            "glut",
            -- "pstl",
        }
    end


    buildoptions {
        "-std=c++17",
        "-fopenmp-simd",
        "-fno-rtti",
        "-fno-exceptions",
    }