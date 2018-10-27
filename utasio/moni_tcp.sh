#!/bin/bash
#ScriptName: tcp_client

function StartTcpClient()
{
    echo start tcp_client
    /usr/local/bin/tcp_client 132.232.95.19 8800 &
}

echo "tcp_client is monitor !"
while ((1)) ; do
  count=$(ps -aux | grep /tcp_client | grep -v grep | grep screen -v | grep SCREEN -v | wc -l)
  #echo "$count"
  if [ $count -eq 0 ]; then
#echo "count==0, restart ucenter"
    StartTcpClient;
  else
#    echo  "start is runinng " 
    vara=10
  fi
  sleep 10
done

