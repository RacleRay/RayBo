all:prot conf sock db user rela mess bus photo dbt svr cln

prot:
	cd ./proto && make
conf:
	g++ -c -o conf.o Config.cpp -D_D
sock:
	g++ -c -o sock.o Socket.cpp -D_D
db:
	g++ -c -o db.o Database.cpp -D_D
user:
	g++ -c -o userI.o UserInfo.cpp -D_D
	g++ -c -o userM.o UserManager.cpp -D_D
rela:
	g++ -c -o relaI.o RelationInfo.cpp -D_D
	g++ -c -o relaM.o RelationManager.cpp -D_D
mess:
	g++ -c -o mess.o MessageManager.cpp -D_D
bus:
	g++ -c -o bus.o BusManager.cpp -D_D
photo:
	g++ -c -o photo.o PhotoManager.cpp -D_D
dbt:
	g++ -o userserver proto/bin/*.o db.o userI.o userM.o bus.o user_server.cpp -lprotobuf -lmysqlclient -D_D
svr:
	g++ -o server proto/bin/*.o *.o main_server.cpp -lprotobuf -lmysqlclient -D_D
cln:
	g++ -o client proto/bin/*.o conf.o sock.o client_test.cpp -lprotobuf -D_D
clean:
	rm -f ./proto/bin/*.o ./proto/*.pb.cc ./proto/*.pb.h *.o userserver server client