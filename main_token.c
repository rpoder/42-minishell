#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
}
