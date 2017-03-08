#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_FOR_DIV_COUNT if(diff<0){printf("[error]"); return 0;}
#define BUFF_SIZE 2047

typedef enum enum_search_return
{
  INIT,
  OPEN_DIV,
  CLOSE_DIV,
  NO_DIV,
  END_OF_STRING,
  ERROR
} search_return;

char **div_format (char **);	              //prototype
search_return div_search (char *, char **);

char **div_format (char **s)
{
  ;
}

char *first_space_delete (char *s)
{
  while (*s == ' ')
    s++;
  return s;
}

void call_error ()
{
  printf("[error]");
  exit (1);
}

void space_print (unsigned int n)
{ 
  if ((int) n < 0)
    {
      call_error ();
    }  
        
  while (n--)
    printf ("    ");
}        

search_return div_search (char *begin, char **curr)
{
  char *open, *close;// *EOS;
  *curr = begin;
  
  open  = strstr(begin,  "<div>");
  close = strstr(begin, "</div>");
//EOS   = strstr(begin, "\n");
//if (open == NULL && close == NULL)
//  {
//    return END_OF_STRING
//  }
  if (open == NULL)
    if (close != NULL)
      {
        *curr = first_space_delete(close+sizeof("</div>"));
        return CLOSE_DIV;
      }
    else
      {
        return NO_DIV;      //Ничего не нашли
      }
  else
    if (close == NULL)
      {
        *curr = first_space_delete(open+sizeof("<div>"));
        return OPEN_DIV;
      }
    else
      if (open>close)
        {
          *curr = first_space_delete(open+sizeof("<div>"));
          return OPEN_DIV;
        }
      else
        {
          *curr = first_space_delete(close+sizeof("</div>"));
          return CLOSE_DIV;
        } 
  return ERROR;
}

int
main (void)
{
  char text[BUFF_SIZE], c;	//сделать предположение о длине строки или выделять инкрементом сколько надо? Реаллок
  char *begin, *curr;
  unsigned int counter_open = 0, counter_close = 0, diff = 0;
  search_return res = ERROR;
  
  printf ("test:\n");
  while (fgets (text, sizeof (text), stdin))
    {				//сжираем строку со входа
      begin = text;
      while (*begin == ' ')
	      begin++;
	      
	    res = INIT;
	    
	    while (res != OPEN_DIV)   //тут нужно сделать итератор по тегам - если достигли конца строки, сказать об этом
        {
          res = div_search (begin, &curr);
      
          switch (res)
            {
            case OPEN_DIV:
              counter_open++;
              diff = counter_open - counter_close;
              CHECK_FOR_DIV_COUNT
              space_print (diff);
              printf ("<div>\n");
              break;
            case CLOSE_DIV:
              counter_close++;
              diff = counter_open - counter_close;
              CHECK_FOR_DIV_COUNT
              space_print (diff);
              printf ("</div>\n");
              break;
            case NO_DIV:
              diff = counter_open - counter_close;
              CHECK_FOR_DIV_COUNT
              space_print (diff);
              if (curr != NULL)
                printf ("%s\n", curr);
              break;
            case ERROR:
              call_error ();
              break;
            }   
        }
    }
}
