cmake_minimum_required(VERSION 3.16)

project(GroceryManagement LANGUAGES C)

add_executable(GroceryManagement main.c
    user.h
    user.c

    inventory.h
    inventory.c
    cart.h
    cart.c
    billing.h
    billing.c
    report.h
    report.c
    start.h
    start.c
    file_operations.h
    file_operations.c
    enum.h)

include(GNUInstallDirs)
install(TARGETS GroceryManagement
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
