#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER pocl_trace

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./pocl_lttng.h"

#if !defined(POCL_LLTTNG_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define POCL_LLTTNG_H

#include <lttng/tracepoint.h>

/**
 *  NDRange kernel tracepoint
 */
TRACEPOINT_EVENT(
    pocl_trace,
    ndrange_kernel,
    TP_ARGS(
        int, event_status,
        char*, kernel_name
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_string(kernel_name, kernel_name)
    )
)

/**
 *  R/W Buffer tracepoint
 */
TRACEPOINT_EVENT(
    pocl_trace,
    read_buffer,
    TP_ARGS(
        int, event_status,
        const void *, host_ptr,
        size_t, buffer_size
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_integer_hex(const void *, host_ptr, host_ptr)
        ctf_integer_hex(size_t, buffer_size, buffer_size)
    )
)

TRACEPOINT_EVENT(
    pocl_trace,
    write_buffer,
    TP_ARGS(
        int, event_status,
        const void *, host_ptr,
        size_t, buffer_size
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_integer_hex(const void *, host_ptr, host_ptr)
        ctf_integer_hex(size_t, buffer_size, buffer_size)
    )
)

/**
 *  Copy Buffer tracepoint
 */
TRACEPOINT_EVENT(
    pocl_trace,
    copy_buffer,
    TP_ARGS(
        int, event_status,
        size_t, buffer_size
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_integer_hex(size_t, buffer_size, buffer_size)
    )
)

/**
 *  Fill Buffer tracepoint
 */
TRACEPOINT_EVENT(
    pocl_trace,
    fill_buffer,
    TP_ARGS(
        int, event_status,
        size_t, fill_size
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_integer_hex(size_t, fill_size, fill_size)
    )
)/**
 *  Map tracepoint
 */
TRACEPOINT_EVENT(
    pocl_trace,
    map,
    TP_ARGS(
        int, event_status,
        size_t, fill_size
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_integer_hex(size_t, fill_size, fill_size)
    )
)

/**
 *  Generic tracepoint for other commands
 */
TRACEPOINT_EVENT(
    pocl_trace,
    command,
    TP_ARGS(
        int, event_status,
        const char *, cmd_type
    ),
    TP_FIELDS(
        ctf_integer(int, event_status, event_status)
        ctf_string(cmd_type, cmd_type)
    )
)

/**
 *  Default tracepoint
 */

#endif /* POCL_LLTTNG_H */

#include <lttng/tracepoint-event.h>
