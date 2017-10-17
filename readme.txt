To run these examples, you will need to take the following steps.

(1) Prepare the arm-linux-gnueabihf compiler toolchain.

Go to C:/intelFPGA_lite/17.0/embedded/ds-5_installer
Click on setup.exe
Go through the installation of the compiler toolchain
This will install a linux-GNU chain for ARM under
C:/Progam Files/DS-5 v5.25.0/sw/gcc/bin

We need to use this C compiler to create executables for the ARM dual core

(2) Make sure that the Cygwin prompt can find this compiler.
Add the following line to .bashrc of your Cygwin installation

export PATH=$PATH:/cygdrive/c/Program\ Files/DS-5\ v5.25.0/sw/gcc/bin

(3) Prepare a linux disk image for your DE1SoC.

You will need an SDcard of 8G or more (this card is not included
in the kit so unfortunately you will have to provide one yourself. Sorry).

Download the 'linux console' Micro SD Card Image. You can get it from
Terasic but there is a backup copy on Canvas under Files - data - DE1_SoC_SD.zip

This is a very basic command-line linux install. We won't need any complicated
features such as GUI.

Extract the disk image from the zip and write it onto the SD card
using an image writing utility. For example, Win32DiskImageWriter
works fine.  Find an unused SD card that you are not using for
anything else; the disk image writer destroys the SD Card data,
including any partitions.

After the image is written, insert the SD card into the DE1SoC board.
Connect a UART USB Cable and an Ethernet Cable.

(4) Log in to the DE1SoC board over UART USB.
Use MobaXterm. You should be able to log in as root with no password.

There are several mechanism to configure the networking, and we will
discuss this during a coming lecture. For now, I am assuming that you
are able to pluf the board into a router. Then, let's say that your
network is 192.168.10.x, and you give your board the IP 192.168.10.20,
you would add the following data to /etc/network/interfaces

#--------------------------
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)
# The loopback interface
auto lo
iface lo inet loopback
iface atml0 inet dhcp
# Wired or wireless interfaces
auto eth0
iface eth0 inet static
  address 192.168.10.20
  netmask 255.255.255.0
  gateway 192.168.10.1
#--------------------------

(5) Once networking is set up, you can ssh into the board.

Uncomment the line 'PermitRootLogin yes' in the file /etc/ssh/sshd_config
I also disable the root password by replacing it with an empty passwd

When an SSH link into the board is available, you can copy executables
compiled on your laptop onto the board.

(6) Hello World Example

Go into helloworld
Type make
Copy hello to the board

Once the file is on the board SD card, enable the executable flag
chmod +x hello

Finally, you can run the program
./hello

The other examples work in the same way

