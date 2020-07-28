For later use

--------------
While the dtb-builder also from Robert C. Neslon git. 
https://github.com/RobertCNelson/dtb-rebuilder
As a BB-W1-P09.12-00A0.dts file is from Robert C. Neslon git. 
https://github.com/beagleboard/bb.org-overlays/blob/master/src/arm/BB-W1-P9.12-00A0.dts
Boot time read file discription- folder to read the .dtbo file in the follwing folder.
/lib/fireware/name.dtbo here i putted my file at this loaction 
don't know why but its /boot/dtbs/name.dtbo 
then The dtb_overlay path for the dtbo file in the uEnv.txt file 
nano /boot/uEnv.txt
by adding the file loaction at the custome overlay
dtb_overlay=/lib/firware/name.dtbo
reboot.  


will also uploaded the uEnu.txt file later reference or any future help.
---------------------------------------------------------------------------------------
