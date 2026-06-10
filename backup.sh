#! /bin/bash 




 WORKING_DIR=$( pwd )

 BACKUP_DIR=${WORKING_DIR}/BACKUP
 

FILE_LIST=$( ls ${WORKING_DIR} ) 




for file  in ${FILE_LIST} 

	do 
		if  [   -f  ${WORKING_DIR}/"$file" ]  && [  -d ${BACKUP_DIR} ]   
			then 
				echo "backing up ${file}..."	
				cp $file ${BACKUP_DIR}/${file}.$( date +%Y%m%d-%H%M ) 		;
				echo "${file} backed up" 
	fi
done 
