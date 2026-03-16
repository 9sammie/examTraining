/* Allowed functions: pipe, fork, dup2, execvp, close, exit

write the following function:

    int    ft_popen(const char file, char const argv[], char type)

The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

example:

int main() {
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');

    char line;
    while(line = get_next_line(fd))
        ft_putstr(line);
}

Hint: Do not leak file descriptors! */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const av[], char type)
{
	int fd[2];
	pid_t pid;

	if (!file || !av || (type != 'w' && type != 'r'))
		return -1;
	if (pipe(fd) < 0)
		return -1;

	pid = fork();
	if (pid < 0)
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
		return -1;
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], 1) == -1)
				exit(1);
		}
		if (type == 'w')
		{
			if (dup2(fd[0], 0) == -1)
				exit(1);
		}
		close(fd[1]);
		close(fd[0]);
		execvp(file, av);
		exit(1);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return(fd[0]);
		}
		else
		{
			close(fd[0]);
			return(fd[1]);
		}
	}
}

int main()
{
	int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');

	char buf[256];
	int n;

	while ((n = read(fd, buf, 256)) > 0)
		write(1, buf, n);

	close(fd);
	return (0);
}