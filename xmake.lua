add_rules("mode.debug", "mode.release")

add_requires("spdlog", "sfml")

set_runtimes("MD")

target("TicTacToe")
    set_version("1.0.0")

    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_includedirs("include/")

    add_packages("spdlog", "sfml") 
    add_syslinks("opengl32")
    set_symbols("debug")