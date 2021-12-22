#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int is_process_child(int pid, int ppid) {
  char filename[18];
  FILE* proc_file;
  int proc_number = pid;
  while (proc_number > 1) {
    sprintf(filename, "/proc/%d/stat", proc_number);
    proc_file = fopen(filename, "r");
    fscanf(proc_file, "%*d %*s %*c %d", &proc_number);
    fclose(proc_file);
    if (proc_number == ppid)
      return 1;
  }
  return 0;
}

int main(int argc, char* argv[])
{
  int pid, ppid, count = 1;
  struct dirent *dirEntry;
  DIR *dir;

  ppid = (argc != 2) ? 1 : atoi(argv[1]);
  dir = opendir("/proc/");
  while (NULL != (dirEntry = readdir(dir))) {
    pid = atoi(dirEntry->d_name);
    if (pid <= 1)
      continue;
    count += is_process_child(pid, ppid);
  }
  closedir(dir);
  printf("%d\n", count);
  return 0;
}
