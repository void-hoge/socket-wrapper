all: receiver sender

sender: ../../socket_wrapper.hpp test_cin_sender.cpp
	c++ test_cin_sender.cpp -o cin_sender

receiver: ../../socket_wrapper.hpp test_cin_receiver.cpp
	c++ test_cin_receiver.cpp -o cin_receiver

clean:
	rm cin_sender cin_receiver
