#include "../../headers/minishell.h"

static void	create_new_node(t_cmd_data **p, t_cmd_data **c, t_cmd_env *e)
{
	lstadd_back(p, lstnew(e));
	e->num_of_cmds++;
	*c = (*c)->next;
}

static int	struct_empty(t_cmd_data **c)
{
	if ((*c)->outfile || (*c)->heredoc || (*c)->infile || (*c)->arg_count > 0)
		return (0);
	return (1);
}

static void	create_args_array(t_cmd_data **c)
{
	t_arg_lst	*current;
	int			i;

	if ((*c)->env_ptr->parsing_error == 1)
		return ;
	if (struct_empty(c))
	{
		(*c)->env_ptr->parsing_error = 1;
		return ;
	}
	(*c)->args = (char **)malloc(sizeof(char *) * ((*c)->arg_count + 1));
	if (!(*c)->args)
		error_exit(NULL, "malloc failed\n", c, 1);
	current = (*c)->arg_lst;
	i = -1;
	while ((++i < (*c)->arg_count) && current)
	{
		(*c)->args[i] = current->arg;
		current = current->next;
	}
	(*c)->args[i] = NULL;
	if ((*c)->args[0])
		clean_dlr((*c)->args, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
	dprintf(2, "%c\n", (*c)->args[0][0]);
	arg_lstclear(&(*c)->arg_lst);
}

void	parse_input(t_cmd_data **c, char *input, t_cmd_env *c_env)
{
	t_cmd_data	*current;
	int			i;

	current = *c;
	i = 0;
	while (input[i] && !c_env->parsing_error)
	{
		if (i > 0)
			create_new_node(c, &current, c_env);
		while (input[i] && !c_env->parsing_error)
		{
			while (ft_isspace(input[i]) == 1)
				i++;
			if (input[i] == '|')
			{
				i++;
				break ;
			}
			if (input[i] == '<' || input[i] == '>')
				handle_redirection(&current, input, &i);
			else
				handle_command(&current, input, &i);
		}
		create_args_array(&current);
	}
}
