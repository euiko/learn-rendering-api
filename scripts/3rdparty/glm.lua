-- glm = dependency("3rdparty", "glm", true)
--     kind    "StaticLib"

    GLM_DIR = path.join(LRA_3RDPARTY, "glm")
    GLM_SRC_DIR = path.join(GLM_DIR, "glm")
    GLM_INC_DIR = GLM_DIR

    -- files {
    --     -- path.join(GLM_SRC_DIR, "**.h"),
    --     -- path.join(GLM_SRC_DIR, "**.hpp")
    -- }

    -- includedirs {
    --     GLM_INC_DIR
    -- }