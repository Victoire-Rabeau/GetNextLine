/*
** EPITECH PROJECT, 2020
** get next line
** File description:
** main
*/

#include "get_next_line.h"

static int my_line_len(char const *str)
{
    int i = 0;

    for (; str[i] && str[i] != '\n'; i++);
    return i;
}

static char *read_file(int fd, char *buff)
{
    int offset = 0;
    int len = 1;

    while (len > 0) {
        len = read(fd, buff + offset, READ_SIZE);
        offset += len;
    }
    buff[offset] = '\0';
    return buff;
}

static char *string_to_array(char *buff, int len)
{
    char *str = malloc(sizeof(char) * len + 1);
    int i = 0;
    int j = 0;

    if (!str)
        return NULL;
    for (; j < len ; j++) {
        str[j] = buff[i];
        i++;
    }
    str[len] = '\0';
    return str;
}

static char **fill_buffer(char *buff)
{
    char **buffer;
    int y = 1;
    int j = 0;
    int len = 0;
    int count = 1;

    for (int i = 0; buff[i]; i++)
        if (buff[i] == '\n')
            y++;
    buffer = malloc(sizeof(char *) * (y + 1));
    if (!buffer)
        return NULL;
    for (; count <= y; count++, j++) {
        len = my_line_len(buff);
        buffer[j] = malloc(sizeof(char) * len + 1);
        buffer[j] = string_to_array(buff, len);
        buff += (len + 1);
    }
    buffer[j] = NULL;
    return buffer;
}

char *get_next_line(int fd)
{
    char *buff;
    char buff2[1000000];
    static char **buffer;
    static int i = -1;

    if (fd == -1)
        return NULL;
    if (i == -1) {
        buff = read_file(fd, buff2);
        buffer = fill_buffer(buff);
    }
    if (!buffer)
        return NULL;
    i++;
    return buffer[i];
}
