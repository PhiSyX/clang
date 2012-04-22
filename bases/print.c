#include <stdio.h>

#define LF "\n"

void
printw(char* w1, char* w2);

int
main()
{
  printw("Hello", "world");
  printw("Salut", "comment va-t'on?");
  printw("Ho", "petit sacripant");
  printw("Nous te souhaitons la bienvenue cher visiteur",
         "profite bien bien de ce code source");
  return 0;
}

void
printw(char* w1, char* w2)
{
  printf("%s, %s!%s", w1, w2, LF);
}

/* eof */