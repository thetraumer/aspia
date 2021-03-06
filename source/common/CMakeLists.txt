#
# Aspia Project
# Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
#

include(translations)

list(APPEND SOURCE_COMMON
    clipboard.cc
    clipboard.h
    desktop_session_constants.cc
    desktop_session_constants.h
    file_depacketizer.cc
    file_depacketizer.h
    file_packet.h
    file_packetizer.cc
    file_packetizer.h
    file_platform_util.h
    file_task.cc
    file_task.h
    file_task_consumer.h
    file_task_consumer_proxy.cc
    file_task_consumer_proxy.h
    file_task_factory.cc
    file_task_factory.h
    file_task_producer.h
    file_task_producer_proxy.cc
    file_task_producer_proxy.h
    file_worker.cc
    file_worker.h
    keycode_converter.cc
    keycode_converter.h
    session_type.cc
    session_type.h)

if (WIN32)
    list(APPEND SOURCE_COMMON
        file_platform_util_win.cc)
endif()

if (LINUX)
    list(APPEND SOURCE_COMMON
        file_platform_util_linux.cc)
endif()

if (APPLE)
    list(APPEND SOURCE_COMMON
        file_platform_util_mac.mm)
endif()

list(APPEND SOURCE_COMMON_UI
    ui/about_dialog.cc
    ui/about_dialog.h
    ui/about_dialog.ui
    ui/download_dialog.cc
    ui/download_dialog.h
    ui/download_dialog.ui
    ui/language_action.cc
    ui/language_action.h
    ui/update_checker.cc
    ui/update_checker.h
    ui/update_checker_impl.cc
    ui/update_checker_impl.h
    ui/update_dialog.cc
    ui/update_dialog.h
    ui/update_dialog.ui
    ui/update_info.cc
    ui/update_info.h)

if (WIN32)
    list(APPEND SOURCE_COMMON_WIN
        win/file_enumerator.cc
        win/file_enumerator.h)
endif()

list(APPEND SOURCE_COMMON_RESOURCES
    resources/common.qrc)

source_group("" FILES ${SOURCE_COMMON})
source_group(ui FILES ${SOURCE_COMMON_UI})
source_group(resources FILES ${SOURCE_COMMON_RESOURCES})

if (WIN32)
    source_group(win FILES ${SOURCE_COMMON_WIN})
endif()

add_library(aspia_common STATIC
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_UI}
    ${SOURCE_COMMON_WIN}
    ${SOURCE_COMMON_RESOURCES})
target_link_libraries(aspia_common
    aspia_base
    aspia_proto
    ${QT_COMMON_LIBS}
    ${QT_PLATFORM_LIBS}
    ${THIRD_PARTY_LIBS})
set_property(TARGET aspia_common PROPERTY AUTOMOC ON)
set_property(TARGET aspia_common PROPERTY AUTOUIC ON)
set_property(TARGET aspia_common PROPERTY AUTORCC ON)

if(Qt5LinguistTools_FOUND)
    # Get the list of translation files.
    file(GLOB COMMON_TS_FILES translations/*.ts)
    add_translations(aspia_common QRC_FILE "translations/common_translations.qrc" TS_FILES ${COMMON_TS_FILES})

    # Get the list of files containing messages.
    file(GLOB_RECURSE COMMON_TR_SOURCES
        ${PROJECT_SOURCE_DIR}/common/*.cc
        ${PROJECT_SOURCE_DIR}/common/*.cpp
        ${PROJECT_SOURCE_DIR}/common/*.h
        ${PROJECT_SOURCE_DIR}/common/*.ui)

    create_translation(TS_COMMON_UPDATE ${COMMON_TR_SOURCES} ${COMMON_TS_FILES})
    add_custom_target(aspia_common_ts_update DEPENDS ${TS_COMMON_UPDATE})
else()
    message(WARNING "Qt5 linguist tools not found. Internationalization support will be disabled.")
endif()
