Player position X : 9.500000 Y : 9.500000
adresse window->mlx_ptr = 0x560efd706620
debut calculate map
pixel = 10 x 10 game->x_len 19, game-> y_len = 19
zsh: segmentation fault (core dumped)  ./Cub3D ./maps/loulou.cub
c2r10p3% code .
c2r10p3% ./Cub3D ./maps/loulou.cub
 20 0
11111111111111111111
10000000000000000001
10111111111111111001
10100000000000001001
10101111111111101001
10101000000000101001
10101011111110101001
10101010000010101001
10101010111010101001
101S1010101001010101
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10100000000000000001
10111111111111111001
10000000000000000001
11111111111111111111

11111111111111111111
10000000000000000001
10111111111111111001
10100000000000001001
10101111111111101001
10101000000000101001
10101011111110101001
10101010000010101001
10101010111010101001
101S1010101001010101
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10100000000000000001
10111111111111111001
10000000000000000001
11111111111111111111

Map X : 19
Map Y : 19
Player position X : 3.500000 Y : 9.500000
adresse window->mlx_ptr = 0x5572e01ac620
debut calculate map
pixel = 10 x 10 game->x_len 19, game-> y_len = 19
c2r10p3% valgrind -s ./Cub3D ./maps/loulou.cub
==23866== Memcheck, a memory error detector
==23866== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==23866== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==23866== Command: ./Cub3D ./maps/loulou.cub
==23866== 
 20 0
11111111111111111111
10000000000000000001
10111111111111111001
10100000000000001001
10101111111111101001
10101000000000101001
10101011111110101001
10101010000010101001
10101010111010101001
101010101S1001010101
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10100000000000000001
10111111111111111001
10000000000000000001
11111111111111111111

11111111111111111111
10000000000000000001
10111111111111111001
10100000000000001001
10101111111111101001
10101000000000101001
10101011111110101001
10101010000010101001
10101010111010101001
101010101S1001010101
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10101010101010101001
10100000000000000001
10111111111111111001
10000000000000000001
11111111111111111111

Map X : 19
Map Y : 19
Player position X : 9.500000 Y : 9.500000
adresse window->mlx_ptr = 0x4d42fb0
debut calculate map
pixel = 10 x 10 game->x_len 19, game-> y_len = 19
==23866== Invalid write of size 1
==23866==    at 0x1113E7: img_pix_put (mlx.c:29)
==23866==    by 0x113A61: draw_column_pixels (dda.c:215)
==23866==    by 0x114025: calc_pix_to_draw (dda.c:302)
==23866==    by 0x1138CE: dda (dda.c:182)
==23866==    by 0x111412: draw_image (mlx.c:36)
==23866==    by 0x114760: control_key (key_hook.c:135)
==23866==    by 0x115E8C: mlx_loop (in /home/nbaldes/c42/cub3d/Cub3D)
==23866==    by 0x111F03: create_window (mlx.c:237)
==23866==    by 0x1101DF: main (main.c:95)
==23866==  Address 0x53c3000 is not stack'd, malloc'd or (recently) free'd
==23866== 
==23866== 
==23866== Process terminating with default action of signal 11 (SIGSEGV)
==23866==  Access not within mapped region at address 0x53C3000
==23866==    at 0x1113E7: img_pix_put (mlx.c:29)
==23866==    by 0x113A61: draw_column_pixels (dda.c:215)
==23866==    by 0x114025: calc_pix_to_draw (dda.c:302)
==23866==    by 0x1138CE: dda (dda.c:182)
==23866==    by 0x111412: draw_image (mlx.c:36)
==23866==    by 0x114760: control_key (key_hook.c:135)
==23866==    by 0x115E8C: mlx_loop (in /home/nbaldes/c42/cub3d/Cub3D)
==23866==    by 0x111F03: create_window (mlx.c:237)
==23866==    by 0x1101DF: main (main.c:95)
==23866==  If you believe this happened as a result of a stack
==23866==  overflow in your program's main thread (unlikely but
==23866==  possible), you can try to increase the size of the
==23866==  main thread stack using the --main-stacksize= flag.
==23866==  The main thread stack size used in this run was 8388608.
==23866== 
==23866== HEAP SUMMARY:
==23866==     in use at exit: 117,050 bytes in 150 blocks
==23866==   total heap usage: 2,058 allocs, 1,908 frees, 1,227,151 bytes allocated
==23866== 
==23866== LEAK SUMMARY:
==23866==    definitely lost: 0 bytes in 0 blocks
==23866==    indirectly lost: 0 bytes in 0 blocks
==23866==      possibly lost: 0 bytes in 0 blocks
==23866==    still reachable: 117,050 bytes in 150 blocks
==23866==         suppressed: 0 bytes in 0 blocks
==23866== Rerun with --leak-check=full to see details of leaked memory
==23866== 
==23866== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
==23866== 
==23866== 1 errors in context 1 of 1:
==23866== Invalid write of size 1
==23866==    at 0x1113E7: img_pix_put (mlx.c:29)
==23866==    by 0x113A61: draw_column_pixels (dda.c:215)
==23866==    by 0x114025: calc_pix_to_draw (dda.c:302)
==23866==    by 0x1138CE: dda (dda.c:182)
==23866==    by 0x111412: draw_image (mlx.c:36)
==23866==    by 0x114760: control_key (key_hook.c:135)
==23866==    by 0x115E8C: mlx_loop (in /home/nbaldes/c42/cub3d/Cub3D)
==23866==    by 0x111F03: create_window (mlx.c:237)
==23866==    by 0x1101DF: main (main.c:95)
==23866==  Address 0x53c3000 is not stack'd, malloc'd or (recently) free'd
==23866== 
--23866-- 
--23866-- used_suppression:      1 X on SUSE11 writev uninit padding /usr/libexec/valgrind/default.supp:377
==23866== 
==23866== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
zsh: segmentation fault (core dumped)  valgrind -s ./Cub3D ./maps/loulou.cub
c2r10p3% 


-------------------------------------------------------------

NO	./textures/NO.xpm  
     
SO ./textures/SO.xpm

WE ./textures/WE.xpm

EA ./textures/EA.xpm    
C 225,,255

F 0,100,0





11111111111111111111
1000000000000E000001
111111011111111111111
1010101 101111
1101111111
1111

c2r10p3% ./Cub3D ./test.cub
zsh: segmentation fault (core dumped)  ./Cub3D ./test.cub


----------------------------------------------------------------

NO	./textures/NO.xpm  
     
SO ./textures/SO.xpm

EA ./textures/EA.xpm    
WE ./textures/WE.xpm

C 225,1,255

F 0,100,1


        111111111111
        11111110111
        1101
11111111111111111111
1000000000000E000001
111111011111111111111
1010101 101111
1101111111
1111

-----------------------------------------------------------------

NO	./textures/NO.xpm  
     
SO ./textures/SO.xpm

EA ./textures/EA.xpm    
WE ./textures/WE.xpm

C 225,1,255

F 0,100,1


 1
1N1
 1