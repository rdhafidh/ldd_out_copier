# ldd_out_copier
===========

 A simple linux shared library copier, based on Linux ldd utility output.
 
 Usage :
 ```
 $ ldd /home/user/cpp/qt_custom_root/lib/libQt5Sql.so.5
	libQt5Sql.so.5 => /home/user/cpp/qt_custom_root/lib/libQt5Sql.so.5 (0x00007f5b86139000)
        libQt5PrintSupport.so.5 => /home/user/cpp/qt_custom_root/lib/libQt5PrintSupport.so.5 (0x00007f5b85ed2000)
        libQt5Widgets.so.5 => /home/user/cpp/qt_custom_root/lib/libQt5Widgets.so.5 (0x00007f5b856b7000)
        libQt5Gui.so.5 => /home/user/cpp/qt_custom_root/lib/libQt5Gui.so.5 (0x00007f5b8503e000)
        libQt5Core.so.5 => /home/user/cpp/qt_custom_root/lib/libQt5Core.so.5 (0x00007f5b8490a000)
        libc++.so.1 => /home/user/cpp/qt_custom_root/lib/libc++.so.1 (0x00007f5b84619000)
        libc++abi.so.1 => /home/user/cpp/qt_custom_root/lib/libc++abi.so.1 (0x00007f5b843d0000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f5b840b3000)
        libgcc_s.so.1 => /home/user/cpp/qt_custom_root/lib/libgcc_s.so.1 (0x00007f5b83e9a000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f5b83ad1000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f5b838b4000)
        libicui18n.so.56 => /home/user/cpp/qt_custom_root/lib/libicui18n.so.56 (0x00007f5b8334d000)
        libicuuc.so.56 => /home/user/cpp/qt_custom_root/lib/libicuuc.so.56 (0x00007f5b82f61000)
        libicudata.so.56 => /home/user/cpp/qt_custom_root/lib/libicudata.so.56 (0x00007f5b8157b000)
  
  #now come into action 
  $ ldd /home/user/cpp/qt_custom_root/lib/libQt5Sql.so.5 > lddout
  $ ldd_out_copier lddout /opt/destination/to_chroot_your_linux_shared_lib_app
  # you can now check /opt/destination/to_chroot_your_linux_shared_lib_app should contains 
  # libQt5PrintSupport.so.5 until libicudata.so.56 based on what your lddout input arg.
  
 ```
 
 Some thirdparties license include :
 
 [Qt5](https://www.qt.io/) (LGPL V3) (only qtcore module)

 [cpp-peglib](https://github.com/yhirose/cpp-peglib) (MIT)
 
 **This application license is under MIT license**