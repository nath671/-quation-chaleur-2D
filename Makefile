
EDP_2D.txt: main.exe
				./main.exe

main.exe: main.cpp EquationChaleur2D.o Air.o Piece.o Radiateur.o Fenetre.o Mur.o Domaine2D.o Domaine2D.h EquationChaleur2D.h Piece.h Air.h Mur.h Fenetre.h Radiateur.h
				g++ EquationChaleur2D.o Air.o Piece.o Radiateur.o Fenetre.o Mur.o Domaine2D.o main.cpp -o main.exe

EquationChaleur1D.o: EquationChaleur2D.cpp EquationChaleur2D.h Domaine2D.h Piece.h Air.h
				g++ -c EquationChaleur2D.cpp

Air.o: Air.h Air.cpp Domaine2D.h Mur.h Radiateur.h Fenetre.h
				g++ -c Air.cpp

Piece.o: Piece.cpp Piece.h Domaine2D.h Mur.h Radiateur.h Fenetre.h
				g++ -c Piece.cpp

Radiateur.o: Radiateur.h Radiateur.cpp
				g++ -c Radiateur.cpp

Fenetre.o: Fenetre.h Fenetre.cpp
				g++ -c Fenetre.cpp

Mur.o: Mur.h Mur.cpp
				g++ -c Mur.cpp

Domaine2D.o: Domaine2D.h Domaine2D.cpp
				g++ -c Domaine2D.cpp