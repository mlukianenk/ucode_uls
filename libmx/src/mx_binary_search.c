#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int min = 0;
	int max = size - 1;
	int mid;

	while(min <= max) {
  mid = (min + max) / 2;
  (*count)++;
  if(mx_strcmp(arr[mid], s) < 0) {
  	min = mid + 1;
  }
  else if(mx_strcmp(arr[mid], s) > 0) {
  	max = mid - 1;
  }
  else {
  	return mid;
  }
	}
	*count = 0;
	return -1;
}
