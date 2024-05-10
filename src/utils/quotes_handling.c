#include "../../headers/utils.h"

/* 
CHECK THIS FUNCTION!
   return_value = 0 if we have open quote and not closed!
   return_value = 1 when inside pair of quotes we have another one ..........error for key
   return_value = 2 when we have same quotes closed without other quote inside
   return_value = 3 if there are no quotes
*/

static int   return_value(char quote, int inside_quotes, int flag)
{
   if (quote != 0)
    return (0);
  else if (quote == 0 && inside_quotes == 1)
    return (1);
  else if (quote == 0 && inside_quotes == 0 && flag == 1)
    return (2);
   else
     return (3);
}

int  check_word(char *string, int start, int end)
{
  int  inside_quotes;
  char quote;
   int   flag;

  inside_quotes = 0;
  quote = 0;
   flag = 0;
  while (start < end)
  {
      if (string[start] == '"' || string[start] == "'")
      {
         flag = 1;
        if (quote == 0)
          quote = string[start]; // we open quotes
        else if (quote == string[start])
          quote = 0; // we close quotes
        else
          inside_quotes = 1; // this means that we came to different quote after not closing this one, so we have inside_quotes
      }
     start++;
  }
  return (return_value(quote, inside_quotes, flag));
}

/*
   return_value = -1 open quotes and not closed
   return_value = 0 not inside quotes 
   return_value = 1 inside of double quotes with no quotes between
   return_value = 2 inside of single quotes with no quotes between
   return_value = 3 mix of different quotes
*/
int   is_inside_quotes(char *str, int start, int end)
{
   if (check_word(str, start, end) == 0)
      return (-1);
   if (check_word(str, start, end) == 3)
      return (0);
   if (str[start] == '"' && str[end - 1] == '"' && check_word(str, start + 1, end - 1) == 3)
      return (1);
   if (str[start] == "'" && str[end - 1] == "'" && check_word(str, start + 1, end - 1) == 3)
      return (2);
   return (3);
}
