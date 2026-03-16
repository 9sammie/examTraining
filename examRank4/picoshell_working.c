#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int io_fd[2] = {-1, -1};
	int previous_fd = -1;
	int i = 0;
	int status;
	pid_t cpid;

	if (!cmds)
		return 1;

	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(io_fd) == -1)
			return 1;
		cpid = fork();
		if (cpid == -1)
		{
			close(io_fd[0]);
			close(io_fd[1]);
			return 1;
		}
		if (cpid == 0)
		{
			if (i != 0)
			{
				if (dup2(previous_fd, 0) == -1)
				{
					close(io_fd[0]);
					close(io_fd[1]);
					if (previous_fd != -1)
						close(previous_fd);
					exit(1);
				}
			}
			if (cmds[i + 1])
			{
				if (dup2(io_fd[1], 1) == -1)
				{
					close(io_fd[0]);
					close(io_fd[1]);
					if (previous_fd != -1)
						close(previous_fd);
					exit(1);
				}
			}
			close(io_fd[0]);
			close(io_fd[1]);
			if (previous_fd != -1)
				close(previous_fd);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if (previous_fd != -1)
				close(previous_fd);
			if (cmds[i + 1])
			{
				close(io_fd[1]);
				previous_fd = io_fd[0];
			}
			i++;
		}
	}
    while (wait(&status) > 0)
	{
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return 1;
	}
	return 0;
}

int main(int ac, char **av)
{
    char **cmds[200];
    int j = 0;
    
    if (ac < 2)
        return 1;
    
    cmds[j++] = &av[1];
    
    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] == '|' && av[i][1] == '\0')
        {
            av[i] = NULL;
            if (i + 1 < ac)
                cmds[j++] = &av[i + 1];
        }
    }
    cmds[j] = NULL;

    picoshell(cmds);
    return 0;
}
