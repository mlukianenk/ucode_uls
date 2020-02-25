#include "libmx.h"

int mx_count_words(const char *str, char c) {
	int nbofwords = 0;
	int flag = 0;
	int increment = 1;
	if(!str) {
  return -1;
	}
	while(*str) {
  if(*str == c)
  	flag = 0;	
  else if (flag == 0) {
  	flag = increment;
  	++nbofwords;
  }
  ++str;
	}
	return nbofwords;
}
