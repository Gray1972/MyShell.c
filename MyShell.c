#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LINE 80 

void setup(char inputBuffer[], char *args[], int *flag)
{
  int length,
      i,
      start,
      ct;
  ct = 0;
  length = read(0,inputBuffer,MAX_LINE);

  start = -1;
  if (length == 0)
    exit(0);
  if (length < 0)
  {
    perror("error reading the command");
    exit(-1);
  }

  for(i=0;i<length;i++)
  {
    switch (inputBuffer[i])
    {
      case ' ':
      case '\t' :
        if(start != -1)
        {
          args[ct] = &inputBuffer[start];
          ct++;
        }
        inputBuffer[i] = '\0';
        start = -1;
        break;
      case '\n':
        if(start != -1) 
        {
          args[ct] = &inputBuffer[start];
          ct++;
        }
        inputBuffer[i] = '\0';
        start = -1;
        args[ct] = NULL;
        break;

        default :
          if (start == -1)
            start = i;
          if (inputBUffer[i] == '&' 
          {
            *flag = 1; 
            inputBuffer[i] = '\0';
          }
      }
    }
    args[ct] = NULL;
  }

int main(void)
{
  int flag;
  char *args{MAX_LINE/2];
  int child,
      status;
  char inputBuffer[MAX_LINE];

  while (1)
  {
    flag = 0;
    printf(" COMMAND->\n");
      setup(inputBuffer, args, &flag);
      child = fork();
    switch(child)
    {
      case -1:
        perror("could not fork the process");
        break;

      case 0:
        status = execvp(args[0],args);
        if (status != 0)
        {
          perror(" error in execvp");
          exit (-2);
        }
        break;

      default : 
        if(flag==0)
          while (child != wait((int *) 0)); 
    }
  }
}
