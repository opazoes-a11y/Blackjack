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

    -- Solo los .cc del ejecutable
    files {
        "main.cc",
        "game.cc",
        "cards.cc",
        "dealer.cc",
        "player.cc"
    }

    -- Carpeta raíz para todos los .h (incluye zagerfe_player.h)
    includedirs {
        "."
    }

    -- Donde está el .lib externo
    libdirs {
        "."   
    }

    -- Librerías a enlazar
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
