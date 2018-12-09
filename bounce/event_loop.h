/*
* Copyright (C) 2018 poppinzhang.
*
* Written by poppinzhang with C++11 <poppinzhang@tencent.com>
*
* This file is head file of the EventLoop.
* You must include this file if you want to use EventLoop.
* It's a public class, users can use this class.
*
* Use of this source code is governed by the GNU Lesser General Public.
*/

#ifndef BOUNCE_EVENTLOOP_H
#define BOUNCE_EVENTLOOP_H

#include <chrono>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include <bounce/poller.h>

namespace bounce {

class Channel;

class EventLoop {
	typedef std::function<void()> Functor;
public:
	EventLoop();
	~EventLoop() {}
	EventLoop(const EventLoop&) = delete;
	EventLoop& operator=(const EventLoop&) = delete;

	void loop();
	void updateChannel(Channel* channel);
	//void removeChannel(Channel* channel);

	// TODO: add move version (&&)
	void doTaskInThread(Functor& func);
	void queueTaskInThread(Functor& func);

	void doTaskInThread(Functor&& func);
	void queueTaskInThread(Functor&& func);

private:
	void doTheTasks();

	bool looping_;
	bool stop_;
	std::thread::id thread_id_;
	std::unique_ptr<Poller> poller_;

	typedef std::list<Channel*> ChannelList;
	ChannelList active_channels_;
	Channel* cur_channel_;

	std::mutex mutex_;
	std::vector<Functor> task_vec_;
};

} // namespace bounce

#endif // BOUNCE_EVENTLOOP_H