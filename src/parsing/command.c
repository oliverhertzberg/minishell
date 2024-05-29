#include "../../headers/minishell.h"

int	count_words(char *input, int j, t_cmd_data **c)
{
	char	*word;
	int		count;
	int		i;

	i = j;
	count = 0;
	while (input[i] && input[i] != '|')
	{
		word = get_next_word(input, &i);
		if (!word)
			error_exit(NULL, "malloc failed \n", c, 1);
		if (word[0] == '<' || word[0] == '>' \
			|| word[0] == '|' || word[0] == '\0')
		{
			free (word);
			break ;
		}
		free (word);
		count++;
	}
	return (count);
}

void	handle_command(t_cmd_data **c, char *input, int *i)
{
	int	word_count;
	int	j;

	word_count = count_words(input, *i, c);
	(*c)->arg_count += word_count;
	j = -1;
	while (++j < word_count)
		arg_lstadd_back(&(*c)->arg_lst, arg_lstnew(get_next_word(input, i)));
}
