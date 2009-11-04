#ifndef RPROTOBUF_CONNECTIONS_H
#define RPROTOBUF_CONNECTIONS_H

typedef struct Rconn  *Rconnection;
struct Rconn {
    char* class;
    char mode[5];
    Rboolean text, isopen, incomplete, canread, canwrite, canseek, blocking, isGzcon;
    int (*fgetc)(struct Rconn *);
    size_t (*read)(void *, size_t, size_t, struct Rconn *);
    size_t (*write)(const void *, size_t, size_t, struct Rconn *);
};

#endif
