target_sources(${PROJECT_NAME} PRIVATE
    "Client.cpp"
)

add_subdirectory(Mem)
add_subdirectory(Utils)

add_subdirectory(Game)
add_subdirectory(Context)