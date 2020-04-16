#include "random.hpp"
#include "vec.hpp"

Vec3 vec3_urand(double min, double max)
{
  return Vec3({uniform_rand(min, max), uniform_rand(min, max), uniform_rand(min, max)});
}


Vec3 vec3_nrand(double mean, double std)
{
  return Vec3({normal_rand(mean, std), normal_rand(mean, std), normal_rand(mean, std)});
}


Vec2 vec2_urand(double min, double max)
{
  return Vec2({uniform_rand(min, max), uniform_rand(min, max)});
}


Vec2 vec2_nrand(double mean, double std)
{
  return Vec2({normal_rand(mean, std), normal_rand(mean, std)});
}


template<int N>
std::ostream& operator<< (std::ostream &os, const VecN<N> v) {
  os << v.repr();
  return os;
}

template<>
std::ostream& operator<< <3>(std::ostream &os, const VecN<3> v) {
  os << v.repr();
  return os;
}

template<>
std::ostream& operator<< <2>(std::ostream &os, const VecN<2> v) {
  os << v.repr();
  return os;
}
