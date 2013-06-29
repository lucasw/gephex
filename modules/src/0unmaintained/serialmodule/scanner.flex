%{
#include <stdlib.h>
%}

WS       [ \t]
COORD    [0-3]
SIZE     [0-4]
COL      [0-9]|([0-5][0-9])|("6"[0-3])
MONITOR  ("m"{WS}+"0")|("mon"{WS}+"4"{WS}+"3")|("mon"{WS}+{COORD}{WS}+{COORD})

BLK      "blk"{WS}+{SIZE}{WS}+{COORD}{WS}+{COORD}
CO       "co"{WS}+{COL}{WS}+{COL}{WS}+{COL}{WS}+{MONITOR}
CMD      {BLK}|{CO}

%%

^{CMD}$       { return 1;}

[ \t]+          /* eat up whitespace */    
    
.  {
     //fprintf (stderr,"Fehler beim Scannen. Ungültiges Token : '%s' \n",yytext);
     return 0;
   }

%%

// don't want to link against libflex...
int yywrap(void)
{
return 1;
}

int check_command(const char* command)
{
  int len = strlen(command);
  YY_BUFFER_STATE b;
  int result = 0;

  // append a newline at the end, if not already there
  if (command[len-1] == '\n')
  {
     b = yy_scan_bytes(command, len);
  }
  else
  {
   char* command_;   
   command_ = malloc(len+2);
   memcpy(command_, command, len);
   command_[len] = '\n';
   command_[len+1] = 0;
   b = yy_scan_bytes(command_, len+1);
   free(command_);
  }

  
  result = yylex();

  yy_delete_buffer(b);

  return result;
}
