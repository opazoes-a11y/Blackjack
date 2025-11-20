workspace "Blackjack"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Blackjack"
    location "build"

------------------------
-- Executable: Blackjack
------------------------
project "Blackjack"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    -- Source files for the NewBJ implementation
    files {
        "NewBJ/main.cc",
        "NewBJ/jaco_game.cc",
        "NewBJ/jaco_table.cc",
        "NewBJ/jaco_player.cc",
        "NewBJ/cards.cc",
        "NewBJ/jaco_rules.cc"
    }

    -- Root include dirs for headers
    includedirs {
        ".",
        "NewBJ",
        "Interface"
    }

    -- External lib dirs (none required currently)
    libdirs {
        "."
    }

    -- Libraries to link (empty placeholder)
    links {
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"
