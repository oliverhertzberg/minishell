void ft_exit(char *input)
{
  free(input);
  ft_putstr_fd("Exiting minishell...\n", 2);
  exit(0);
}
