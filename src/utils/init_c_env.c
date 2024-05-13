#include "../../headers/minishell.h"

void init_c_env(t_cmd_env *c)
{
	c->hashmap = NULL;
	c->exit_code = 0;
	c->paths = NULL;
	c->num_of_cmds = 0;
	c->pid = NULL;
	c->pipes = NULL;
}
