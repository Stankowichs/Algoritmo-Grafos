floyd=./floydwarshall.bin

echo "Testando algoritmo de Floyd-Warshall"
for i in {1..20}
do
    echo -e "\e[33mInstância entrada$i.dat\e[0m"
    
    $floyd -f entradas/entrada$i.dat > temp

    diff -w temp saidas/saida$i.dat > /dev/null
    if [ $? -eq 0 ]; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mErro\e[0m"
    fi

    rm temp
done
