function initX11()
    if os.is("Linux") then
        if (os.isdir("/usr/include") and os.isfile("/usr/include/X11/X.h")) then
            links{
                "dl",
                "X11",
                "Xrandr",
                "Xinerama",
                "Xi",
                "Xv",
                "Xt",
                "Xext",
                "Xmu",
                "Xtst",
                "Xxf86vm",
                "Xcursor",
                "pthread",
            }
        else
            print("No X11/X.h found, using dynamic loading of X11")
            defines {"DYNAMIC_LOAD_X11_FUNCTIONS"}
            links {"dl","pthread"}
        end
    end
end


function exampleProjectDefaults()

	-- debugdir (path.join(BGFX_DIR, "examples/runtime"))

	-- includedirs {
	-- 	path.join(BX_DIR,   "include"),
	-- 	path.join(BIMG_DIR, "include"),
	-- 	path.join(BGFX_DIR, "include"),
	-- 	path.join(BGFX_DIR, "3rdparty"),
	-- 	path.join(BGFX_DIR, "examples/common"),
	-- }

	-- flags {
	-- 	"FatalWarnings",
	-- }

	links {
		-- "example-common",
		-- "example-glue",
		-- "bgfx",
		-- "bimg_decode",
		-- "bimg",
		-- "bx",
	}

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

		configuration { "linux or freebsd" }
			if _OPTIONS["with-wayland"]  then
				links {
					"wayland-egl",
				}
			end

		configuration { "osx" }
			libdirs { "$(SDL2_DIR)/lib" }

		configuration {}
	end

	if _OPTIONS["with-glfw"] then
		defines { "ENTRY_CONFIG_USE_GLFW=1" }
		links   { "glfw3" }

		configuration { "linux or freebsd" }
			if _OPTIONS["with-wayland"] then
				links {
					"wayland-egl",
				}
			else
				links {
					"Xrandr",
					"Xinerama",
					"Xi",
					"Xxf86vm",
					"Xcursor",
				}
			end

		configuration { "osx" }
			linkoptions {
				"-framework CoreVideo",
				"-framework IOKit",
			}

		configuration {}
	end

	configuration { "vs*", "x32 or x64" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

	configuration { "vs201*", "x32 or x64" }
		linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
			"/DELAYLOAD:\"libEGL.dll\"",
			"/DELAYLOAD:\"libGLESv2.dll\"",
		}

	configuration { "mingw*" }
		targetextension ".exe"
		links {
			"gdi32",
			"psapi",
		}

	configuration { "vs20*", "x32 or x64" }
		links {
			"gdi32",
			"psapi",
		}

	configuration { "durango" }
		links {
			"d3d11_x",
			"d3d12_x",
			"combase",
			"kernelx",
		}

	configuration { "winstore*" }
		removelinks {
			"DelayImp",
			"gdi32",
			"psapi"
		}
		links {
			"d3d11",
			"d3d12",
			"dxgi"
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

	-- WinRT targets need their own output directories or build files stomp over each other
	configuration { "x32", "winstore*" }
		targetdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "obj", _name))

	configuration { "x64", "winstore*" }
		targetdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "obj", _name))

	configuration { "ARM", "winstore*" }
		targetdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "obj", _name))

	configuration { "mingw-clang" }
		kind "ConsoleApp"

	configuration { "android*" }
		kind "ConsoleApp"
		targetextension ".so"
		linkoptions {
			"-shared",
		}
		links {
			"EGL",
			"GLESv2",
		}

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"

	configuration { "linux-* or freebsd", "not linux-steamlink" }
		links {
			"X11",
			"GL",
			"pthread",
		}

	configuration { "linux-steamlink" }
		links {
			"EGL",
			"GLESv2",
			"SDL2",
			"pthread",
		}

	configuration { "rpi" }
		links {
			"X11",
			"brcmGLESv2",
			"brcmEGL",
			"bcm_host",
			"vcos",
			"vchiq_arm",
			"pthread",
		}

	configuration { "osx" }
		linkoptions {
			"-framework Cocoa",
			"-framework QuartzCore",
			"-framework OpenGL",
			"-weak_framework Metal",
		}

	configuration { "ios* or tvos*" }
		kind "ConsoleApp"
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
			"-weak_framework Metal",
		}

	configuration { "xcode4", "ios" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/iOS-Info.plist"),
		}

	configuration { "xcode4", "tvos" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/tvOS-Info.plist"),
		}


	configuration { "qnx*" }
		targetextension ""
		links {
			"EGL",
			"GLESv2",
		}

	configuration {}

	strip()
end

function exampleProject(_baseExampleDir, _prefix, ...)
    for _, name in ipairs({...}) do
        project (_prefix .. "-" .. name)
            uuid (os.uuid(_prefix .. "-" .. name))
            kind "WindowedApp"

        files {
            path.join(_baseExampleDir, name, "**.c"),
            path.join(_baseExampleDir, name, "**.cpp"),
            path.join(_baseExampleDir, name, "**.h"),
            path.join(_baseExampleDir, name, "**.hpp"),
        }

        removefiles {
            path.join(_baseExampleDir, name, "**.bin.h"),
        }

        exampleProjectDefaults()
    end

end

function dep(namespace, name, cppmodule, usage_decl, deps)
    local m = {
        project = nil,
        cppmodule = cppmodule,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        usage_decl = usage_decl,
        deps = deps,
    }

    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end

    m.project = project(m.idname)
    m.lib = {
        name = project().name,
        links = {},
        kind = "StaticLib",
    }

    if cppmodule then
        modules(m)
    end

    return m
end

function modules(m)
    if not _OPTIONS["cpp-modules"] then
        return
    end

    removeflags { "Cpp17" }
    flags {
        "CppLatest",
        --"CppModules",
    }

    defines { "_CRT_NO_VA_START_VALIDATION" }

    if _ACTION == "vs2015"
	or _ACTION == "vs2017" then
        files {
            path.join(m.path, m.dotname .. ".ixx"),
        }
    else
        files {
            path.join(m.path, m.dotname .. ".mxx"),
        }

        links {
            "std_core",
            "std_io",
            "std_threading",
            "std_regex",
        }
    end
end

function include_files(dependency, files)
    local name;
    if(type(dependency) == "string") then
        name = dependency
    else
        name = dependency.idname
    end

    local inc_dir = path.join(PROJECT_DIR, "include")
    if not os.isdir(inc_dir) then
        os.mkdir(inc_dir)
    end

    local dir = path.join(inc_dir, name)
    if not os.isdir(dir) then
        os.mkdir(dir)
    end

    for _, file in ipairs(files) do
        os.copyfile(file, dir)
    end
    return inc_dir
end
