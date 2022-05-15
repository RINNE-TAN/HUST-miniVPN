//
// Created by csepsk on 2022/5/14.
//

#include "Tun.h"

Tun::Tun() {
    struct ifreq ifr{};
    memset(&ifr, 0, sizeof(ifr));

    // 1. Open the device
    tunfd = open("/dev/net/tun", O_RDWR);
    if (tunfd == -1) {
        printf("Open /dev/net/tun failed! (%d: %s)\n", errno, strerror(errno));
        exit(-1);
    }

    // 2. setup the virtual tun interface tun0
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    if (ioctl(tunfd, TUNSETIFF, &ifr) == -1) {
        printf("Setup TUN interface by ioctl failed! (%d: %s)\n", errno, strerror(errno));
        exit(-1);
    }

    // 3. use socket to connect the tun
    ctlSock = new IoctlIfSock(ifr);
}

void Tun::up(const char *runIP, const char *netmask) {
    // 4. Assign IP Address
    ctlSock->adapterAssignIp(runIP);
    // 5. Assign NetMask
    ctlSock->adapterAssignNetmask(netmask);
    // 6. Run TUN Device
    ctlSock->adapterActivate();

    printf("Setup TUN interface(%s) success!\n",ctlSock->getIfName());
}


ssize_t Tun::send(const char *buff, size_t len) const {
    return write(tunfd, buff, len);
}

ssize_t Tun::recv(char *buff, size_t size) const {
    return read(tunfd, buff, size);
}

int Tun::fd() const {
    return tunfd;
}

Tun::~Tun() {
    close(tunfd);
    delete ctlSock;
}

void Tun::addRouteTo(const char *destIP, const char *netmask) {
    ctlSock->adapterAddRouteTo(destIP,netmask);
}

const char *Tun::TunIfName() {
    return ctlSock->getIfName();
}

