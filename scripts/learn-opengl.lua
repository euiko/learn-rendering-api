require 'utils/inspect'
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
        path.join(LOPENGL_SRC_DIR, "*.h"),
    }

    links {
        "X11",
        "GL",
        "GLEW",
        "pthread",
        "glfw",
        -- "pstl",
    }

    buildoptions {
        "-std=c++17",
        "-fopenmp-simd",
        "-fno-rtti",
        "-fno-exceptions",
    }

matches = os.matchdirs(path.join(LOPENGL_SRC_DIR, "*"))
-- printtable("halo", matches)
for _,dir in ipairs(matches) do
    name = path.getrelative(LOPENGL_SRC_DIR, dir)
    exampleProject(LOPENGL_SRC_DIR, "learn-opengl", name)
    copyResource(os.matchdirs(dir .. "/*"), target, name)
    -- files {
    --     path.join(LOPENGL_SRC_DIR, name, "**.glsl")
    -- }
    includedirs {
        STB_INC_DIR,
        GLM_INC_DIR,
    }

    links {
        "learn-opengl",
        "X11",
        "GL",
        "GLEW",
        "pthread",
        "glfw",
        "3rdparty_stb",
        "3rdparty_glm"
        -- "pstl",
    }

    -- print(path.join(dir, "shaders"))
    -- if os.isdir(path.join(dir, "shaders")) then
    --     postbuildcommands ("cp -R " .. path.join(dir, "shaders") .. " " .. path.join(LOPENGL_SRC_DIR, "shaders", name))
    -- end
    -- print(path.join(LOPENGL_SRC_DIR, "shaders", name))
    -- prebuildcommands("echo \"Copying resource to $(TARGETDIR);\"")
    -- local currentProject = project( "learn-opuengl-" .. name)
    -- for key, value in pairs(currentProject.solution.blocks) do
    --     for k, v in pairs(value) do
    --         -- print(k, v)
    --     end
    -- end
    -- print()
    -- printtable("a", _OPTIONS)
    -- printtable(name, shaders)
    buildoptions {
        "-std=c++17",
        "-fopenmp-simd",
        "-fno-rtti",
        "-fno-exceptions",
    }
end