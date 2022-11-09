#include "get_next_line.h"
#include <stdio.h>
int	main()
{
	int		fd;
	char	*line;
	
	//fd = open("./null.txt", O_RDONLY);
	fd = open("./mobyDick.txt", O_RDONLY);
	//fd = open("./numeros.txt", O_RDONLY);
	line = get_next_line(42);
	printf("====%s",line);
	free(line);
	
	line = get_next_line(fd);
	printf("====%s",line);
	free(line);
	close(fd);
	//system("leaks -q a.out");
}

////BONUS////

/*
#include <stdio.h>
int	main()
{
	char	*temp;
	int	fd1, fd2, fd3;
	int i;

	fd1 = open("./mobyDick.txt", O_RDONLY);
	fd2 = open("./numeros.txt", O_RDONLY);
	fd3 = open("./null.txt", O_RDONLY);
	i = 0;
	while(i < 5)
	{
		i++;
		printf("%d---\n",i);
		temp = get_next_line(fd1);
		if (!temp)
		break ;
		printf("%s", temp);
		free(temp);
		
		temp = get_next_line(fd2);
		if (!temp)
		break ;
		printf("%s", temp);
		free(temp);
		
		temp = get_next_line(fd3);
		printf("%s\n", temp);
		free(temp);
	}
	return (0);
}
}*/