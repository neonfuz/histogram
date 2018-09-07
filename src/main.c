#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

void get_win_size(int *rows_out, int *cols_out)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  *rows_out = w.ws_row;
  *cols_out = w.ws_col;
}

typedef struct {
  int num;
  char *str;
} Entry;

int read_entries(Entry *entries, int max, int maxlen)
{
  for (int i=0; i<max; ++i) {
    if (scanf("%d\t%s\n", &entries[i].num, entries[i].str) == EOF)
      return i;
    entries[i].str = malloc(maxlen+1);
    printf("%d\t%s\n", entries[i].num, entries[i].str);
    entries[i].str = realloc(entries[i].str, strlen(entries[i].str));
  }
  return max;
}

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAX_WRAP(fun,a,b) (fun(a)>fun(b)?a:b)

// Get largest number and longest string
Entry get_max_entry(Entry *entries, int count)
{
  Entry max = {0, ""};
  for (int i=0; i<count; ++i) {
    max.num = MAX(max.num, entries[i].num);
    max.str = MAX_WRAP(strlen, max.str, entries[i].str);
  }
  return max;
}

void repeatchar(char c, int num) {
  for(int i=0; i<num; ++i) putchar(c);
}

int main (int argc, char **argv)
{
  int rows, cols;
  get_win_size(&rows, &cols);

  Entry entries[rows];
  int count = read_entries(entries, rows, cols);
  Entry max = get_max_entry(entries, count);

  int width = snprintf(NULL, 0, "%d\t%s ", max.num, max.str);
  if (width >= cols) {
    fprintf(stderr, "Err: Terminal not wide enough\n");
    return -1;
  }
  double divisor = (double)max.num / (cols-width);

  for (int i=0; i<count; ++i) {
    printf("%d\t%s ", entries[i].num, entries[i].str);
    repeatchar(' ', strlen(max.str)-strlen(entries[i].str));
    repeatchar('=', entries[i].num/divisor);
    putchar('\n');
  }

  return 0;
}
