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

    std::mutex threads_mutex;
    std::list<std::thread> threads;

    double size;
    bool running, listening;

    std::map<std::string, Colony_ptr> colonies;

    SafeQueue<Event> events;

    std::list<Galaxy_ptr> galaxies;

    double time; // "indiction" -> 15 earth years
    void set_time(double new_time);
    void listen(int port);
    void process_client_requests(int client_fd);
    void process_client_requests_in_bg(int client_fd);

  public:

    Universe();
    ~Universe();

    double get_time() const;

    static Universe_ptr get_universe();

    Colony_ptr add_colony(std::string name);
    Galaxy_ptr get_galaxy(Vec3 point);

    void listen_in_bg(int port);
    void run_events();
    void stop();

    void add_event(Event_ptr event);

};
