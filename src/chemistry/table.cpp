#include <vector>

#include "../util/sqlite.hpp"
#include "../types.hpp"

#include "element.hpp"

const std::vector<Element_ptr> &get_elements()
{
  static std::vector<Element_ptr> elements;
  static bool loaded = false;

  if (not loaded) {
    SQLiteInterface db = SQLiteInterface::get_resource_db();

    SQLiteResults res = db.execute("SELECT * FROM Elements;");

    for (unsigned int i = 0; i < res.size(); i++) {
      const SQLiteRow &row = res[i];

      elements.push_back(std::make_shared<Element>(
              row["Name"],
              row["Symbol"],
              row["NumberElectrons"],
              row["MolecularWeight"],
              row["HalfLife"],
              LinearEqn(row["BoilingPoint_Gradient"], row["BoilingPoint_Intercept"]),
              LinearEqn(row["MeltingPoint_Gradient"], row["MeltingPoint_Intercept"])
            ));
    }

    loaded = true;

  }

  return elements;
}

Element_ptr Element::get_element_by_n(int n)
{
  auto table = get_elements();
  return table[n-1];
}
