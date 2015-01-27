
#include <iostream>
#include "../timer.h"
#include "../data_generator.h"
#include "../../src/algorithms/sort.h"

template<typename Seq>
class SortTimer {
    Timer t;
    void (*func)(typename Seq::iterator first, typename Seq::iterator last);
    DataGenerator<Seq> gen;
  public:
    SortTimer(void (*func)(typename Seq::iterator first, typename Seq::iterator last));
    float time(int inp_sz, int runs = 1);

};

template<typename Seq>
SortTimer<Seq>::SortTimer(void (*sort_func)(typename Seq::iterator first, typename Seq::iterator last)) {
  func = sort_func;

}

template<typename Seq>
float SortTimer<Seq>::time(int inp_sz, int runs) {
  Seq* sequences = new Seq[runs];

  // Fill the sequences using data generator
  for(int i = 0; i < runs; i++)
    sequences[i] = gen.random_data(inp_sz);

  t.start();

  // Run the sorting routine on each of the seq
  for(int i = 0; i < runs; i++)
    func(sequences[i].begin(), sequences[i].end());

  t.stop();
  return t.time_elapsed();
}

int main() {

  SortTimer<std::vector<int>> st1(merge_sort);
  std::cout << "Running time for merge sort for input size : 1000 and runs = 1000 is : " 
  			<<  st1.time(1000, 1000) << " sec" << std::endl;
  			
  SortTimer<std::vector<int>> st2(quick_sort);
  std::cout << "Running time for quick sort for input size : 1000 and runs = 1000 is : " 
  			<<  st2.time(1000, 1000) << " sec" << std::endl;
  			
  			
  SortTimer<std::vector<int>> st3(selection_sort);
  std::cout << "Running time for selection sort for input size : 1000 and runs = 1000 is : " 
  			<<  st3.time(1000, 1000) << " sec" << std::endl;
  			
  SortTimer<std::vector<int>> st4(std::sort);
  std::cout << "Running time for std sort for input size : 1000 and runs = 1000 is : " 
  			<<  st4.time(1000, 1000) << " sec" << std::endl;
  
  
}
