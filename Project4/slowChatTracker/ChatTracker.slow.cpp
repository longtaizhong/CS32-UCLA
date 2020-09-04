// ChatTracker.cpp

// This is a correct but inefficient implementation of
// the ChatTracker functionality.

#include "ChatTracker.h"
#include <string>
#include <vector>
using namespace std;

  // This class does the real work of the implementation.

class ChatTrackerImpl
{
  public:
    ChatTrackerImpl(int maxBuckets);
    void join(string user, string chat);
    int terminate(string chat);
    int contribute(string user);
    int leave(string user, string chat);
    int leave(string user);

  private:
    struct Info
    {
        Info(string u, string c) : user(u), chat(c), count(0) {}
        string user;
        string chat;
        int count;
    };

    vector<Info> m_info;
    vector<Info> m_usersWhoLeft;
};

ChatTrackerImpl::ChatTrackerImpl(int /* maxBuckets */)
{
    // Since this implementation does not use a hash table, we don't do
    // anything with the parameter and leave it unnamed so the compiler
    // doesn't issue a warning about an unused parameter.
}

void ChatTrackerImpl::join(string user, string chat)
{
    vector<Info>::iterator p = m_info.end();
    while (p > m_info.begin())
    {
        p--;
        if (p->user == user  &&  p->chat == chat)
        {
            Info info = *p;
            m_info.erase(p);
            m_info.push_back(info);
            return;
        }
    }
    m_info.push_back(Info(user, chat));
}

int ChatTrackerImpl::terminate(string chat)
{
    int total = 0;
    vector<Info>::iterator p = m_info.begin();
    while (p != m_info.end())
    {
        if (p->chat == chat)
	{
            total += p->count;
            p = m_info.erase(p);
	}
	else
	    p++;
    }
    p = m_usersWhoLeft.begin();
    while (p != m_usersWhoLeft.end())
    {
        if (p->chat == chat)
	{
            total += p->count;
            p = m_usersWhoLeft.erase(p);
	}
	else
	    p++;
    }
    return total;
}

int ChatTrackerImpl::contribute(string user)
{
    vector<Info>::iterator p = m_info.end();
    while (p > m_info.begin())
    {
        p--;
        if (p->user == user)
        {
            p->count++;
            return p->count;
        }
    }
    return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
{
    vector<Info>::iterator p = m_info.end();
    while (p > m_info.begin())
    {
        p--;
        if (p->user == user  &&  p->chat == chat)
        {
            int count = p->count;
            m_usersWhoLeft.push_back(*p);
            m_info.erase(p);
            return count;
        }
    }
    return -1;
}

int ChatTrackerImpl::leave(string user)
{
    vector<Info>::iterator p = m_info.end();
    while (p > m_info.begin())
    {
        p--;
        if (p->user == user)
        {
            int count = p->count;
            m_usersWhoLeft.push_back(*p);
            m_info.erase(p);
            return count;
        }
    }
    return -1;
}

//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
    m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
    delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
    m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
    return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
    return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
    return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
    return m_impl->leave(user);
}
