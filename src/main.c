#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

void get_win_size(int *rows_out, int *cols_out)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  *rows_out = w.ws_row;
  *cols_out = w.ws_col;
}

int main (int argc, char **argv)
{
  int rows, cols;
  get_win_size(&rows, &cols);

  

  return 0;
}
