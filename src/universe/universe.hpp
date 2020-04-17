#pragma once
#include <memory>
#include <map>
#include <list>
#include <string>
#include <thread>
#include <mutex>

#include "../util/safeq.hpp"
#include "../util/vec.hpp"
#include "../event/event.hpp"
#include "../types.hpp"



class Universe {

  private:

    int server_fd;
    std::map<std::string, SafeQueue<Message>> colony_messages;

    double size;
    bool running;

    std::map<std::string, Colony_ptr> colonies;

    std::mutex events_mutex;
    std::list<Event_ptr> events;

    std::list<Galaxy_ptr> galaxies;

    double time; // "indiction" -> 15 earth years
    void set_time(double new_time);

  public:

    Universe();
    ~Universe();

    double get_time() const;

    static Universe_ptr get_universe();

    bool has_colony(std::string name);
    Colony_ptr add_colony(std::string name);
    Galaxy_ptr get_galaxy(Vec3 point);

    void run_events();
    void stop();

    void add_event(Event_ptr event);

};
