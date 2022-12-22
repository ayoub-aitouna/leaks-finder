#include "./includes/leak_finder.h"

void show_leaked_list(char **list)
{
    int index = 0, i = 0;
    if (list[0] == NULL)
    {
        printf("\033[0;32m");
        printf("-------------------------------\n");
        printf("-             0 LEAK          -\n");
        printf("-------------------------------\n");
    }

    printf("\033[0;31m");
    while (list[index])
    {
        int i = 0;
        while (list[index][i])
        {
            if (list[index][i] == '+')
                list[index][i] = '\n';
            i++;
        }
        printf("%s", list[index++]);
    }
    printf("\033[0m");
}

void init(int *leaks_lenght, int *allocated_lenght)
{
    char *temp;
    int program_file = open("./program_file", O_RDONLY);
    int allocation_log = open("./allocation_log", O_RDONLY);
    if (program_file == -1 || allocation_log == -1)
        exit(1);
    while (1)
    {
        temp = get_next_line(allocation_log);
        if (ft_strnstr(temp, "ALLOCATED:", -1))
            (*allocated_lenght)++;
        if (temp == NULL)
            break;
    }

    while (1)
    {
        temp = get_next_line(program_file);
        if (ft_strnstr(temp, "LEAK", -1))
            (*leaks_lenght)++;
        if (temp == NULL)
            break;
    }
    // reseat;
    close(program_file);
    get_next_line(program_file);
}

char **filter(char **Allocated, char **LEAK, char **Selected_Allocated)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *line;
    int exists = 0;
    char *leak_line = malloc(16);
    int Selected_Allocated_index = 0;
    char *leak_line_n;

    while (Allocated[i] != NULL)
    {
        exists = 0;
        if ((line = ft_strnstr(Allocated[i], "ADDRESS: '", -1)))
        {

            j = 0;
            while (line[j + 10] != 0)
            {
                if (line[j + 10] == '\'')
                    break;
                leak_line[j] = line[j + 10];
                j++;
            }
            leak_line[j] = 0;
            k = 0;
            while (LEAK[k] != NULL)
            {
                if ((leak_line_n = ft_strnstr(LEAK[k], "LEAK: ", -1)))
                {
                    int leak_i = 0;
                    while (leak_line_n[leak_i + 6] != 0 && leak_line_n[leak_i + 6] != ' ')
                    {
                        if (leak_line_n[leak_i + 6] != leak_line[leak_i])
                        {
                            exists = 0;
                            break;
                        }
                        else
                            exists = 1;
                        leak_i++;
                    }
                    if (exists)
                    {
                        Selected_Allocated[Selected_Allocated_index++] = Allocated[i];
                    }
                }
                k++;
            }
        }
        i++;
    }
    Selected_Allocated[Selected_Allocated_index] = NULL;
    return (Selected_Allocated);
}

int main()
{
    char **LEAK;
    char **Allocated;
    char *temp;
    int i = 0;
    int leaks_lenght = 0;
    int allocated_lenght = 0;
    init(&leaks_lenght, &allocated_lenght);

    int program_file = open("./program_file", O_RDONLY);
    int allocation_log = open("./allocation_log", O_RDONLY);
    if (program_file == -1 || allocation_log == -1)
        exit(1);
    LEAK = malloc(leaks_lenght * sizeof(char *));
    Allocated = malloc((allocated_lenght + 1) * sizeof(char *));
    char **Selected_Allocated = malloc((allocated_lenght + 1) * sizeof(char *));

    leaks_lenght = 0;
    allocated_lenght = 0;
    while (1)
    {

        temp = get_next_line(program_file);
        if (temp == NULL)
            break;
        if (ft_strnstr(temp, "LEAK", -1))
            LEAK[leaks_lenght++] = temp;
    }
    close(program_file);
    while (1)
    {

        temp = get_next_line(allocation_log);
        if (temp == NULL)
            break;
        if (ft_strnstr(temp, "ALLOCATED:", -1))
            Allocated[allocated_lenght++] = temp;
    }
    close(allocation_log);
    LEAK[leaks_lenght] = NULL;
    Allocated[allocated_lenght] = NULL;
    filter(Allocated, LEAK, Selected_Allocated);
    show_leaked_list(Selected_Allocated);
}
