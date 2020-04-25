#include "sqlite.hpp"


SQLiteValue::SQLiteValue(const char *value)
{
  if (value != nullptr) {
    this->value = std::string(value);
    this->null = false;
  }
  else {
    this->null = true;
    this->value = "";
  }
}

SQLiteValue::~SQLiteValue()
{
}

std::string SQLiteValue::as_string() const
{
  return std::string(this->value);
}

int SQLiteValue::as_int() const
{
  return std::stoi(this->value);
}

double SQLiteValue::as_double() const
{
  return std::stod(this->value);
}

bool SQLiteValue::is_null() const
{
  return this->null;
}






SQLiteResults::SQLiteResults()
{
  // do nothing
}

SQLiteResults::~SQLiteResults()
{
  // do nothing
}

const SQLiteRow &SQLiteResults::get(unsigned int i) const
{
  if (i > this->rows.size() - 1)
    throw IndexError(Formatter() << "Index " << i << " invalid for vector of size " << this->rows.size() << ".");
  return this->rows[i];
}

int SQLiteResults::factory(void *addr, int ncol, char** values, char **fields)
{
  SQLiteResults *res = (SQLiteResults *)addr;
  res->rows.push_back(SQLiteRow(values, fields, ncol));
  return 0;
}


unsigned int SQLiteResults::size() const
{
  return this->rows.size();
}












SQLiteRow::SQLiteRow(char **values, char **fields, int n)
{
  for (int i = 0; i < n; i++) {
    std::string key(fields[i]);
    this->map[key] = SQLiteValue(values[i]);
  }
}

SQLiteRow::~SQLiteRow()
{
  // do nothing
}


const SQLiteValue &SQLiteRow::get(const std::string &k) const
{
  auto it = this->map.find(k);
  if (it == this->map.end())
    throw SQLiteError(Formatter() << "No column with name \"" << k << "\" in SQLite results row.");

  return (*it).second;
}











SQLiteInterface::SQLiteInterface(std::string path)
{
  if (__sqlite3::sqlite3_open(path.c_str(), &this->db))
    throw SQLiteError(Formatter() << "Error opening database \"" << path << "\": " << __sqlite3::sqlite3_errmsg(this->db) << ".");
}



SQLiteInterface::~SQLiteInterface()
{
  __sqlite3::sqlite3_close(this->db);
}



SQLiteResults SQLiteInterface::execute(std::string command)
{
  const char *c = command.c_str();
  char *e = nullptr;
  SQLiteResults res;
  int rc = __sqlite3::sqlite3_exec(this->db, c, SQLiteResults::factory, &res, &e);

  if (rc != SQLITE_OK) {
    std::string s = Formatter() << "Error executing \"" << command << "\": " << e << ".";
    __sqlite3::sqlite3_free(e);
    throw SQLiteError(s);
  }

  return res;
}
