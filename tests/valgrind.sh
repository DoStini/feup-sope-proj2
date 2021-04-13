
echo "TESTING CLIENT"

cd client

valgrind -q --gen-suppressions=yes ./c

cd ..

echo "FINISHED TESTING CLIENT"
echo ""
echo ""
