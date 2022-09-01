static int	redirection_word_checker(char *str, int i)
{
	if (str[i] == '|')
	{
		if (str[i - 1] && str[i - 1] == '|')
			return (1);
	}
	if (str[i] == '>')
	{
		if ((str[i - 1] && str[i - 1] == '>' && str[i - 2] && str[i - 2] == '>')
			|| (str[i - 1] && str[i - 1] == '<'))
			return (1);
	}
	if (str[i] == '<')
	{
		if ((str[i - 1] && str[i - 1] == '<' && str[i - 2] && str[i - 2] == '<')
			|| (str[i - 1] && str[i - 1] == '>'))
			return (1);
	}
	return (0);
}

if (redirection_word_checker(str, i) != 0)
			{
				ft_printf("syntax error near unexpected word `%c'\n", str[i]);
				return (1);
			}