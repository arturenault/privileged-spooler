echo -e "This tester assumes no other commands have been run after make install"

if [[ $(showqueue) ]] ; then
  echo -e "FAIL\tshowqueue should return nothing on first execution"
else
  echo -e "PASS"
fi

if [[ $(addqueue non-existent-file) != "non-existent-file: X file cannot be opened" ]] ; then
  echo -e "FAIL\tshowqueue should retun nothing on first execution"
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

if [[ $(rmqueue 2) != "2: Y" ]] ; then
  echo -e "FAIL\trmqueue fails"
else
  echo -e "PASS"
fi

if [[ $(addqueue spooler.h spooler.cc Makefile) != $"spooler.h: Y\nspooler.cc: Y\nMakefile: Y" ]] ; then
  echo -e "FAIL\taddqueue fails on multiple files"
else
  echo -e "PASS"
fi

if [[ $(rmqueue 3 4 5) != $"3: Y\n4: Y\n5: Y" ]] ; then
  echo -e "FAIL\rmqueue fails on multiple files"
else
  echo -e "PASS"
fi
