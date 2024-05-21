#include "../../headers/builtins.h"

// void	print_space(t_cmd_data *d, int i)
// {
// 	if (d->args[i])
// 	{
// 		write(1, " ", 1);
// 		i++;
// 	}
// }

// /* printing string from start to end position or to the end of string
// if end == -1 */
// void	print_string(char *str, int start, int end)
// {
// 	while (str[start] != 0 && (start < end || end == -1))
// 	{
// 		write(1, &str[start], 1);
// 		start++;
// 	}
// }

// /*
// dolar 
// */
// void    handle_dolar(char *str, int start, int end, t_hmap *h)
// {
//     char    *ekey;

//     if (start == end) //if there is $ alone
//         write(1, "$", 1);
//     else
//     {
//         if (is_inside_quotes(str, start, end) == 1 //if we have quotes
//             || is_inside_quotes(str, start, end) == 2
//             || inside_mix(str, start, end) != 0)
//             print_string(str, start + 1, end - 1);
//         else //if we don't have quotes
//         {
//             ekey = malloc(end - start + 1);
//             if (!ekey)
//                 //error
//                 exit(EXIT_FAILURE);
//             if (key_exists(h, ekey) == 1) //if key exists it prints it's value
//                 print_string(return_value_hash(h, ekey), 0, -1);
//             free(ekey);
//         }
//     }
// }

// /*
// I need to make an extra function that will detect $ and check if after dolar we have anything but letters,
// numbers, '_' or quotes, and then it stops;
// if quotes are after $ right away it will take a word all the way until it comes to white space or end
// if quote is in the middle, it will take a word until first quote.
// if there is any other character other then letter, num ot '_', it will take a word until then
// when I find thi word, I send it to this function as an str
// */
// char    *detect_dolar(char *str, int start, int end)
// {

// }