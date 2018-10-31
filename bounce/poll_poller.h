/*
* Copyright (C) 2018 poppinzhang.
*
* Written by poppinzhang with C++11 <poppinzhang@tencent.com>
*
* This file is head file of the PollPoller.
* This is an internal header file, users should not include this.
*
* Use of this source code is governed by the GNU Lesser General Public.
*/

#ifndef BOUNCE_POLLPOLLER_H
#define BOUNCE_POLLPOLLER_H

#include <poll.h>

#include <list>
#include <vector>

#include <bounce/poller.h>

namespace bounce {

class Channel;
class EventLoop;

class PollPoller : public Poller {
public:
	PollPoller(EventLoop* loop) : Poller(loop) {}
	//~PollPoller();

	std::time_t poll(int timeout, ChannelList* active_channels);
	void updateChannel(Channel* channel);
	void removeChannel(Channel* channel);

private:
	std::vector<struct pollfd> pollfds_;
};

} // namespace bounce

#endif // !BOUNCE_POLLPOLLER_H