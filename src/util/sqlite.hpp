#pragma once
#include <string>
#include <map>
#include <vector>

namespace __sqlite3 {
  #include <sqlite3.h>
};

#include "exception.hpp"


EXCEPTION(SQLiteError, "SQLiteError");


class SQLiteRow {

  private:

    std::map<std::string, std::string> map;

  public:

    SQLiteRow(char **values, char **fields, int n);
    ~SQLiteRow();
    std::string get(std::string);
    std::string operator[](std::string k) { return this->get(k); }

};


class SQLiteResults {

  private:

    std::vector<SQLiteRow> rows;

  public:

    SQLiteResults();
    ~SQLiteResults();

    static int factory(void *addr, int ncol, char** values, char **fields);

    SQLiteRow get(unsigned int i);
    SQLiteRow operator[](int i) { return this->get(i); }
    unsigned int size() const;
};


class SQLiteInterface {

  private:

    __sqlite3::sqlite3 *db;

  public:

    SQLiteInterface(std::string path);
    ~SQLiteInterface();

    SQLiteResults execute(std::string command);
};
