cd build
if [ -e "PO_GO" ]; then
    ./PO_GO "${@:1}"
elif [ -e "PO_GO.exe" ]; then
    ./PO_GO.exe "${@:1}"
fi