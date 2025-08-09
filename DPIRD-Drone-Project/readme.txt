Step 1:

-- Backup the nv-l4t-usb-device-mode.sh to nv-l4t-usb-device-mode.bak

cd /opt/nvidia/l4t-usb-device-mode/
mv nv-l4t-usb-device-mode.sh nv-l4t-usb-device-mode.bak


Step 2: 

-- Replace the nv-l4t-usb-device-mode.sh to /opt/nvidia/l4t-usb-device-mode/

cp nv-l4t-usb-device-mode.sh /opt/nvidia/l4t-usb-device-mode/nv-l4t-usb-device-mode.sh 


Step 3: 

-- Compile the startup_bulk program and must in '/home/your_computer/Desktop/startup_bulk'

sudo apt-get install libaio-dev

cd startup_bulk

make

Step 4: 

-- Reboot your computer

Step 5: 

-- Check ep0/ep1/ep2 is not generated

ls -l /dev/usb-ffs/bulk/


