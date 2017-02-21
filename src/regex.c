#include "regex.h"
#include "bst.h"
#include "array.h"


struct sstring_regex {
   
};

// I'm going to stuff character classes into the negatives
struct transition {
  int character;
  int default_state;
  int alt_state;
};

static struct state_table {
  int cur_state;
  int num_states;
};
