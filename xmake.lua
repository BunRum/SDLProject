--#selene: allow(undefined_variable)
add_rules("mode.debug", "mode.release")


local sdlpath = "./SDL"

add_requires("libsdl")
add_requires("libsdl_image")
set_config("yes", true)

function SDL()
    -- add_includedirs(sdlpath .. "/include")
    add_packages("libsdl")
    add_packages("libsdl_image")
end

target("hello")
    set_kind("binary")
    add_files("*.cpp")
    SDL()