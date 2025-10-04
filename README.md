#To compile (GTK 4):
gcc App.c -o app $(pkg-config --cflags --libs gtk4)
step2:
./app to run
done
Tested with MSYS2 (ucrt64)
