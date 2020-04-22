#include "sqlite.hpp"


SQLiteResults::SQLiteResults()
{
  // do nothing
}

SQLiteResults::~SQLiteResults()
{
  // do nothing
}

SQLiteRow SQLiteResults::get(unsigned int i)
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
    std::string key(fields[i]), value(values[i]);
    this->map[key] = value;
  }
}

SQLiteRow::~SQLiteRow()
{
  // do nothing
}

std::string SQLiteRow::get(std::string k)
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
