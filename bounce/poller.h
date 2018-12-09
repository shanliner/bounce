/*
* Copyright (C) 2018 poppinzhang.
*
* Written by poppinzhang with C++11 <poppinzhang@tencent.com>
*
* This file is head file of the Poller.
* Poller is an abstract class.
* This is an internal header file, users should not include this.
*
* Use of this source code is governed by the GNU Lesser General Public.
*/

#ifndef BOUNCE_POLLER_H
#define BOUNCE_POLLER_H

#include <chrono>
#include <list>
#include <map>

namespace bounce {

class Channel;
class EventLoop;

class Poller {
public:
	typedef std::list<Channel*> ChannelList;
	Poller(EventLoop* loop) : loop_(loop) {}
	virtual ~Poller() {}
	Poller(const Poller&) = delete;
	Poller& operator=(const Poller&) = delete;

	virtual std::time_t poll(int timeout, ChannelList* active_channels) = 0;
	virtual void updateChannel(Channel* channel) = 0;
	virtual void removeChannel(Channel* channel) = 0;

protected:
	typedef std::map<int, Channel*> ChannelMap;
	ChannelMap channels_;

private:
	EventLoop* loop_;
};

} // namespace bounce

#endif // !BOUNCE_POLLER_H