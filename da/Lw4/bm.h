#ifndef _BM_
#define _BM_

#include <vector>

void PreBmBc(std::vector<std::pair<std::string, int> > &pattern, int *array, int max, int pSize);
void Nfunc(std::vector<std::pair<std::string, int> > &pattern, int *array,int pSize);
void Lfunc(std::vector<std::pair<std::string, int> > &pattern, int *array, int *nArray, int * llArray,int pSize);

#endif