/*

Copyright (c) 2003, Arvid Norberg, Daniel Wallin
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include "libtorrent/pch.hpp"

#include "libtorrent/alert.hpp"
#include <boost/thread/xtime.hpp>

namespace libtorrent {

	alert::alert(severity_t severity, const std::string& msg)
		: m_msg(msg)
		, m_severity(severity)
		, m_timestamp(time_now())
	{
	}

	alert::~alert()
	{
	}

	ptime alert::timestamp() const
	{
		return m_timestamp;
	}

	const std::string& alert::msg() const
	{
		return m_msg;
	}

	alert::severity_t alert::severity() const
	{
		return m_severity;
	}



	alert_manager::alert_manager()
		: m_severity(alert::fatal)
	{}

	alert_manager::~alert_manager()
	{
		while (!m_alerts.empty())
		{
			delete m_alerts.front();
			m_alerts.pop();
		}
	}

	alert const* alert_manager::wait_for_alert(time_duration max_wait)
	{
		boost::mutex::scoped_lock lock(m_mutex);

		if (!m_alerts.empty()) return m_alerts.front();
		
		int secs = total_seconds(max_wait);
		max_wait -= seconds(secs);
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);
		xt.sec += secs;
		boost::int64_t nsec = xt.nsec + total_microseconds(max_wait) * 1000;
		if (nsec > 1000000000)
		{
			nsec -= 1000000000;
			xt.sec += 1;
		}
		xt.nsec = boost::xtime::xtime_nsec_t(nsec);
		if (!m_condition.timed_wait(lock, xt)) return 0;
		TORRENT_ASSERT(!m_alerts.empty());
		if (m_alerts.empty()) return 0;
		return m_alerts.front();
	}

	void alert_manager::post_alert(const alert& alert_)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		if (m_severity > alert_.severity()) return;

		// the internal limit is 100 alerts
		if (m_alerts.size() == 100)
		{
			alert* result = m_alerts.front();
			m_alerts.pop();
			delete result;
		}
		m_alerts.push(alert_.clone().release());
		m_condition.notify_all();
	}

	std::auto_ptr<alert> alert_manager::get()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		
		TORRENT_ASSERT(!m_alerts.empty());

		alert* result = m_alerts.front();
		m_alerts.pop();
		return std::auto_ptr<alert>(result);
	}

	bool alert_manager::pending() const
	{
		boost::mutex::scoped_lock lock(m_mutex);
		
		return !m_alerts.empty();
	}

	void alert_manager::set_severity(alert::severity_t severity)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		
		m_severity = severity;
	}
	
	bool alert_manager::should_post(alert::severity_t severity) const
	{
		return severity >= m_severity;
	}

} // namespace libtorrent

