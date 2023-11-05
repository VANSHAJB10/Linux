# 1. bash program to print 'line 10' only when starting from line 1

n=1;
while read line ;
do
    if [ $n -eq 10 ]; then      # the space before $n and after 10 is necessary
        echo "$line"
    fi
    n=$((n+1));
done < file.txt
