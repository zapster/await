cmake_minimum_required(VERSION 3.10)

# set the project name
project(await)

# add the executable
add_executable(push src/push.c src/await.c)
add_executable(pop src/pop.c src/await.c)
add_executable(server src/server.c src/await.c)
