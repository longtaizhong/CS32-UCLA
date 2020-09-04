//
//  ChatTracker.cpp
//  sloChatTracker
//
//  Created by Ryan Zhong  on 6/1/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

// ChatTracker.cpp

// This is a correct but inefficient implementation of
// the ChatTracker functionality.

#include "ChatTracker.h"
#include <string>
#include <vector>
#include <functional>
#include <list>
#include <iostream>
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
    // integer that holds maxmimum People
    int max;
    
    //Hash table, vector of vector that holds Info
    vector<vector<Info>> m_info;
    vector<Info> m_usersWhoLeft;
};

ChatTrackerImpl::ChatTrackerImpl(int maxBuckets)
{
    max = maxBuckets;
    m_info.resize(max);
}

void ChatTrackerImpl::join(string user, string chat)
{
    //Calculating BucketNum
    hash<string> str_hash;
    unsigned int hashValue = str_hash(user);
    unsigned int bucket = hashValue % max;
    
    //Iterators
    vector<vector<Info>>::iterator nameI;
    vector<Info>:: iterator chatI;
    
    //The bucket is empty, meaning there is no user there
    if(m_info[bucket].empty()){
        m_info[bucket].push_back(Info(user, chat));
       // cerr<< "added" << endl;
     //   cerr<< m_info[bucket].begin()->user << endl;
        return;
    }
    //Bucket is not empty
    for(chatI = m_info[bucket].begin(); chatI < m_info[bucket].end(); chatI++){
        if(chatI->user == user && chatI->chat == chat){
            Info info = *chatI;
            m_info[bucket].erase(chatI);
            m_info[bucket].push_back(info);
            return;
        }
    }
    m_info[bucket].push_back(Info(user, chat));
    
  
  
}

int ChatTrackerImpl::terminate(string chat)
{
    //Goes through the hash table and if its not empty, delete the person that contains certain chat
    vector<vector<Info>>::iterator p;
    vector<Info>::iterator charI;
    int total = 0;
    for(p = m_info.begin(); p < m_info.end(); p++){
        if(!p->empty()){
            /*
            for(charI = p->begin(); charI < p->end(); charI++){
                if(charI->chat == chat){
                    total += charI->count;
                    charI = p->erase(charI);
                }
            }*/
            charI = p->begin();
            while(charI != p->end()){
                if(charI -> chat == chat){
                    total += charI->count;
                    charI = p->erase(charI);
                }else{
                    charI++;
                }
            }
        }
    }
    
    vector<Info>::iterator k = m_usersWhoLeft.begin();
    while (k != m_usersWhoLeft.end())
    {
        if (k->chat == chat)
        {
            total += k->count;
            k = m_usersWhoLeft.erase(k);
        }
        else
            k++;
    }
    return total;
    
    
    
    
    /*
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
     return total;*/
}

int ChatTrackerImpl::contribute(string user)
{
    //If theres user, increment the count
    hash<string> str_hash;
    unsigned int hashValue = str_hash(user);
    unsigned int bucket = hashValue % max;
    
    
    //Iterators
    vector<vector<Info>>::iterator nameI;
    vector<Info>:: iterator chatI;
    if(!m_info[bucket].empty()){
        
        for(chatI = m_info[bucket].end()-1; chatI >= m_info[bucket].begin(); chatI--){
            
            if(chatI->user == user){
           //     cerr<< "ADD COUNT" << endl;
                chatI->count++;
                return chatI->count;
            }
        }
    }
    return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
{
    /*
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
    }*/
    //If theres user, remove it and add it to the vector of userWhoLeft
    hash<string> str_hash;
    unsigned int hashValue = str_hash(user);
    unsigned int bucket = hashValue % max;
    
    
    //Iterators
    vector<vector<Info>>::iterator nameI;
    vector<Info>:: iterator chatI = m_info[bucket].end();
    while(chatI > m_info[bucket].begin()){
        chatI--;
        if(chatI->user == user && chatI->chat == chat){
            int count = chatI->count;
            m_usersWhoLeft.push_back(*chatI);
            m_info[bucket].erase(chatI);
            return count;
        }
    }
    return -1;
}

int ChatTrackerImpl::leave(string user)
{
    /*
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
    }*/
    hash<string> str_hash;
    unsigned int hashValue = str_hash(user);
    unsigned int bucket = hashValue % max;
    
    
    //Iterators
    vector<vector<Info>>::iterator nameI;
    vector<Info>:: iterator chatI = m_info[bucket].end();
    while(chatI > m_info[bucket].begin()){
        chatI--;
        if(chatI->user == user){
            int count = chatI->count;
            m_usersWhoLeft.push_back(*chatI);
            m_info[bucket].erase(chatI);
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

