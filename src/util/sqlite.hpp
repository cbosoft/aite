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

    std::string as_string() const;
    int as_int() const;
    double as_double() const;
    bool is_null() const;

    operator std::string() const
    {
      return this->as_string();
    }

    operator double() const
    {
      return this->as_double();
    }

    operator bool() const
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
    const SQLiteValue &get(const std::string&) const;
    const SQLiteValue &operator[](const std::string &k) const { return this->get(k); }

};


class SQLiteResults {

  private:

    std::vector<SQLiteRow> rows;

  public:

    SQLiteResults();
    ~SQLiteResults();

    static int factory(void *addr, int ncol, char** values, char **fields);

    const SQLiteRow &get(unsigned int i) const;
    const SQLiteRow &operator[](int i) const { return this->get(i); }
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
