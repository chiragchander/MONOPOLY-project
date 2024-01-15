# Lovato Emanuele

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(monopoly)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)	# In caso di mancata specificazione, compila versione Release.
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")	# Flags comuni per mostrare i warning in compilazione.
set(CMAKE_CXX_FLAGS_DEBUG "-g")		# Parametro -g serve per compilare includendo informazioni di debug.
set(CMAKE_CXX_FLAGS_RELEASE "-O2")	# Parametro -O2 del compilatore, per ottimizzazione.

include_directories(include)

add_executable(monopoly
	src/Monopoly.cpp
)

add_library(game
	include/Game.h
	src/Game.cpp
)

add_library(board
	include/Board.h
	src/Board.cpp
)

add_library(casella
	include/Casella.h
	src/Casella.cpp
)

add_library(player
	include/Player.h
	src/Player.cpp
)

add_library(logger
	include/Logger.h
	src/Logger.cpp
)

add_library(posizione
	include/Posizione.h
	src/Posizione.cpp
)

add_library(dadi
	include/Dadi.h
	src/Dadi.cpp
)

target_link_libraries(monopoly
	game
	board
	casella
	player
	logger
	posizione
	dadi
)
