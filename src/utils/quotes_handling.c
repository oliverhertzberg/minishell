#include "../../headers/utils.h"

/* 
   return_value = 0 if we have open quote and not closed!
   return_value = 1 when inside pair of quotes we have another one
   return_value = 2 when we have same quotes closed without other quote inside
*/
int  check_word(char *string, int start, int end)
{
  int  inside_quotes;
  char quote;

  inside_quotes = 0;
  quote = 0;
  while (start < end)
  {
      if (string[start] == '"' || string[start] == "'")
      {
        if (quote == 0)
          quote = string[start]; // we open quotes
        else if (quote == string[start])
          quote = 0; // we close quotes
        else
          inside_quotes = 1; // this means that we came to different quote after not closing this one, so we have inside_quotes
      }
      start++;
  }
  if (quote != 0)
    return (0);
  else if (quote == 0 && inside_quotes == 1)
    return (1);
  else
    return (2);
}
