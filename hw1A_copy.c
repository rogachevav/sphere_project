#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 2047

typedef enum enum_search_return
{
  OPEN_DIV,
  CLOSE_DIV,
  NO_DIV,                                      //после DIV нет непробельных символов
  ERROR
} search_return;

char **div_format (char **);	              //prototype
search_return div_search (char *, char **);

char **
div_format (char **s)
{
  ;
}

char *first_space_delete (char *s)
{
  while (*s == ' ')
    s++;
  return s;
}

void space_print (unsigned int n)
{ 
  if ((int) n < 0)
    {
      printf("[error]");
      exit (1);
    }  
        
  while (n--)
    printf ("    ");
}        
search_return
div_search (char *begin, char **curr)
{
  char *open, *close;
  *curr = begin;
  
  open  = strstr(begin,  "<div>");
  close = strstr(begin, "</div>");
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
	      
      res = div_search (begin, &curr);
      
      switch (res)
        {
        case OPEN_DIV:
          counter_open++;
          diff = counter_open - counter_close;
          space_print (diff);
          printf ("<div>\n");
          break;
        case CLOSE_DIV:
          counter_close++;
          diff = counter_open - counter_close;
          space_print (diff);
          printf ("</div>\n");
          break;
        case NO_DIV:
          diff = counter_open - counter_close;
          space_print (diff);
          if (curr != NULL)
            printf ("%s\n", curr);
          break;
        case ERROR:
          break;
        }
      

    }



















//считывание с буферизацией - fgets?

//проверка на количество <div> и <\div>

//удаление лишних пробелов (можно совместно с прошлой функцией реализовать)

//модернизация и расставление табуляции (придумать быстрый алгоритм, желательно поточный, мб. итератор пробелов запустить с декрементом и инкрементом при прохождении через тег)

//вывод в stdout

//TODO сделать умный отлавливатель ошибок
}
