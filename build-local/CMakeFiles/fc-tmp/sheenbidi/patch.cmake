cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for sheenbidi")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "/home/zaheer-abbas/Games/youtube/game 1/build-local/_deps/sheenbidi-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[/usr/bin/cmake]====] [====[-DSHEENBIDI_DIR=/home/zaheer-abbas/Games/youtube/game 1/build-local/_deps/sheenbidi-src]====] [====[-P]====] [====[/home/zaheer-abbas/Games/youtube/game 1/build/_deps/sfml-src/tools/sheenbidi/PatchSheenBidi.cmake]====]
)

endblock()
