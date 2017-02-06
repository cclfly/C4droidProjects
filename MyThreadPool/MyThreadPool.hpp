// MyThreadPool

#ifndef MYTHREADPOOL_HPP
#define MYTHREADPOOL_HPP

#include <iostream>
#include <array>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>

enum ThreadStatue{threadRunning,threadSleeping};

template<std::size_t num=1>
class MyThreadPool
{
private:
	std::array<std::tuple<std::thread,ThreadStatue>,num> pool;
	std::queue<std::function<void()>> tasks;
	std::thread thMain;
	std::mutex mut;
public:
    MyThreadPool():thMain([this](){
    	while(true)
    	{
    		mut.lock();
    		if(tasks.size()==0)
    		{
    			mut.unlock();
    			continue;
    		}
    		auto func=std::move(tasks.front());
    		for(auto &tup:pool)
    		{
    		    if(std::get<1>(tup)==threadSleeping)
    		    {
    		    	auto& stat=std::get<1>(tup);
    		    	std::get<0>(tup).detach();
    		    	std::get<0>(tup)=std::move(std::thread([&stat,&func](){
    		    		func();
    		    		stat=threadSleeping;
    		    	}));
    		    	std::get<1>(tup)=threadRunning;
    		    	tasks.pop();
    		    	continue;
    		    }
    		}
    		mut.unlock();
    	}
    })
    {
    	for(auto &tup:pool)
    	{
    		std::get<0>(tup)=std::move(std::thread(std::bind([](){})));
    		std::get<1>(tup)=threadSleeping;
    	}
    }
    ~MyThreadPool()
    {
    	for (auto &tup:pool)
    	{
    		std::get<0>(tup).detach();
    	}
    	thMain.detach();
    }
    
    template<typename F,typename ...Args>
    void add(F f,Args ...args)
    {
    	mut.lock();
    	tasks.push(std::move(std::bind(f,args...)));
    	mut.unlock();
    }
};


#endif //MYTHREADPOOL_HPP