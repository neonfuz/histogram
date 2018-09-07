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
    if (scanf("%d\t", &entries[i].num) == EOF)
      return i;
    entries[i].str = NULL;
    size_t size = 0;
    int len = getline(&entries[i].str, &size, stdin);
    if (entries[i].str[len-1] == '\n')
      entries[i].str[len-1] = '\0';
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

// Minimum number of columns in a bar
#define MINBARCOLS 3

void tableprint(Entry *entries, int count, char *fmt, int maxwidth)
{
  Entry max = get_max_entry(entries, count);
  int numwidth = snprintf(NULL, 0, "%d", max.num);
  int strwidth = strlen(max.str);
  int width = numwidth + 1 + strwidth + 1;
  if (width > maxwidth + MINBARCOLS) {
    fprintf(stderr, "Err: Terminal not wide enough\n");
    exit(-1);
  }
  double divisor = (double)max.num / (maxwidth-width);
  int w;
  for (int i=0; i<count; ++i) {
    for (int c=0; fmt[c]; ++c) {
      switch (fmt[c]) {
      case 'n':
        w = printf("%d", entries[i].num);
        repeatchar(' ', numwidth+1-w);
        break;
      case 's':
        printf("%s", entries[i].str);
        repeatchar(' ', strlen(max.str)+1-strlen(entries[i].str));
        break;
      case 'b':
        repeatchar('=', entries[i].num/divisor);
        break;
      default: break;
      }
    }
    putchar('\n');
  }
}

int main (int argc, char **argv)
{
  int rows, cols;
  get_win_size(&rows, &cols);

  Entry entries[rows];
  int count = read_entries(entries, rows, cols);
  tableprint(entries, count, "nsb", cols);

  return 0;
}
