
SET(TARGET_NAME flutter_fml)
SET(FLUTTER_FML_SRC_DIR .)
SET(FLUTTER_FML_SRC
    ${FLUTTER_FML_SRC_DIR}/ascii_trie.cc
    ${FLUTTER_FML_SRC_DIR}/ascii_trie.h
    ${FLUTTER_FML_SRC_DIR}/backtrace.h
    ${FLUTTER_FML_SRC_DIR}/base32.cc
    ${FLUTTER_FML_SRC_DIR}/base32.h
    ${FLUTTER_FML_SRC_DIR}/build_config.h
    ${FLUTTER_FML_SRC_DIR}/closure.h
    ${FLUTTER_FML_SRC_DIR}/compiler_specific.h
    ${FLUTTER_FML_SRC_DIR}/concurrent_message_loop.cc
    ${FLUTTER_FML_SRC_DIR}/concurrent_message_loop.h
    ${FLUTTER_FML_SRC_DIR}/delayed_task.cc
    ${FLUTTER_FML_SRC_DIR}/delayed_task.h
    ${FLUTTER_FML_SRC_DIR}/eintr_wrapper.h
    ${FLUTTER_FML_SRC_DIR}/file.cc
    ${FLUTTER_FML_SRC_DIR}/file.h
    ${FLUTTER_FML_SRC_DIR}/hash_combine.h
    ${FLUTTER_FML_SRC_DIR}/log_level.h
    ${FLUTTER_FML_SRC_DIR}/log_settings.cc
    ${FLUTTER_FML_SRC_DIR}/log_settings.h
    ${FLUTTER_FML_SRC_DIR}/log_settings_state.cc
    ${FLUTTER_FML_SRC_DIR}/logging.cc
    ${FLUTTER_FML_SRC_DIR}/logging.h
    ${FLUTTER_FML_SRC_DIR}/make_copyable.h
    ${FLUTTER_FML_SRC_DIR}/mapping.cc
    ${FLUTTER_FML_SRC_DIR}/mapping.h
    ${FLUTTER_FML_SRC_DIR}/memory/ref_counted.h
    ${FLUTTER_FML_SRC_DIR}/memory/ref_counted_internal.h
    ${FLUTTER_FML_SRC_DIR}/memory/ref_ptr.h
    ${FLUTTER_FML_SRC_DIR}/memory/ref_ptr_internal.h
    ${FLUTTER_FML_SRC_DIR}/memory/task_runner_checker.cc
    ${FLUTTER_FML_SRC_DIR}/memory/task_runner_checker.h
    ${FLUTTER_FML_SRC_DIR}/memory/thread_checker.h
    ${FLUTTER_FML_SRC_DIR}/memory/weak_ptr.h
    ${FLUTTER_FML_SRC_DIR}/memory/weak_ptr_internal.cc
    ${FLUTTER_FML_SRC_DIR}/memory/weak_ptr_internal.h
    ${FLUTTER_FML_SRC_DIR}/message_loop.cc
    ${FLUTTER_FML_SRC_DIR}/message_loop.h
    ${FLUTTER_FML_SRC_DIR}/message_loop_impl.cc
    ${FLUTTER_FML_SRC_DIR}/message_loop_impl.h
    ${FLUTTER_FML_SRC_DIR}/message_loop_task_queues.cc
    ${FLUTTER_FML_SRC_DIR}/message_loop_task_queues.h
    ${FLUTTER_FML_SRC_DIR}/native_library.h
    ${FLUTTER_FML_SRC_DIR}/paths.cc
    ${FLUTTER_FML_SRC_DIR}/paths.h
    ${FLUTTER_FML_SRC_DIR}/posix_wrappers.h
    ${FLUTTER_FML_SRC_DIR}/raster_thread_merger.cc
    ${FLUTTER_FML_SRC_DIR}/raster_thread_merger.h
    ${FLUTTER_FML_SRC_DIR}/size.h
    ${FLUTTER_FML_SRC_DIR}/synchronization/atomic_object.h
    ${FLUTTER_FML_SRC_DIR}/synchronization/count_down_latch.cc
    ${FLUTTER_FML_SRC_DIR}/synchronization/count_down_latch.h
    ${FLUTTER_FML_SRC_DIR}/synchronization/semaphore.cc
    ${FLUTTER_FML_SRC_DIR}/synchronization/semaphore.h
    ${FLUTTER_FML_SRC_DIR}/synchronization/shared_mutex.h
    ${FLUTTER_FML_SRC_DIR}/synchronization/sync_switch.cc
    ${FLUTTER_FML_SRC_DIR}/synchronization/sync_switch.h
    ${FLUTTER_FML_SRC_DIR}/synchronization/waitable_event.cc
    ${FLUTTER_FML_SRC_DIR}/synchronization/waitable_event.h
    ${FLUTTER_FML_SRC_DIR}/task_queue_id.h
    ${FLUTTER_FML_SRC_DIR}/task_runner.cc
    ${FLUTTER_FML_SRC_DIR}/task_runner.h
    ${FLUTTER_FML_SRC_DIR}/task_source.cc
    ${FLUTTER_FML_SRC_DIR}/task_source.h
    ${FLUTTER_FML_SRC_DIR}/thread.cc
    ${FLUTTER_FML_SRC_DIR}/thread.h
    ${FLUTTER_FML_SRC_DIR}/thread_local.cc
    ${FLUTTER_FML_SRC_DIR}/thread_local.h
    ${FLUTTER_FML_SRC_DIR}/time/time_delta.h
    ${FLUTTER_FML_SRC_DIR}/time/time_point.cc
    ${FLUTTER_FML_SRC_DIR}/time/time_point.h
    ${FLUTTER_FML_SRC_DIR}/unique_fd.cc
    ${FLUTTER_FML_SRC_DIR}/unique_fd.h
    ${FLUTTER_FML_SRC_DIR}/unique_object.h
    ${FLUTTER_FML_SRC_DIR}/wakeable.h
    )

if (WIN32)
    SET(FLUTTER_FML_SRC ${FLUTTER_FML_SRC}
        #${FLUTTER_FML_SRC_DIR}/platform/win/errors_win.cc
        #${FLUTTER_FML_SRC_DIR}/platform/win/errors_win.h
        #${FLUTTER_FML_SRC_DIR}/platform/win/file_win.cc
        ${FLUTTER_FML_SRC_DIR}/platform/win/mapping_win.cc
        ${FLUTTER_FML_SRC_DIR}/platform/win/message_loop_win.cc
        ${FLUTTER_FML_SRC_DIR}/platform/win/message_loop_win.h
        #${FLUTTER_FML_SRC_DIR}/platform/win/native_library_win.cc
        ${FLUTTER_FML_SRC_DIR}/platform/win/paths_win.cc
        ${FLUTTER_FML_SRC_DIR}/platform/win/posix_wrappers_win.cc
        ${FLUTTER_FML_SRC_DIR}/platform/win/wstring_conversion.h
        )
endif()

ADD_LIBRARY(${TARGET_NAME} STATIC ${FLUTTER_FML_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party)

TARGET_COMPILE_DEFINITIONS(${TARGET_NAME} PUBLIC NOMINMAX)
