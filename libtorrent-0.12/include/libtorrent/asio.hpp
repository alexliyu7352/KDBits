//
// asio.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_HPP
#define ASIO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/basic_datagram_socket.hpp"
#include "asio/basic_deadline_timer.hpp"
#include "asio/basic_io_object.hpp"
#include "asio/basic_socket_acceptor.hpp"
#include "asio/basic_socket_iostream.hpp"
#include "asio/basic_socket_streambuf.hpp"
#include "asio/basic_stream_socket.hpp"
#include "asio/basic_streambuf.hpp"
#include "asio/buffer.hpp"
#include "asio/buffered_read_stream_fwd.hpp"
#include "asio/buffered_read_stream.hpp"
#include "asio/buffered_stream_fwd.hpp"
#include "asio/buffered_stream.hpp"
#include "asio/buffered_write_stream_fwd.hpp"
#include "asio/buffered_write_stream.hpp"
#include "asio/completion_condition.hpp"
#include "asio/datagram_socket_service.hpp"
#include "asio/deadline_timer_service.hpp"
#include "asio/deadline_timer.hpp"
#include "asio/error.hpp"
#include "asio/error_code.hpp"
#include "asio/handler_alloc_hook.hpp"
#include "asio/handler_invoke_hook.hpp"
#include "asio/io_service.hpp"
#include "asio/ip/address.hpp"
#include "asio/ip/address_v4.hpp"
#include "asio/ip/address_v6.hpp"
#include "asio/ip/basic_endpoint.hpp"
#include "asio/ip/basic_resolver.hpp"
#include "asio/ip/basic_resolver_entry.hpp"
#include "asio/ip/basic_resolver_iterator.hpp"
#include "asio/ip/basic_resolver_query.hpp"
#include "asio/ip/host_name.hpp"
#include "asio/ip/multicast.hpp"
#include "asio/ip/resolver_query_base.hpp"
#include "asio/ip/resolver_service.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/ip/udp.hpp"
#include "asio/ip/unicast.hpp"
#include "asio/ip/v6_only.hpp"
#include "asio/is_read_buffered.hpp"
#include "asio/is_write_buffered.hpp"
#include "asio/placeholders.hpp"
#include "asio/read.hpp"
#include "asio/read_until.hpp"
#include "asio/socket_acceptor_service.hpp"
#include "asio/socket_base.hpp"
#include "asio/strand.hpp"
#include "asio/stream_socket_service.hpp"
#include "asio/streambuf.hpp"
#include "asio/system_error.hpp"
#include "asio/thread.hpp"
#include "asio/time_traits.hpp"
#include "asio/write.hpp"

#endif // ASIO_HPP
