/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/26 19:21:10 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_metachar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	is_to_interpret(char *str, int i, int sgl_quote, int dbl_quote)
{
	if (dbl_quote)
		return (1);
	else if (sgl_quote)
		return (0);
	return (1);
}

static int	is_separator(char c)
{
	if (c == ' ' || c == '$' || c == '|' || c == '\"' || c == '\'' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	dollar_key_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && !is_separator(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*find_dollar_value(t_list *shellvars, char *dollar_key)
{
	char	*dollar_value;
	
	while (shellvars)
	{
		if (ft_strcmp(((t_shellvar *)shellvars->content)->key, dollar_key) == 0)
			return (((t_shellvar *)shellvars->content)->value);	
		else	
			shellvars = shellvars->next;
	}
	return (NULL);
}

static int	dollar_value_len(t_data *data, char *str, int i)
{
	int		dollar_value_len;
	char	*dollar_key;
	char	*dollar_value;
	int		j;

	dollar_key = malloc((dollar_key_len(str, i) + 1) * sizeof(char));
	if (!dollar_key)
		return (-1);
	j = 0;
	while (str[i + j] && !is_separator(str[i + j]))
	{
		dollar_key[j] = str[i + j];
		j++;
	}
	dollar_key[j] = '\0';
	dollar_value = getenv(dollar_key); /*cherche dans env sinon cherche dans lst >> priorité ? */
	if (dollar_value == NULL)
		dollar_value = find_dollar_value(data->shellvars, dollar_key);
	printf("dollar_key = %s\n", dollar_key);
	printf("dollar_value = %s\n", dollar_value);
	dollar_value_len = ft_strlen(dollar_value);
	return (dollar_value_len);
}

static int	dst_len(t_data *data, char *str)
{
	int		i;
	bool	sgl_quote;
	bool	dbl_quote;
	int		len;

	sgl_quote = false;
	dbl_quote = false;
	i = 0;
	len = 0;
	while(str[i])
	{
		if (str[i] == '\"')
			dbl_quote = !dbl_quote;
		if (str[i] == '\'')
			sgl_quote = !sgl_quote;
		if (str[i] == '$' && str[i + 1] && is_to_interpret(str, i, sgl_quote, dbl_quote))
		{
			len += dollar_value_len(data, str, i + 1);
			i += dollar_key_len(str, i + 1);
		}
		else
			len++;
		i++;
	}
	printf("total dst_len = %d\n", len);
	return (len);
}

char *metachar_interpreter(t_data *data, char *src)
{
	char *dst;

	printf("src = %s\n", src);
	if (!has_metachar(src))
		return (src);
	dst_len(data, src);
	
	return (dst);
}

