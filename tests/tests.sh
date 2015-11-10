echo "This tester assumes no other commands have been run after make install"

if [[ $(showqueue) ]] ; then
  echo "FAIL\tshowqueue should return nothing on first execution"
else
  echo "PASS"
fi

if [[ $(addqueue non-existent-file) -ne "non-existent-file: X file cannot be opened" ]] ; then
  echo "FAIL\tshowqueue should retun nothing on first execution"
else
  echo "PASS"
fi

if [[ $(showqueue) ]] ; then
  echo "FAIL\tshowqueue should still be empty"
else
  echo "PASS"
fi

if [[ $(addqueue spooler.h) -ne "spooler.h: Y " ]] ; then
  echo "FAIL\taddqueue fails"
else
  echo "PASS"
fi

if [[ ! $(showqueue) ]] ; then
	echo "FAIL\tshowqueue should not be empty now"
else
	echo "PASS"
fi

if [[ $(rmqueue random_string) -ne "random_string: X file does not exist or does not belong to user" ]] ; then
  echo "FAIL\trmqueue should not delete a non-existent-file"
else
  echo "PASS"
fi

if [[ $(rmqueue $UID-2) -ne "$UID-2: Y" ]] ; then
  echo "FAIL\trmqueue fails"
else
  echo "PASS"
fi