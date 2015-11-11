echo -e "This tester assumes no other commands have been run after make install"

if [[ $(showqueue) ]] ; then
  echo -e "FAIL\tshowqueue should return nothing on first execution"
else
  echo -e "PASS"
fi

if [[ $(addqueue non-existent-file) != "non-existent-file: X file cannot be opened" ]] ; then
  echo -e "FAIL\taddqueue should not add non-existent files"
else
  echo -e "PASS"
fi

if [[ $(showqueue) ]] ; then
  echo -e "FAIL\tshowqueue should still be empty"
else
  echo -e "PASS"
fi

if [[ $(addqueue spooler.h) != "spooler.h: Y " ]] ; then
  echo -e "FAIL\taddqueue fails"
else
  echo -e "PASS"
fi

if [[ ! $(showqueue) ]] ; then
	echo -e "FAIL\tshowqueue should not be empty now"
else
	echo -e "PASS"
fi

if [[ $(rmqueue random_string) != "random_string: X file does not exist or does not belong to user" ]] ; then
  echo -e "FAIL\trmqueue should not delete a non-existent-file"
else
  echo -e "PASS"
fi

if [[ $(rmqueue 1) != "1: Y " ]] ; then
  echo -e "FAIL\trmqueue fails"
else
  echo -e "PASS"
fi
