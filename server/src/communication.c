#include "../include/communication.h"

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/timer.h"

int build_message(message_t* msg, int id, int res, int t) {
    memset(msg, 0, sizeof(message_t));

    msg->rid = id;
    msg->pid = getpid();
    msg->tskres = res;
    msg->tskload = t;
    msg->tid = pthread_self();
    return 0;
}

int recv_message(message_t* msg) {
    int fd = get_public_fifo();
    fd_set fds;
    struct timeval timer;

    timer_get_remaining_timeval(&timer);
    timer.tv_sec++;

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    int err;
    err = select(fd + 1, &fds, NULL, NULL, &timer);

    if (err == -1) {
        close(fd);
        return ERROR;
        perror("select()");
    } else if (err) {
        size_t data_size = read(fd, msg, sizeof(message_t));

        return sizeof(message_t) == data_size ? 0 : ERROR;
    }
    return ERROR;
}

int send_private_message(message_t* msg, pid_t pid, pthread_t tid) {
    char fifo[MAX_FIFO_NAME] = "";
    snprintf(fifo, MAX_FIFO_NAME, "/tmp/%d.%lu", pid, tid);
    fprintf(stderr, "[server] opened %s\n", fifo);
    int fd = open(fifo, O_RDWR);
    if (fd < 0)
        return ERROR;
    perror("private fifo");
    fprintf(stderr, "open fd: %d\n", fd);
    fd_set fds;
    struct timeval timer;
    timer_get_remaining_timeval(&timer);
    timer.tv_sec++;

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    int err;
    err = select(fd + 1, NULL, &fds, NULL, &timer);

    if (err == -1) {
        close(fd);
        perror("select()");
        return ERROR;
    } else if (err) {
        int sent_size = write(fd, msg, sizeof(message_t));

        fprintf(stderr, "%d size sent: %d %lu\n", msg->rid, sent_size, sizeof(message_t));

        int err = close_fifo(fd);

        if (sent_size != sizeof(message_t) || err)
            return ERROR;
        return 0;
    }
    fprintf(stderr, "[server]failed\n");
    close(fd);
    return ERROR;
}
