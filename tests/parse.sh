
RES_CLIENT=$(grep 'GOTRS' client_log.txt | tr -d [:blank:] | awk -F\; '{print $6}' | sort -n)
RES_EXEC=$(grep 'TSKEX' server_log.txt | tr -d [:blank:] | awk -F\; '{print $6}' | sort -n)
ID_CLIENT=$(grep 'IWANT' client_log.txt | tr -d [:blank:] | awk -F\; '{print $2}' | sort -n)
ID_EXEC_2LATE=$(grep 'TSKEX\|2LATE' server_log.txt | tr -d [:blank:] | awk -F\; '{print $2}' | sort -n)

echo $RES_CLIENT | sed 's/\s\+/\n/g' > res_client.txt
echo $RES_EXEC | sed 's/\s\+/\n/g' > res_exec.txt
echo $ID_CLIENT | sed 's/\s\+/\n/g' > id_client.txt
echo $ID_EXEC_2LATE | sed 's/\s\+/\n/g' > id_exec_2late.txt
