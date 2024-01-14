# Lovato Emanuele

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(monopoly)

include_directories(include)

add_executable(maintest
	src/MainTest.cpp
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

target_link_libraries(maintest
	game
	board
	casella
	player
	logger
	posizione
	dadi
)
