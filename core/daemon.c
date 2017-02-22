#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "libp2p/net/p2pnet.h"
#include "ipfs/core/daemon.h"
#include "ipfs/core/ipfs_node.h"

int ipfs_daemon (int argc, char **argv)
{
    int count_pths = 0;
    pthread_t work_pths[MAX];
    struct IpfsNodeListenParams listen_param;

    fprintf(stderr, "Initializing daemon...\n");

    // create a new IpfsNode
    struct IpfsNode local_node;
    local_node.mode = MODE_ONLINE;
    //local_node.peerstore = ipfs_peerstore_new();
    //local_node.repo = fsrepo;
    //local_node.peer_id = peer_id;

    // Set null router param
    listen_param.ipv4 = 0; // ip 0.0.0.0, all interfaces
    listen_param.port = 4001;
    listen_param.local_node = &local_node;

    // Create pthread for ipfs_null_listen.
    if (pthread_create(&work_pths[count_pths++], NULL, ipfs_null_listen, &listen_param)) {
        fprintf(stderr, "Error creating thread for ipfs_null_listen\n");
        return 1;
    }

    fprintf(stderr, "Daemon is ready\n");

    // Wait for pthreads to finish.
    while (count_pths) {
        if (pthread_join(work_pths[--count_pths], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }

    // All pthreads aborted?
    return 0;
}
