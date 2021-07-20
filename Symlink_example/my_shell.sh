echo "[+] Giving executable permission to the files\n"

sudo chmod +x my_file

sudo chmod +x evil_file

sudo chmod +x overwrite

printf "[+] Creating a hard link to my_file named \"my_link\"\n"

ln my_file my_link

printf "[+] Contents of my_file before overwriting it: \n\n"
printf "########## START OF MY_FILE ##########\n"

./my_link

printf "########## END OF MY_FILE ##########\n\n"


printf "[+] Overwriting my_file using overwrite.exe\n"

./overwrite

printf "[+] Contents of my_file after overwriting it: \n\n"
printf "########## START OF MY_FILE ##########\n"

./my_link

printf "########## END OF MY_FILE ##########\n\n"

printf "[+] Reverting my_file to original form\n"

gcc my_file.c -o my_file

printf "[+] Deleting hard link named \"my_link\"\n"

sudo rm my_link
