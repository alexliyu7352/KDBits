//
// timer_queue.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_TIMER_QUEUE_HPP
#define ASIO_DETAIL_TIMER_QUEUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/push_options.hpp"

#include "asio/detail/push_options.hpp"
#include <cstddef>
#include <functional>
#include <limits>
#include <memory>
#include <vector>
#include <boost/config.hpp>
#include "asio/detail/pop_options.hpp"

#include "asio/error.hpp"
#include "asio/detail/hash_map.hpp"
#include "asio/detail/noncopyable.hpp"
#include "asio/detail/timer_queue_base.hpp"

namespace asio {
namespace detail {

template <typename Time_Traits>
class timer_queue
  : public timer_queue_base
{
public:
  // The time type.
  typedef typename Time_Traits::time_type time_type;

  // The duration type.
  typedef typename Time_Traits::duration_type duration_type;

  // Constructor.
  timer_queue()
    : timers_(),
      heap_(),
      cancelled_timers_(0),
      cleanup_timers_(0)
  {
  }

  // Add a new timer to the queue. Returns true if this is the timer that is
  // earliest in the queue, in which case the reactor's event demultiplexing
  // function call may need to be interrupted and restarted.
  template <typename Handler>
  bool enqueue_timer(const time_type& time, Handler handler, void* token)
  {
    // Ensure that there is space for the timer in the heap. We reserve here so
    // that the push_back below will not throw due to a reallocation failure.
    heap_.reserve(heap_.size() + 1);

    // Create a new timer object.
    std::auto_ptr<timer<Handler> > new_timer(
        new timer<Handler>(time, handler, token));

    // Insert the new timer into the hash.
    typedef typename hash_map<void*, timer_base*>::iterator iterator;
    typedef typename hash_map<void*, timer_base*>::value_type value_type;
    std::pair<iterator, bool> result =
      timers_.insert(value_type(token, new_timer.get()));
    if (!result.second)
    {
      result.first->second->prev_ = new_timer.get();
      new_timer->next_ = result.first->second;
      result.first->second = new_timer.get();
    }

    // Put the timer at the correct position in the heap.
    new_timer->heap_index_ = heap_.size();
    heap_.push_back(new_timer.get());
    up_heap(heap_.size() - 1);
    bool is_first = (heap_[0] == new_timer.get());

    // Ownership of the timer is transferred to the timer queue.
    new_timer.release();

    return is_first;
  }

  // Whether there are no timers in the queue.
  virtual bool empty() const
  {
    return heap_.empty();
  }

  // Get the time for the timer that is earliest in the queue.
  virtual boost::posix_time::time_duration wait_duration() const
  {
    return Time_Traits::to_posix_duration(
        Time_Traits::subtract(heap_[0]->time_, Time_Traits::now()));
  }

  // Dispatch the timers that are earlier than the specified time.
  virtual void dispatch_timers()
  {
    const time_type now = Time_Traits::now();
    while (!heap_.empty() && !Time_Traits::less_than(now, heap_[0]->time_))
    {
      timer_base* t = heap_[0];
      remove_timer(t);
      t->prev_ = 0;
      t->next_ = cleanup_timers_;
      cleanup_timers_ = t;
      t->invoke(asio::error_code());
    }
  }

  // Cancel the timers with the given token. Any timers pending for the token
  // will be notified that they have been cancelled next time
  // dispatch_cancellations is called. Returns the number of timers that were
  // cancelled.
  std::size_t cancel_timer(void* timer_token)
  {
    std::size_t num_cancelled = 0;
    typedef typename hash_map<void*, timer_base*>::iterator iterator;
    iterator it = timers_.find(timer_token);
    if (it != timers_.end())
    {
      timer_base* t = it->second;
      while (t)
      {
        timer_base* next = t->next_;
        remove_timer(t);
        t->prev_ = 0;
        t->next_ = cancelled_timers_;
        cancelled_timers_ = t;
        t = next;
        ++num_cancelled;
      }
    }
    return num_cancelled;
  }

  // Dispatch any pending cancels for timers.
  virtual void dispatch_cancellations()
  {
    while (cancelled_timers_)
    {
      timer_base* this_timer = cancelled_timers_;
      cancelled_timers_ = this_timer->next_;
      this_timer->next_ = cleanup_timers_;
      cleanup_timers_ = this_timer;
      this_timer->invoke(asio::error::operation_aborted);
    }
  }

  // Destroy timers that are waiting to be cleaned up.
  virtual void cleanup_timers()
  {
    destroy_timer_list(cleanup_timers_);
  }

  // Destroy all timers.
  virtual void destroy_timers()
  {
    typename hash_map<void*, timer_base*>::iterator i = timers_.begin();
    typename hash_map<void*, timer_base*>::iterator end = timers_.end();
    while (i != end)
    {
      timer_base* t = i->second;
      typename hash_map<void*, timer_base*>::iterator old_i = i++;
      timers_.erase(old_i);
      destroy_timer_list(t);
    }
    heap_.clear();
    timers_.clear();
    destroy_timer_list(cancelled_timers_);
    destroy_timer_list(cleanup_timers_);
  }

private:
  // Base class for timer operations. Function pointers are used instead of
  // virtual functions to avoid the associated overhead.
  class timer_base
  {
  public:
    // Perform the timer operation and then destroy.
    void invoke(const asio::error_code& result)
    {
      invoke_func_(this, result);
    }

    // Destroy the timer operation.
    void destroy()
    {
      destroy_func_(this);
    }

  protected:
    typedef void (*invoke_func_type)(timer_base*,
        const asio::error_code&);
    typedef void (*destroy_func_type)(timer_base*);

    // Constructor.
    timer_base(invoke_func_type invoke_func, destroy_func_type destroy_func,
        const time_type& time, void* token)
      : invoke_func_(invoke_func),
        destroy_func_(destroy_func),
        time_(time),
        token_(token),
        next_(0),
        prev_(0),
        heap_index_(
            std::numeric_limits<size_t>::max BOOST_PREVENT_MACRO_SUBSTITUTION())
    {
    }

    // Prevent deletion through this type.
    ~timer_base()
    {
    }

  private:
    friend class timer_queue<Time_Traits>;

    // The function to be called to dispatch the handler.
    invoke_func_type invoke_func_;

    // The function to be called to destroy the handler.
    destroy_func_type destroy_func_;

    // The time when the operation should fire.
    time_type time_;

    // The token associated with the timer.
    void* token_;

    // The next timer known to the queue.
    timer_base* next_;

    // The previous timer known to the queue.
    timer_base* prev_;

    // The index of the timer in the heap.
    size_t heap_index_;
  };

  // Adaptor class template for using handlers in timers.
  template <typename Handler>
  class timer
    : public timer_base
  {
  public:
    // Constructor.
    timer(const time_type& time, Handler handler, void* token)
      : timer_base(&timer<Handler>::invoke_handler,
          &timer<Handler>::destroy_handler, time, token),
        handler_(handler)
    {
    }

    // Invoke the handler and then destroy it.
    static void invoke_handler(timer_base* base,
        const asio::error_code& result)
    {
      static_cast<timer<Handler>*>(base)->handler_(result);
    }

    // Destroy the handler.
    static void destroy_handler(timer_base* base)
    {
      delete static_cast<timer<Handler>*>(base);
    }

  private:
    Handler handler_;
  };

  // Move the item at the given index up the heap to its correct position.
  void up_heap(size_t index)
  {
    size_t parent = (index - 1) / 2;
    while (index > 0
        && Time_Traits::less_than(heap_[index]->time_, heap_[parent]->time_))
    {
      swap_heap(index, parent);
      index = parent;
      parent = (index - 1) / 2;
    }
  }

  // Move the item at the given index down the heap to its correct position.
  void down_heap(size_t index)
  {
    size_t child = index * 2 + 1;
    while (child < heap_.size())
    {
      size_t min_child = (child + 1 == heap_.size()
          || Time_Traits::less_than(
            heap_[child]->time_, heap_[child + 1]->time_))
        ? child : child + 1;
      if (Time_Traits::less_than(heap_[index]->time_, heap_[min_child]->time_))
        break;
      swap_heap(index, min_child);
      index = min_child;
      child = index * 2 + 1;
    }
  }

  // Swap two entries in the heap.
  void swap_heap(size_t index1, size_t index2)
  {
    timer_base* tmp = heap_[index1];
    heap_[index1] = heap_[index2];
    heap_[index2] = tmp;
    heap_[index1]->heap_index_ = index1;
    heap_[index2]->heap_index_ = index2;
  }

  // Remove a timer from the heap and list of timers.
  void remove_timer(timer_base* t)
  {
    // Remove the timer from the heap.
    size_t index = t->heap_index_;
    if (!heap_.empty() && index < heap_.size())
    {
      if (index == heap_.size() - 1)
      {
        heap_.pop_back();
      }
      else
      {
        swap_heap(index, heap_.size() - 1);
        heap_.pop_back();
        size_t parent = (index - 1) / 2;
        if (index > 0 && Time_Traits::less_than(
              heap_[index]->time_, heap_[parent]->time_))
          up_heap(index);
        else
          down_heap(index);
      }
    }

    // Remove the timer from the hash.
    typedef typename hash_map<void*, timer_base*>::iterator iterator;
    iterator it = timers_.find(t->token_);
    if (it != timers_.end())
    {
      if (it->second == t)
        it->second = t->next_;
      if (t->prev_)
        t->prev_->next_ = t->next_;
      if (t->next_)
        t->next_->prev_ = t->prev_;
      if (it->second == 0)
        timers_.erase(it);
    }
  }

  // Destroy all timers in a linked list.
  void destroy_timer_list(timer_base*& t)
  {
    while (t)
    {
      timer_base* next = t->next_;
      t->next_ = 0;
      t->destroy();
      t = next;
    }
  }

  // A hash of timer token to linked lists of timers.
  hash_map<void*, timer_base*> timers_;

  // The heap of timers, with the earliest timer at the front.
  std::vector<timer_base*> heap_;

  // The list of timers to be cancelled.
  timer_base* cancelled_timers_;

  // The list of timers to be destroyed.
  timer_base* cleanup_timers_;
};

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_TIMER_QUEUE_HPP
