void ft_exit(char *input)
{
  free(input);
  ft_putstr_fd("Exiting minishell...\n", STDERR_FILENO);
  exit(0);
}
