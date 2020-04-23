#pragma once
#include <string>
#include <map>
#include <vector>

namespace __sqlite3 {
  #include <sqlite3.h>
};

#include "exception.hpp"


EXCEPTION(SQLiteError, "SQLiteError");
EXCEPTION(SQLiteNullError, "SQLiteNullError");

class SQLiteValue {

  private:
    std::string value;
    bool null;

  public:

    SQLiteValue() : SQLiteValue(nullptr){}
    SQLiteValue(const char *value);
    ~SQLiteValue();

    std::string as_string();
    int as_int();
    double as_double();
    bool is_null();

    operator std::string()
    {
      return this->as_string();
    }

    operator double()
    {
      return this->as_double();
    }

    operator bool()
    {
      return this->is_null();
    }

};

class SQLiteRow {

  private:

    std::map<std::string, SQLiteValue> map;

  public:

    SQLiteRow(char **values, char **fields, int n);
    ~SQLiteRow();
    SQLiteValue get(const std::string&);
    SQLiteValue operator[](const std::string &k) { return this->get(k); }

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
