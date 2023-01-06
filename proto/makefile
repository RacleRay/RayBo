.PHONY: clean

all: *.proto
	protoc --cpp_out=./ *.proto
	g++ -c -o ./bin/user_pb.o user_info_base.pb.cc
	g++ -c -o ./bin/rela_pb.o relation_info_base.pb.cc
	g++ -c -o ./bin/message_pb.o message_info_base.pb.cc
	g++ -c -o ./bin/photo_pb.o photo_info_base.pb.cc
	g++ -c -o ./bin/cmd_def.o message_define.pb.cc
clean:
	rm *.pb.h *.pb.cc ./bin/*.o
