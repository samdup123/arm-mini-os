#ifndef DIE_H_
#define DIE_H_

// Stop system and loop forever, intermittently displaying a message.
void die(void (*print_fn)(const char*), const char* message);

#endif  // DIE_H_
