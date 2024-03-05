 #include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/usbdevice_fs.h>
#include <libudev.h>
#include <stdio.h>

//numara și returneaza numarul de dispozitive de intrare/iesire, mai precis dispozitive USB, conectate la sistemul de operare.
//udev detectează automat atunci când dispozitive hardware sunt conectate sau deconectate din sistem
int numberOfIODevices() {
   // Se declara un pointer la o structură udev, care reprezintă un obiect udev și va fi utilizat pentru a interacționa cu subsistemul udev.
    struct udev *udev;
    //se declara un pointer la o structura, folosit pentru a efectua listarea dispozitivelor
    struct udev_enumerate *enumerate;
    // se declara pointeri la structuri, utilizati pentru a parcurge lista de dispozitive
    struct udev_list_entry *devices, *dev_list_entry;
    //contor pentru a numara dispozitivele USB
    int num_usb_devices = 0;

    // cream un obiect udev nou folosit pentru a efectua listarea dispozitivelor
    udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Failed to create udev.\n");
        return -1;
    }

    // adaugam un filtru pentru a lista doar dispozitivele USB
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "usb");
    udev_enumerate_scan_devices(enumerate);
    // obtinem lista de dispozitive
    devices = udev_enumerate_get_list_entry(enumerate);

    // parcurgem lista de dispozitive si numaram dispozitivele USB
    udev_list_entry_foreach(dev_list_entry, devices) {
        num_usb_devices++;
    }

    // Cleanup
    udev_enumerate_unref(enumerate);
    udev_unref(udev);


    return num_usb_devices;
}