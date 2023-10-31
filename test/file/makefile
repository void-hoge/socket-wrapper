all: sender receiver

sender: ../../socket_wrapper.hpp test_file_sender.cpp
	c++ test_file_sender.cpp -o file_sender

receiver: ../../socket_wrapper.hpp test_file_receiver.cpp
	c++ test_file_receiver.cpp -o file_receiver

clean:
	rm file_sender file_receiver
