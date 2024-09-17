#ifndef EVENT_SYSTEM_HPP
#define EVENT_SYSTEM_HPP

#include <functional>
#include <vector>
#include <map>
#include <string>
#include <iostream>

using Callback = std::function<void(void)>;

class Event {
    std::vector<Callback> callbacks;

   public:
    void register_callback(Callback callback) {
        callbacks.push_back(callback);
    }

    void fire() {
        for (auto& callback : callbacks) {
            callback();
        }
    }
};

class EventSystem {
   private:
    inline static std::map<std::string, Event*> events;

   public:
    static Event* register_event(std::string event_name) {
        events.insert({event_name, new Event{}});
        return events[event_name];
    }
    static void register_callback(std::string event_name, Callback callback) {
        auto it = events.find(event_name);
        if (it != events.end()) {
            it->second->register_callback(callback);
        }
    }

    static void fire_event(std::string event_name) {
        auto it = events.find(event_name);
        if (it != events.end()) {
            std::cout << "Firing event: " << event_name << std::endl;
            it->second->fire();
        }
    }
};

#endif  // EVENT_SYSTEM_HPP