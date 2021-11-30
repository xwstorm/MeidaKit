
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

set(COMMON_SOURCES
	${SOURCE_DIR}/base/ant_base.h
	${SOURCE_DIR}/base/ant_lock.h
	${SOURCE_DIR}/base/ant_location.h
	${SOURCE_DIR}/base/ant_message_handler.h
	${SOURCE_DIR}/base/ant_task_thread.h
	${SOURCE_DIR}/base/ant_task_thread.cpp
	${SOURCE_DIR}/base/ant_thread_message.h
	${SOURCE_DIR}/base/ant_thread_message.h
	${SOURCE_DIR}/base/ant_thread.h
	${SOURCE_DIR}/base/ant_thread.cpp
	${SOURCE_DIR}/base/event_bus.h
	${SOURCE_DIR}/base/event_bus.cpp
	${SOURCE_DIR}/base/event_box.h
	${SOURCE_DIR}/base/event_box.cpp

	${SOURCE_DIR}/media/media_manager.h
	${SOURCE_DIR}/media/media_manager.cpp
	${SOURCE_DIR}/media/video/video_capture_interface.h
	${SOURCE_DIR}/media/video/video_capture_interface.cpp

	${SOURCE_DIR}/sdk/live_engine_interface.h
	${SOURCE_DIR}/sdk/live_engine_interface.cpp
	${SOURCE_DIR}/sdk/live_engine.h
	${SOURCE_DIR}/sdk/live_engine.cpp
	${SOURCE_DIR}/sdk/live_core.h
	${SOURCE_DIR}/sdk/live_core.cpp
	)

if (MST_MACOS)
endif()

set(SOURCES ${COMMON_SOURCES})

include_directories(${SOURCE_DIR})