case "$1" in
	install)
		sudo cp -v -n CircularBuffer.h /usr/local/include/CircularBuffer
		;;
	remove)
		sudo rm -v /usr/local/include/CircularBuffer
		;;
	reinstall)
		sudo cp -v CircularBuffer.h /usr/local/include/CircularBuffer
		;;
	*)
		echo $"Usage: $0 {install|remove|reinstall}"
		exit 1
esac
