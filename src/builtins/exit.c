static void free_input(char **input)
{
  int i;

  i = 0;
  while (input[i] != NULL)
  {
    free(input[i]);
    i++;
  }
  free(input);
}

void ft_exit(char **input)
{
  free(input);
  ft_putstr_fd("Exiting minishell...\n", STDERR_FILENO);
  
  exit(0);
}
