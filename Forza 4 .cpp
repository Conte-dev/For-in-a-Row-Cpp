#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int righe=6, colonne=7;
const char vuoto=' ', giocatore1='X', giocatore2='O';

int casuale(int min,int max) {
	return min+rand()%(max-min+1);
}

void inizializza(char g[righe][colonne]) {
	for(int i=0; i<righe; i++)
		for(int j=0; j<colonne; j++)
			g[i][j]=vuoto;
}
void stampa(char g[righe][colonne]){
    cout<<"\n  ";
    for (int j=0; j<colonne; j++) cout<<j+1<<" ";
    cout<<"\n";
    for (int i=0; i<righe; i++) {
        cout<<"  ";
        for (int j=0; j<colonne; j++) {
            cout<<g[i][j];
            if (j<colonne-1) cout<<"|";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
int pedina(char g[righe][colonne],int col,char giocatore){
	if(col<0||col>=colonne){
		cout<<"\n-----------------------\n";
		cout<<"| Colonna non valida! |\n";
		cout<<"-----------------------\n";
		return 0;
	}
	for(int i=righe-1; i>=0; i--){
		if(g[i][col]==vuoto) {
			g[i][col]=giocatore;
			return 1;
		}
	}
	cout<<"\n------------------\n";
	cout<<"| Colonna piena! |\n";
	cout<<"------------------\n";
	return 0;
}

int vittoria(char g[righe][colonne],char giocatore){
	for(int i=0; i<righe; i++)
		for(int j=0; j<=colonne-4; j++)
			if(g[i][j]==giocatore&&g[i][j+1]==giocatore&&g[i][j+2]==giocatore&&g[i][j+3]==giocatore)
				return 1;
	for(int i=0; i<=righe-4; i++)
		for(int j=0; j<colonne; j++)
			if(g[i][j]==giocatore&&g[i+1][j]==giocatore&&g[i+2][j]==giocatore&&g[i+3][j]==giocatore)
				return 1;
	for(int i=0; i<=righe-4; i++)
		for(int j=0; j<=colonne-4; j++)
			if(g[i][j]==giocatore&&g[i+1][j+1]==giocatore&&g[i+2][j+2]==giocatore&&g[i+3][j+3]==giocatore)
				return 1;
	for(int i=3; i<righe; i++)
		for(int j=0; j<=colonne-4; j++)
			if(g[i][j]==giocatore&&g[i-1][j+1]==giocatore&&g[i-2][j+2]==giocatore&&g[i-3][j+3]==giocatore)
				return 1;
	return 0;
}

int piena(char g[righe][colonne]) {
	for(int j=0; j<colonne; j++)
		if(g[0][j]==vuoto) return 0;
	return 1;
}

int pc(char g[righe][colonne]){
	srand(time(NULL));
	for(int j=0; j<colonne; j++){
		for(int i=righe-1; i>=0; i--){
			if(g[i][j]==vuoto) {
				g[i][j]=giocatore2;
				if(vittoria(g,giocatore2)){
					g[i][j]=vuoto;
					return j;
				}
				g[i][j]=vuoto;
				break;
			}
		}
	}
	for(int j=0; j<colonne; j++){
		for(int i=righe-1; i>=0; i--){
			if(g[i][j]==vuoto) {
				g[i][j]=giocatore1;
				if(vittoria(g,giocatore1)){
					g[i][j]=vuoto;
					return j;
				}
				g[i][j]=vuoto;
				break;
			}
		}
	}
	int centro=colonne/2;
	for(int i=righe-1; i>=0; i--)
		if(g[i][centro]==vuoto) return centro;

	int col;
	do {
		col=casuale(0,colonne-1);
	}
	while(g[0][col]!=vuoto);
	return col;
}

int main() {
	char g[righe][colonne], giocatore=giocatore1;
	int fine=0, col;

	cout<<"\n-----------------------------------------\n";
	cout<<"|                                       |\n";
	cout<<"|               FORZA 4                 |\n";
	cout<<"|    Sfida il computer e allinea 4      |\n";
	cout<<"|     pedine per vincere la partita!    |\n";
	cout<<"|                                       |\n";
	cout<<"-----------------------------------------\n";

	inizializza(g);

	while(fine==0) {
		stampa(g);
		if(giocatore==giocatore1) {
			cout<<"--------------------------\n";
			cout<<"| Turno X (1-7, 0=esci) |\n";
			cout<<"--------------------------\n";
			cout<<"Scegli colonna: ";
			cin>>col;
			if(col==0) {
				fine=1;
				continue;
			}
			col--;
			if(pedina(g,col,giocatore)==0) 
			continue;
		}else{
			cout<<"----------------\n";
			cout<<"| Turno di O... |\n";
			cout<<"----------------\n";
			col=pc(g);
			pedina(g,col,giocatore);
			cout<<"\n---------------------------\n";
			cout<<"| Computer: colonna "<<col+1<<"      |\n";
			cout<<"---------------------------\n";
		}

		if(vittoria(g,giocatore)==1){
			stampa(g);
			if(giocatore==giocatore1){
				cout<<"\n-----------------------------------------\n";
				cout<<"|                                       |\n";
				cout<<"|     COMPLIMENTI! HAI VINTO!           |\n";
				cout<<"|      SEI UN CAMPIONE!!!               |\n";
				cout<<"|                                       |\n";
				cout<<"-----------------------------------------\n";
			} else {
				cout<<"\n-----------------------------------------\n";
				cout<<"|                                       |\n";
				cout<<"|          HAI PERSO!                   |\n";
				cout<<"|   SARAI PIU' FORTUNATO                |\n";
				cout<<"|     LA PROSSIMA VOLTA!                |\n";
				cout<<"|                                       |\n";
				cout<<"-----------------------------------------\n";
			}
			cout<<"\n----------------------------\n";
			cout<<"| 1=Rigioca    0=Esci      |\n";
			cout<<"----------------------------\n";
			cout<<"Scelta: ";
			char scelta;
			cin>>scelta;
			if(scelta=='0') fine=1;
			else {
				inizializza(g);
				giocatore=giocatore1;
			}
			continue;
		}

		if(piena(g)==1){
			stampa(g);
			cout<<"\n-----------------------------------------\n";
			cout<<"|                                       |\n";
			cout<<"|         PARTITA PARI!                 |\n";
			cout<<"|      BELLA SFIDA COMUNQUE!            |\n";
			cout<<"|                                       |\n";
			cout<<"-----------------------------------------\n";
			cout<<"\n----------------------------\n";
			cout<<"| 1=Rigioca    0=Esci      |\n";
			cout<<"----------------------------\n";
			cout<<"Scelta: ";
			char scelta;
			cin>>scelta;
			if(scelta=='0') fine=1;
			else {
				inizializza(g);
				giocatore=giocatore1;
			}
			continue;
		}
        if (giocatore == giocatore1){
            giocatore = giocatore2;
        } else {
            giocatore = giocatore1;
        }
	}

	cout<<"\n--------------------------\n";
	cout<<"|                        |\n";
	cout<<"|       CIAO!!!          |\n";
	cout<<"|    ALLA PROSSIMA       |\n";
	cout<<"|                        |\n";
	cout<<"--------------------------\n";
	return 0;
}

