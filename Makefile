all: ./a.out

compRun:
	g++ -std=c++17 *.cpp User/*.cpp Database/Database.cpp Admin/Admin.cpp Buyer/Buyer.cpp Seller/Seller.cpp Inventory/*.cpp ECommerce/*.cpp -o r.out

compTest:
	g++ -std=c++17 *.cpp User/*.cpp Database/Database.cpp Admin/Admin.cpp Buyer/Buyer.cpp Seller/Seller.cpp Inventory/*.cpp ECommerce/*.cpp -o a.out

test: clean compTest; ./a.out

run: clean compRun; ./r.out

clean:
	rm -f *.out
