# Source files
list(APPEND SRCS Application.cpp)
list(APPEND SRCS DatabaseManager.cpp)
list(APPEND SRCS DatabaseManager_delete.cpp)
list(APPEND SRCS DatabaseManager_getters.cpp)
list(APPEND SRCS DatabaseManager_insert.cpp)
list(APPEND SRCS DatabaseManager_update.cpp)
list(APPEND SRCS MacawDebug.cpp)
list(APPEND SRCS MainWindow.cpp)
list(APPEND SRCS ServicesManager.cpp)
list(APPEND SRCS main.cpp)
list(APPEND SRCS Dialogs/MovieDialog.cpp)
list(APPEND SRCS Dialogs/PeopleDialog.cpp)
list(APPEND SRCS Dialogs/SettingsWindow.cpp)
list(APPEND SRCS Entities/Entity.cpp)
list(APPEND SRCS Entities/Movie.cpp)
list(APPEND SRCS Entities/People.cpp)
list(APPEND SRCS Entities/Playlist.cpp)
list(APPEND SRCS Entities/Tag.cpp)
list(APPEND SRCS FetchMetadata/FetchMetadata.cpp)
list(APPEND SRCS FetchMetadata/FetchMetadataDialog.cpp)
list(APPEND SRCS FetchMetadata/FetchMetadataQuery.cpp)
list(APPEND SRCS MainWindowWidgets/LeftPannel.cpp)
list(APPEND SRCS MainWindowWidgets/MainPannel.cpp)
list(APPEND SRCS MainWindowWidgets/MetadataPannel.cpp)
list(APPEND SRCS MainWindowWidgets/MoviesPannel.cpp)


# Forms
list(APPEND FORMS MainWindow.ui)
list(APPEND FORMS Dialogs/SettingsWindow.ui)
list(APPEND FORMS Dialogs/MovieDialog.ui)
list(APPEND FORMS Dialogs/PeopleDialog.ui)
list(APPEND FORMS FetchMetadata/FetchMetadataDialog.ui)
list(APPEND FORMS MainWindowWidgets/LeftPannel.ui)
list(APPEND FORMS MainWindowWidgets/MetadataPannel.ui)
list(APPEND FORMS MainWindowWidgets/MoviesPannel.ui)


# Resources
list(APPEND RSRCS resources.qrc)



include_directories(".")
qt5_add_resources(RSRCS_RCC ${RSRCS})
qt5_wrap_ui(FORMS_MOC ${FORMS})
add_executable(${EXECUTABLE_NAME} ${SRCS} ${RSRCS_RCC} ${FORMS_MOC})
qt5_use_modules(${EXECUTABLE_NAME} Widgets Network Sql)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)

