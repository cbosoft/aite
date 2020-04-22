#include <iostream>
#include <fstream>

#include "../../util/sqlite.hpp"

void add_feature();
void edit_feature_by_id(int id);
void edit_feature_by_name(std::string name);

enum Action { AddFeature, EditFeatureByID, EditFeatureByName };

int main(int argc, const char **argv)
{

  argc --; argv++;
  Action action = AddFeature;

  if (strcmp(argv[0], "add") == 0) {
    action = AddFeature;
  }
  else if (strcmp(argv[0], "edit") == 0) {
    if (strcmp(argv[1], "byid") == 0) {
      action = EditFeatureByID;
    }
    else if (strcmp(argv[1], "byname") == 0) {
      action = EditFeatureByName;
    }
    else
      throw ArgumentError("syntax error");
  }
  else {
    throw ArgumentError("syntax error");
  }

  switch (action) {

    case AddFeature:
      add_feature();
      break;

    case EditFeatureByID:
      edit_feature_by_id(atoi(argv[2]));
      break;

    case EditFeatureByName:
      edit_feature_by_name(argv[2]);
      break;

  }

}

void set_temp(
    std::string name="1. Name",
    std::string rarity="2. Rarity (impossible, very rare, rare, uncommon, common, ubiquitous, certain)",
    std::string occurrence="3. Occurrence (as above)",
    std::string body="4-end Body of description on subsequent lines.")
{
    std::ofstream ofs("/tmp/AITE_FEATURE.txt");
    ofs 
      << name << "\n"
      << rarity << "\n"
      << occurrence << "\n"
      << body << std::endl;
}

void get_temp(std::string &name, std::string &rarity, std::string &occurrence, std::string &body)
{
  std::ifstream ifs("/tmp/AITE_FEATURE.txt");
  std::getline(ifs, name);
  std::getline(ifs, rarity);
  std::getline(ifs, occurrence);

  std::stringstream ss;
  std::string line;
  while (std::getline(ifs, line))
    if (line.size())
      ss << line;
  body = ss.str();
}



void add_feature()
{

  set_temp();

  int rc = system("$EDITOR /tmp/AITE_FEATURE.txt");
  if (rc) return;

  std::string name, rarity, occurrence, body;
  get_temp(name, rarity, occurrence, body);

  std::string command = Formatter() << "INSERT INTO Features (Name,DescriptionPrototype,Rarity,Occurrence) VALUES (\""
    << name << "\",\"" << body << "\",\"" << rarity << "\",\"" << occurrence << "\");";

  SQLiteInterface db("resources.db");
  db.execute(command);
}


void edit_feature_by_id(int id)
{
  SQLiteInterface db("resources.db");
  auto result = db.execute(Formatter() << "SELECT * FROM Features WHERE ID=" << id << ";");

  unsigned int s = result.size();
  if (s == 0) {
    throw SQLiteError(Formatter() << "No results returned for ID=" << id << ".");
  }
  else if (s > 1) {
    throw SQLiteError(Formatter() << "Too many results (?) returned for ID=" << id << ".");
  }


  auto row = result[0];
  set_temp(row["Name"], row["Rarity"], row["Occurrence"], row["DescriptionPrototype"]);

  int rc = system("$EDITOR /tmp/AITE_FEATURE.txt");
  if (rc) return;

  std::string name, rarity, occurrence, body;
  get_temp(name, rarity, occurrence, body);

  std::string command = Formatter() << "UPDATE Features SET "
    << "Name=\"" << name << "\","
    << "DescriptionPrototype=\"" << body << "\","
    << "Rarity=\"" << rarity << "\","
    << "Occurrence=\"" << occurrence << "\" WHERE ID=\"" << id << "\";";
  db.execute(command);
}


void edit_feature_by_name(std::string qname)
{
  SQLiteInterface db("resources.db");
  auto result = db.execute(Formatter() << "SELECT * FROM Features WHERE Name=" << qname << ";");

  unsigned int s = result.size();
  if (s == 0) {
    throw SQLiteError(Formatter() << "No results returned for Name =" << qname << ".");
  }
  else if (s > 1) {
    throw SQLiteError(Formatter() << "Too many results (" << s << ") returned for Name =" << qname << ".");
  }


  auto row = result[0];
  set_temp(qname, row["Rarity"], row["Occurrence"], row["DescriptionPrototype"]);

  int rc = system("$EDITOR /tmp/AITE_FEATURE.txt");
  if (rc) return;

  std::string name, rarity, occurrence, body;
  get_temp(name, rarity, occurrence, body);

  std::string command = Formatter() << "UPDATE Features SET "
    << "Name=\"" << name << "\","
    << "DescriptionPrototype=\"" << body << "\","
    << "Rarity=\"" << rarity << "\","
    << "Occurrence=\"" << occurrence << "\" WHERE Name=\"" << qname << "\";";
  db.execute(command);
}
