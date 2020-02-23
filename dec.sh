KEY="<KEY>"
ENCODING="-base<encode>"
BLOCK_ENC_HINT="<hint>"

for cipher in `openssl enc -ciphers | grep ${BLOCK_ENC_HINT}`;
do
        openssl enc -d ${ENCODING} ${cipher} -k ${KEY} -in enc.out ;
        echo $?
        if [[ $? ]]; then
                echo "-------------------------------------"
                echo $cipher;
                echo "-------------------------------------"
        fi;
done

