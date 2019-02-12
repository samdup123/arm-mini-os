#ifndef UTILS_H_
#define UTILS_H_

#define nullptr 0

// terminates the program with a custom message
void die(void (*print_fn)(const char *), const char *msg);

// conditionally terminates the program with a custom message
void dieif(int should_die, void (*print_fn)(const char *), const char *msg);

#endif  // UTILS_H_
