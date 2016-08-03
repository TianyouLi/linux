#!/bin/bash
echo -ne "Installing System.map... "
cp System.map /boot/System.map
echo "done."

echo -ne "Installing bzimage... "
cp arch/x86_64/boot/bzImage /boot/vmlinuz-linux-cherrylake
echo "done."

echo -ne "Generating initramfs... "
mkinitcpio -k /boot/vmlinuz-linux-cherrylake -c /etc/mkinitcpio.conf -g /boot/initramfs-cherrylake.img
echo "done."

echo -ne "Install modules... "
make modules_install
echo "done"

echo -ne "Install headers... "
make headers_install
echo "done"

