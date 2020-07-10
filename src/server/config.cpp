#include <fstream>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <iomanip>

#include "server.hpp"


bool GameServer::load_config(const std::string &path)
{
	std::ifstream ifs(path);

	if (ifs.fail()) {
		std::cerr << "warning! could not load config at " << path << std::endl;
		std::cerr << "(" << errno << ") " << strerror(errno) << std::endl;
		return false; // could not load config
	}

	nlohmann::json json;

	try{
		ifs >> json;
	}
	catch (const nlohmann::json::parse_error& p) {
		std::cerr << "warning! could not load config at " << path << std::endl;
		std::cerr << p.what() << std::endl;
	}

	this->config = json;
	return true;
}


void GameServer::load_config()
{
	static std::list<std::string> search_path;

	// currently only look for server config information in 
	search_path.push_back("./aite_server_config.json");
	search_path.push_back("./.aite_server_config.json");

	bool loaded = false;
	for (const auto &path : search_path) {
		loaded = this->load_config(path);
		if (loaded)
			break;
	}

	if (loaded) {
		std::cerr << "Config loaded!\n" << std::setw(2) << this->config << std::endl;
	}

}