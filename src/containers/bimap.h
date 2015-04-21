
#ifndef _BIMAP_H
#define _BIMAP_H

#include <map>
#include <vector>

template<typename type1, typename type2>
class bimap {

  public:

    bimap();

    void insert(const type1& elt1, const type2& elt2);

    const type2& getimage(const type1& elt) const;
    const type1& getpreimage(const type2& elt) const;

  private:

    typedef std::pair<typename std::map<type1, int>::iterator, typename std::map<type2, int>::iterator> dir_entry;

    std::map<type1, int> type1set;
    std::map<type2, int> type2set;
    std::vector<dir_entry> directory; // An indirection
    int dir_entries;

};

template<typename type1, typename type2>
bimap<type1, type2> :: bimap() {
  dir_entries = 0;
}

template<typename type1, typename type2>
void bimap<type1, type2> :: insert(const type1& elt1, const type2& elt2) {

  // throw an exception if either elt1 or elt2 exists

  auto ret1 = type1set.insert(std::make_pair(elt1, dir_entries));
  auto ret2 = type2set.insert(std::make_pair(elt2, dir_entries));

  directory.push_back(std::make_pair(ret1.first, ret2.first));
  ++dir_entries;

}

template<typename type1, typename type2>
const type2& bimap<type1, type2> :: getimage(const type1& elt) const {

  auto it = type1set.find(elt);
  if(it == type1set.end())
    throw "Invalid element";

  return (directory[it->second].second)->first;

}

template<typename type1, typename type2>
const type1& bimap<type1, type2> :: getpreimage(const type2& elt) const {

  auto it = type2set.find(elt);
  if(it == type2set.end())
    throw "Invalid element";

    return (directory[it->second].first)->first;

}

#endif
