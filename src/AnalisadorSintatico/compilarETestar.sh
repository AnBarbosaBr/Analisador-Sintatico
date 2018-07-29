gcc recursivaPraValer.c -o sint.exe;

cat ./sol/teste1.sol | ./sint.exe >> r1.txt 2> e1.txt ; 
cat ./sol/teste2.sol | ./sint.exe >> r2.txt 2> e2.txt ; 
cat ./sol/teste3.sol | ./sint.exe >> r3.txt 2> e3.txt ; 
cat ./sol/teste4.sol | ./sint.exe >> r4.txt 2> e4.txt ; 
cat ./sol/teste5.sol | ./sint.exe >> r5.txt 2> e5.txt ; 
cat ./sol/teste6.sol | ./sint.exe >> r6.txt 2> e6.txt ;

rm ./sint.exe;