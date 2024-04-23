void ft_exit(char *input)
{
  free(input);
  printf("Exiting minishell...\n");
  exit(0);
}
