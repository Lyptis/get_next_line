# get_next_line
Function that returns next line with '/n' of the filedescriptor(fd)

## Usage
    char  *get_next_line(int fd);

## Return Value
Returns a `char *` Malloc'd null terminated.
The end of the `char *` include `'/n'`

If return value is `NULL`, file is fully readed or an error occured.
