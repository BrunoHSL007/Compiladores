//Licença
//Em vez de adicionar strings com o nome do token na lista, adicionar o valor correspondente a coluna da tabela para facilitar a busca
#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <iterator>
using namespace std;
string reservadas[19]={"void", "int", "char", "bool", "float", "se", "senao", "escolha", "caso", "quebra", "padrao", "para", "enquanto", "comeca", "termina", "leia", "escreva","verdadeiro","falso"};
list <string> listaTokensSTR;
list <int> listaTokens; 
int TabelaLR[268][32];
int TabelaTransicao[268][26];
int tamanhoProducao[2][47]={{0,0,1,1,1,2,3,3,4,4,4,4,4,4,4,4,4,5,5,6,7,8,8,9,10,11,11,12,14,14,13,13,15,16,17,18,19,20,20,21,22,22,23,23,24,24,25},{1,8,1,1,1,3,1,0,1,1,1,1,1,1,4,1,4,1,1,3,3,1,1,5,6,5,0,8,1,1,4,0,13,3,3,3,2,2,0,2,3,3,3,0,1,0,7}};
list <int> linhaerro;

void AnalisadorLexico(FILE *input){
	int ContLinha=1; //contador da linha onde está o erro
	if (input == NULL)  // Se houve erro na abertura
	{
		printf("Problemas na abertura do arquivo\n");
		return;
	}
	while (!feof(input))
	{
		// Lê caracter por caracter do arquivo
		int contador=0;
		char lido = getc(input);
		contador++;
		//cout << " valor lido["<< contador <<"] = " << lido<<endl;
		if(lido=='\n'){
			ContLinha++;
		}
		else if(lido=='&')//Operadores Lógicos
		{
			lido = getc(input);
			if(lido=='&'){
				listaTokensSTR.push_back("OPREL AND");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
				
			}
			else{
				cout << "Erro na Linha " << ContLinha << " => Caractere '&' esperado '&&'"<<endl<<endl;
				fseek(input, -1, 1); //Volta um caractere

			}
		}
		else if(lido=='|')
		{
			lido = getc(input);
			if(lido=='|'){
				listaTokensSTR.push_back("OPREL OR");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
			}
			else{
				cout << "Erro na Linha " << ContLinha << " => Caractere '|' esperado '||'"<<endl<<endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='=')
		{
			lido = getc(input);
			if(lido=='='){
				listaTokensSTR.push_back("OPREL IGUALDADE");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
			}
			else{
				listaTokensSTR.push_back("ATRIBUICAO");
				listaTokens.push_back(24);
				linhaerro.push_back(ContLinha);
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='!')
		{
			lido = getc(input);
			if(lido=='='){
				listaTokensSTR.push_back("OPREL DIFERENTE");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
			}
			else{
				listaTokensSTR.push_back("OPLOG NOT");
				listaTokens.push_back(26);
				linhaerro.push_back(ContLinha);
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='<')
		{
			lido = getc(input);
			if(lido=='='){
				listaTokensSTR.push_back("OPREL MENORIGUAL");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
			}
			else{
				listaTokensSTR.push_back("OPREL MENOR");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='>')
		{
			lido = getc(input);
			if(lido=='='){
				listaTokensSTR.push_back("OPREL MAIORIGUAL");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
			}
			else{
				listaTokensSTR.push_back("OPREL MAIOR");
				listaTokens.push_back(27);
				linhaerro.push_back(ContLinha);
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		//Controle
		else if(lido=='(')
		{
			listaTokensSTR.push_back("ABREPAR");
			listaTokens.push_back(20);
			linhaerro.push_back(ContLinha);
		}
		else if(lido==')')
		{
			listaTokensSTR.push_back("FECHAPAR");
			listaTokens.push_back(21);
			linhaerro.push_back(ContLinha);
		}
		else if(lido=='{')
		{
			listaTokensSTR.push_back("ABRECHAVE");
			listaTokens.push_back(22);
			linhaerro.push_back(ContLinha);
		}
		else if(lido=='}')
		{
			listaTokensSTR.push_back("FECHACHAVE");
			listaTokens.push_back(23);
			linhaerro.push_back(ContLinha);
		}
		else if(lido==';')
		{
			listaTokensSTR.push_back("FIMCOMANDO");
			listaTokens.push_back(28);
			linhaerro.push_back(ContLinha);
		}
		else if(lido==':')
		{
			listaTokensSTR.push_back("DOISPONTOS");
			listaTokens.push_back(29);
			linhaerro.push_back(ContLinha);
		}
		else if(lido==',')
		{
			listaTokensSTR.push_back("VIRGULA");
			listaTokens.push_back(30);
			linhaerro.push_back(ContLinha);
		}
		//Operadores Aritméticos
		else if(lido=='+')
		{
			listaTokensSTR.push_back("OPARIT SOMA");
			listaTokens.push_back(25);
			linhaerro.push_back(ContLinha);
		}
		else if(lido=='-')
		{
			listaTokensSTR.push_back("OPARIT SUBTRACAO");
			listaTokens.push_back(25);
			linhaerro.push_back(ContLinha);
		}
		else if(lido=='*')
		{
			listaTokensSTR.push_back("OPARIT MULTIPLICACAO");
			listaTokens.push_back(25);
			linhaerro.push_back(ContLinha);
		}
		else if(lido=='/')
		{
			lido = getc(input);
			if(lido=='/'){ //Ignora comentários
				while(getc(input)!='\n');
			}
			else{
				listaTokensSTR.push_back("OPARIT DIVISAO");
				listaTokens.push_back(25);
				linhaerro.push_back(ContLinha);
			}
		}
		//Identificadores
		else if(isalpha(lido)){
			fseek(input, -1, 1); //Volta um caractere
			//int tamanhoPalavra=0;
			string palavra;
			lido = getc(input);
			while((isalpha(lido))||(isdigit(lido))){
				//tamanhoPalavra++;
				palavra+=lido;
				lido = getc(input);
			}
			fseek(input, -1, 1); //Volta um caractere
			bool isReservada=false;
			for(int i=0; i<19;i++){
				if(!palavra.compare(reservadas[i])){
					//cout << "reservada " << palavra<<endl;
					isReservada=true;
					switch (i){
						case 1 : listaTokens.push_back(4);break;
						case 2 : listaTokens.push_back(6);break;
						case 3 : listaTokens.push_back(7);break;
						case 4 : listaTokens.push_back(5);break;
						case 5 : listaTokens.push_back(13);break;
						case 6 : listaTokens.push_back(14);break;
						case 7 : listaTokens.push_back(11);break;
						case 8 : listaTokens.push_back(12);break;
						case 9 : listaTokens.push_back(15);break;
						case 11 : listaTokens.push_back(16);break;
						case 12 : listaTokens.push_back(17);break;
						case 13 : listaTokens.push_back(2);break;
						case 14 : listaTokens.push_back(3);break;
						case 15 : listaTokens.push_back(18);break;
						case 16 : listaTokens.push_back(19);break;
						case 17 : listaTokens.push_back(8);break;
						case 18 : listaTokens.push_back(9);break;
					}
					linhaerro.push_back(ContLinha);
					break;
				}
			}
			string aux1;
			if(isReservada){
				for(unsigned int i=0; i<palavra.size(); i++)
				{                            // Converte cada caracter de Str
				 palavra[i] = toupper (palavra[i]);  // para maiusculas
				}
				aux1 = palavra;
			}
			else{
				aux1 = "ID";
				listaTokens.push_back(0);
				linhaerro.push_back(ContLinha);
			}
			listaTokensSTR.push_back(aux1);
			
		}
		else if(isdigit(lido)){
			fseek(input, -1, 1); //Volta um caractere
			//int tamanhoDigito=0;
			string digito;
			lido = getc(input);
			while((isdigit(lido))){
				//tamanhoDigito++;
				digito+=lido;
				lido = getc(input);
			}
			if(lido=='.'){
				digito+=lido;
				lido = getc(input);
				while((isdigit(lido))){
					//tamanhoDigito++;
					digito+=lido;
					lido = getc(input);
				}

				string aux1 = "ID";
				listaTokensSTR.push_back(aux1);
			}
			else{
				string aux1 = "ID";
				listaTokensSTR.push_back(aux1);
			}
			listaTokens.push_back(0);
			linhaerro.push_back(ContLinha);
			fseek(input, -1, 1); //Volta um caractere
		}
		else if(lido =='\"'){
			lido = getc(input);
			string literal;
			while((lido!='\"')){
				//tamanhoDigito++;
				literal+=lido;
				lido = getc(input);
				if(lido==EOF){
					cout << "Nao encontrado \" do fechamento" << endl; //Ver se tá certo com o Professor
					return;
				}
			}
			string aux1 = "LITERAL \'"+literal+"\'";
			listaTokensSTR.push_back(aux1);
			listaTokens.push_back(1);
			linhaerro.push_back(ContLinha);

		}
		else if(lido =='\''){
			lido = getc(input);
			string literal;
			while((lido!='\'')){
				//tamanhoDigito++;
				literal+=lido;
				lido = getc(input);
				if(lido==EOF){
					cout << "Nao encontrado \' do fechamento" << endl; //Ver se tá certo com o Professor
					return;
				}
			}
			string aux1 = "LITERAL \'"+literal+"\'";
			listaTokensSTR.push_back(aux1);
			listaTokens.push_back(1);
			linhaerro.push_back(ContLinha);
		}
		else if(lido!=' ' && lido!=EOF && lido!='\t'){
			cout << "Erro lexico na Linha " << ContLinha << " => Caractere '"<<lido<<"' nao esperado"<<endl<<endl;
		}

		//else if(isdigit(lido)){
		//	cout << "DIGITO" << endl;
		//}
		//else{
		//	string a;
		//	do{
		//		a=getc(input);
		//		cout << "a";
		//	}
		//	while(LetrasPermitidas.substr(a,1));
		//}
	}	
}

void AnalisadorSintatico(){
	list <string> :: iterator ite;
	list <int> :: iterator it;
	//cout << "\tLISTA DE TOKENS\n";
	//for(it = listaTokensSTR.begin(); it != listaTokensSTR.end(); ++it)
	//		cout << *it << '\n' ;
	//for(it = listaTokens.begin(); it != listaTokens.end(); ++it)
	//	cout << *it << '\n' ;
	list <int> pilha;
	pilha.push_back(0);
	//cout << "value = " << (int)pilha.back();
	bool erro=false;
	while((!listaTokens.empty())&&erro==false){
		//for(it = listaTokens.begin(); it != listaTokens.end(); ++it)
		//	cout << *it << ' ' ;
		
		list <int> :: iterator it2;
		int valor = TabelaLR[pilha.back()][listaTokens.front()];
		
		//cout << "TabelaLR["<<pilha.back()<<"]["<<listaTokens.front()<<"]"<<valor;
		
		if((valor>0)&&(valor!=9000)){//empilha
			//cout << " Empilha" << valor<<endl;
			pilha.push_back(listaTokens.front());
			listaTokens.pop_front();
			linhaerro.pop_front();
			listaTokensSTR.pop_front();
			pilha.push_back(valor);
		}
		else if(valor<0){ //reduz
			valor*=-1;
			//cout << " Reduz" << valor<<endl;
			int aux;
			int tamanho2=2*tamanhoProducao[1][valor];
			list <int> listaauxiliar;
					
			//Cuidar do caso onde as produções levam ao vazio reduzir em 1 o tamanho
			if(valor==1000){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if((pilha.back()==6)||(pilha.back()==24)){
					valor=42;
				}
				else{
					valor=44;
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();
			}
			
			if(valor == 5){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=3){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();
			}
			else if(valor == 24){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=11){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();
			}
			else if(valor == 27){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=13){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();
			}
			else if(valor == 36){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=20){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();	
			}
			else if(valor==40){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=23){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();	
			}
			else if(valor==41){
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=23){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();	
			}
			else if(valor==42){
				
				listaauxiliar.push_back(pilha.back());
				pilha.pop_back();
				if(pilha.back()!=24){
					tamanho2=2*(tamanhoProducao[1][valor]-1);
				}
				pilha.push_back(listaauxiliar.back());
				listaauxiliar.pop_back();
			}
			
			
			
			
			for(int i=0;i<(tamanho2);i++){
				pilha.pop_back();
			}
			aux=pilha.back();
			
			//cout <<"aux = "<<aux<<endl;
			
			pilha.push_back(tamanhoProducao[0][valor]);
			int aux2=pilha.back();
			
			//cout <<"aux2 = "<<aux2<<endl<<"Transicao = "<<TabelaTransicao[aux][aux2]<<endl;
			
			pilha.push_back(TabelaTransicao[aux][aux2]);
			
		}
		else if(valor==9000){
			erro=true;
			cout << "Erro sintatico linha "<<linhaerro.front()<<" => ";
			switch(listaTokens.front()){
				case 0 : cout << "ID";break; 
				case 1 : cout << "Literal";break;
				case 2 : cout << "comeca";break;
				case 3 : cout << "termina";break;
				case 4 : cout << "int";break;
				case 5 : cout << "float";break;
				case 6 : cout << "char";break;
				case 7 : cout << "bool";break;
				case 8 : cout << "verdadeiro";break;
				case 9 : cout << "falso";break;
				case 10: cout << "void";break;
				case 11: cout << "escolha";break;
				case 12: cout << "caso";break;
				case 13: cout << "se";break;
				case 14: cout << "senao";break;
				case 15: cout << "quebra";break;
				case 16: cout << "para";break;
				case 17: cout << "enquanto";break;
				case 18: cout << "leia";break;
				case 19: cout << "escreva";break;
				case 20: cout << "(";break;
				case 21: cout << ")";break;
				case 22: cout << "{";break;
				case 23: cout << "}";break;
				case 24: cout << "=";break;
				case 25: cout << "Op_aritmetico";break;
				case 26: cout << "Op_relacional";break;
				case 27: cout << "Op_logico";break;
				case 28: cout << ";";break;
				case 29: cout << ":";break;
				case 30: cout << ",";break;
			}
			cout << " nao esperado" << endl;
		}
		
		//cout << endl<<"Pilha = ";
		//for(it2 = pilha.begin(); it2 != pilha.end(); ++it2)
		//	cout << *it2 << ' ' ;
		//	cout << endl<<"String = ";
		//for(ite = listaTokensSTR.begin(); ite != listaTokensSTR.end(); ++ite)
		//	cout << *ite << ' ' ;
	}
	if(!erro){
		cout << "Compilado com sucesso"<<endl;
	}
}
void inicializaTabelas(){
	for(int i=0;i<268;i++){
		for(int j=0;j<32;j++){
			TabelaLR[i][j]=9000;
		}
	}
	for(int i=0;i<268;i++){
		for(int j=0;j<26;j++){
			TabelaTransicao[i][j]=9000;
		}
	}
	
	//Empilha é valor positivo
	//Reduz é valor negativo
	TabelaLR[0][2]=2;
	TabelaLR[1][31]=1000; //Aceita
	TabelaLR[2][20]=3;
	TabelaLR[3][21]=4;
	TabelaLR[4][22]=5;
	TabelaLR[5][0]=23;
	TabelaLR[5][4]=24;
	TabelaLR[5][5]=25;
	TabelaLR[5][6]=26;
	TabelaLR[5][7]=18;
	TabelaLR[5][11]=20;
	TabelaLR[5][13]=22;
	TabelaLR[5][16]=19;
	TabelaLR[5][17]=21;
	TabelaLR[5][18]=14;
	TabelaLR[5][19]=16;
	TabelaLR[6][3]=27;
	TabelaLR[8][15]=-8;
	TabelaLR[8][23]=-8;
	TabelaLR[9][15]=-9;
	TabelaLR[9][23]=-9;
	TabelaLR[10][15]=-10;
	TabelaLR[10][15]=-10;
	TabelaLR[10][15]=-10;
	TabelaLR[17][0]=32;//id
	TabelaLR[18][0]=34;
	TabelaLR[20][0]=36;
	TabelaLR[24][0]=-2;
	TabelaLR[25][0]=-3;
	TabelaLR[26][0]=-4;
	TabelaLR[28][0]=23;
	TabelaLR[29][0]=64;
	TabelaLR[30][0]=67;
	TabelaLR[37][0]=78;
	TabelaLR[38][0]=82;
	TabelaLR[40][0]=85;
	TabelaLR[41][0]=85;
	TabelaLR[69][0]=92;
	TabelaLR[70][0]=85;
	TabelaLR[72][0]=92;
	TabelaLR[75][0]=101;
	TabelaLR[100][0]=115;
	TabelaLR[103][0]=117;
	TabelaLR[105][0]=119;
	TabelaLR[107][0]=119;
	TabelaLR[108][0]=121;
	TabelaLR[110][0]=85;
	TabelaLR[118][0]=23;
	TabelaLR[120][0]=23;
	TabelaLR[124][0]=78;
	TabelaLR[125][0]=23;
	TabelaLR[190][0]=195;
	TabelaLR[197][0]=201;
	TabelaLR[198][0]=23;
	TabelaLR[200][0]=85;
	TabelaLR[222][0]=23;
	TabelaLR[225][0]=23;
	TabelaLR[30][1]=66;//literal
	TabelaLR[28][3]=-5;//termina
	TabelaLR[43][3]=-5;
	TabelaLR[44][3]=-6;
	TabelaLR[28][4]=24;//int
	TabelaLR[35][4]=75;
	TabelaLR[118][4]=24;
	TabelaLR[120][4]=24;
	TabelaLR[125][4]=24;
	TabelaLR[198][4]=24;
	TabelaLR[222][4]=24;
	TabelaLR[225][4]=24;
	TabelaLR[28][5]=25; //float
	TabelaLR[118][5]=25;
	TabelaLR[120][5]=25;
	TabelaLR[125][5]=25;
	TabelaLR[198][5]=25;
	TabelaLR[222][5]=25;
	TabelaLR[225][5]=25;
	TabelaLR[28][6]=26; //char
	TabelaLR[118][6]=26;
	TabelaLR[120][6]=26;
	TabelaLR[125][6]=26;
	TabelaLR[198][6]=26;
	TabelaLR[222][6]=26;
	TabelaLR[225][6]=26;
	TabelaLR[28][7]=18; //bool
	TabelaLR[118][7]=18;
	TabelaLR[120][7]=18;
	TabelaLR[125][7]=18;
	TabelaLR[198][7]=18;
	TabelaLR[222][7]=18;
	TabelaLR[225][7]=18;
	TabelaLR[73][8]=98;//verdadeiro
	TabelaLR[73][9]=98;//falso
	TabelaLR[28][11]=20;//escolha
	TabelaLR[118][11]=20;
	TabelaLR[120][11]=20;
	TabelaLR[125][11]=20;
	TabelaLR[198][11]=20;
	TabelaLR[222][11]=20;
	TabelaLR[225][11]=20;
	TabelaLR[76][12]=103; //caso
	TabelaLR[191][12]=197;
	TabelaLR[28][13]=22; //se
	TabelaLR[118][13]=22;
	TabelaLR[120][13]=22;
	TabelaLR[125][13]=22;
	TabelaLR[198][13]=22;
	TabelaLR[222][13]=22;
	TabelaLR[225][13]=22;
	TabelaLR[189][14]=193; //senao
	TabelaLR[28][15]=-5;//quebra
	TabelaLR[43][15]=-5;
	TabelaLR[44][15]=-6;
	TabelaLR[168][15]=191;
	TabelaLR[247][15]=268;
	TabelaLR[28][16]=19; //para
	TabelaLR[118][16]=19;
	TabelaLR[120][16]=19;
	TabelaLR[125][16]=19;
	TabelaLR[198][16]=19;
	TabelaLR[222][16]=19;
	TabelaLR[225][16]=19;
	TabelaLR[28][17]=21; //enquanto
	TabelaLR[118][17]=21;
	TabelaLR[120][17]=21;
	TabelaLR[125][17]=21;
	TabelaLR[198][17]=21;
	TabelaLR[222][17]=21;
	TabelaLR[225][17]=21;
	TabelaLR[118][18]=14;//leia
	TabelaLR[28][18]=14;
	TabelaLR[120][18]=14;
	TabelaLR[125][18]=14;
	TabelaLR[198][18]=14;
	TabelaLR[222][18]=14;
	TabelaLR[225][18]=14;
	TabelaLR[28][19]=16;//escreva
	TabelaLR[118][19]=16;
	TabelaLR[120][19]=16;
	TabelaLR[125][19]=16;
	TabelaLR[198][19]=16;
	TabelaLR[222][19]=16;
	TabelaLR[225][19]=16;
	TabelaLR[14][20]=29;//(
	TabelaLR[16][20]=30;
	TabelaLR[19][20]=35;
	TabelaLR[21][20]=37;
	TabelaLR[22][20]=38;
	TabelaLR[23][21]=-36;//)
	TabelaLR[39][21]=-36;
	TabelaLR[64][21]=89;
	TabelaLR[65][21]=90;
	TabelaLR[66][21]=-17;
	TabelaLR[67][21]=-18;
	TabelaLR[77][21]=104;
	TabelaLR[79][21]=106;
	TabelaLR[80][21]=-28;
	TabelaLR[81][21]=-29;
	TabelaLR[85][21]=-36;
	TabelaLR[86][21]=-37;
	TabelaLR[109][21]=-36;
	TabelaLR[119][21]=-34;
	TabelaLR[121][21]=-33;
	TabelaLR[122][21]=-37;
	TabelaLR[194][21]=199;
	TabelaLR[223][21]=-35;
	TabelaLR[36][22]=76;//{
	TabelaLR[104][22]=118;
	TabelaLR[106][22]=120;
	TabelaLR[193][22]=198;
	TabelaLR[199][22]=222;
	TabelaLR[28][23]=-5;//}
	TabelaLR[42][23]=88;
	TabelaLR[43][23]=-5;
	TabelaLR[44][23]=-6;
	TabelaLR[102][23]=116;
	TabelaLR[126][23]=188;
	TabelaLR[146][23]=189;
	TabelaLR[191][23]=-24;
	TabelaLR[196][23]=-24;
	TabelaLR[202][23]=226;
	TabelaLR[227][23]=267;
	TabelaLR[268][23]=-25;
	TabelaLR[23][24]=40;//=
	TabelaLR[32][24]=70;
	TabelaLR[34][24]=73;
	TabelaLR[74][24]=100;
	TabelaLR[91][24]=70;
	TabelaLR[92][24]=70;
	TabelaLR[101][24]=-39;
	TabelaLR[195][24]=200;
	TabelaLR[23][25]=41;//OpArit
	TabelaLR[85][25]=110;
	TabelaLR[82][26]=108;//OpRel
	TabelaLR[78][27]=105;//OpLog
	TabelaLR[82][27]=107;
	TabelaLR[7][28]=28;//;
	TabelaLR[8][28]=-8;
	TabelaLR[9][28]=-9;
	TabelaLR[10][28]=-10;
	TabelaLR[11][28]=-11;
	TabelaLR[12][28]=-12;
	TabelaLR[13][28]=-13;
	TabelaLR[15][28]=-15;
	TabelaLR[23][28]=-36;
	TabelaLR[27][28]=42;
	TabelaLR[31][28]=-40;
	TabelaLR[33][28]=-41;
	TabelaLR[39][28]=-36;
	TabelaLR[68][28]=-40;
	TabelaLR[71][28]=-41;
	TabelaLR[84][28]=-19;
	TabelaLR[85][28]=-36;
	TabelaLR[86][28]=-37;
	TabelaLR[89][28]=-14;
	TabelaLR[90][28]=-16;
	TabelaLR[91][28]=-1000;
	TabelaLR[93][28]=-19;
	TabelaLR[97][28]=-20;
	TabelaLR[98][28]=-21;
	TabelaLR[99][28]=-22;
	TabelaLR[109][28]=-36;
	TabelaLR[111][28]=-42;
	TabelaLR[112][28]=-44;
	TabelaLR[115][28]=124;
	TabelaLR[116][28]=-23;
	TabelaLR[119][28]=-34;
	TabelaLR[122][28]=-37;
	TabelaLR[166][28]=190;
	TabelaLR[188][28]=-46;
	TabelaLR[189][28]=-27;
	TabelaLR[192][28]=-27;
	TabelaLR[226][28]=-30;
	TabelaLR[267][28]=-32;
	TabelaLR[117][29]=125;//:
	TabelaLR[201][29]=225;
	TabelaLR[23][30]=-36;//,
	TabelaLR[31][30]=69;
	TabelaLR[33][30]=72;
	TabelaLR[39][30]=-36;
	TabelaLR[84][30]=-19;
	TabelaLR[85][30]=-36;
	TabelaLR[86][30]=-37;
	TabelaLR[91][30]=69;
	TabelaLR[93][30]=-19;
	TabelaLR[97][30]=-20;
	TabelaLR[98][30]=-21;
	TabelaLR[99][30]=-22;
	TabelaLR[109][30]=-36;
	TabelaLR[122][30]=-37;
	TabelaLR[88][31]=-1;//$


	TabelaTransicao[0][0]=1; //program
	TabelaTransicao[5][1]=17; //tipo
	TabelaTransicao[28][1]=17;
	TabelaTransicao[118][1]=17;
	TabelaTransicao[120][1]=17;
	TabelaTransicao[125][1]=17;
	TabelaTransicao[198][1]=17;
	TabelaTransicao[222][1]=17;
	TabelaTransicao[225][1]=17;
	TabelaTransicao[5][2]=6; //stmt_list
	TabelaTransicao[28][2]=44;
	TabelaTransicao[43][2]=44;
	TabelaTransicao[118][2]=126;
	TabelaTransicao[120][2]=146;
	TabelaTransicao[125][2]=168;
	TabelaTransicao[198][2]=202;
	TabelaTransicao[222][2]=227;
	TabelaTransicao[225][2]=247;
	TabelaTransicao[28][3]=43;//stmt_list_list
	TabelaTransicao[5][4]=7; //stmt
	TabelaTransicao[28][4]=7;
	TabelaTransicao[118][4]=7;
	TabelaTransicao[120][4]=7;
	TabelaTransicao[125][4]=7;
	TabelaTransicao[198][4]=7;
	TabelaTransicao[222][4]=7;
	TabelaTransicao[225][4]=7;
	TabelaTransicao[30][5]=65; //stmt_escreva
	TabelaTransicao[5][6]=15; //atribuicao
	TabelaTransicao[17][6]=31;
	TabelaTransicao[28][6]=15;
	TabelaTransicao[69][6]=91;
	TabelaTransicao[72][6]=91;
	TabelaTransicao[118][6]=15;
	TabelaTransicao[120][6]=15;
	TabelaTransicao[125][6]=15;
	TabelaTransicao[198][6]=15;
	TabelaTransicao[222][6]=15;
	TabelaTransicao[225][6]=15;
	TabelaTransicao[18][7]=33; //tipo_bool_atr
	TabelaTransicao[73][8]=97; //tipo_bool_atr_fat
	TabelaTransicao[5][9]=10; //escolha_stmt
	TabelaTransicao[28][9]=10;
	TabelaTransicao[118][9]=10;
	TabelaTransicao[120][9]=10;
	TabelaTransicao[125][9]=10;
	TabelaTransicao[198][9]=10;
	TabelaTransicao[222][9]=10;
	TabelaTransicao[225][9]=10;
	TabelaTransicao[76][10]=102; //escolha_stmt_caso
    TabelaTransicao[191][11]=196;//escolha_stmt_caso_fat
	TabelaTransicao[5][12]=12; //se_stmt
	TabelaTransicao[28][12]=12;
	TabelaTransicao[118][12]=12;
	TabelaTransicao[120][12]=12;
	TabelaTransicao[125][12]=12;
	TabelaTransicao[198][12]=12;
	TabelaTransicao[222][12]=12;
	TabelaTransicao[225][12]=12;
	TabelaTransicao[189][13]=192; //senao_stmt
	TabelaTransicao[38][14]=79; //exp_se
	TabelaTransicao[5][15]=9; //para_stmt
	TabelaTransicao[28][15]=9;
	TabelaTransicao[118][15]=9;
	TabelaTransicao[120][15]=9;
	TabelaTransicao[125][15]=9;
	TabelaTransicao[198][15]=9;
	TabelaTransicao[222][15]=9;
	TabelaTransicao[225][15]=9;
	TabelaTransicao[38][16]=81; //<exp_relacional>
	TabelaTransicao[37][17]=77; //<exp_logica>
	TabelaTransicao[38][17]=80;
	TabelaTransicao[124][17]=166;
	TabelaTransicao[190][18]=194; //<exp_aritmetica>
	TabelaTransicao[5][19]=13; //<exp>
	TabelaTransicao[28][19]=13;
	TabelaTransicao[40][19]=84;
	TabelaTransicao[41][19]=86;
	TabelaTransicao[70][19]=93;
	TabelaTransicao[110][19]=122;
	TabelaTransicao[118][19]=13;
	TabelaTransicao[120][19]=13;
	TabelaTransicao[125][19]=13;
	TabelaTransicao[198][19]=13;
	TabelaTransicao[200][19]=223;
	TabelaTransicao[222][19]=13;
	TabelaTransicao[225][19]=13;
	TabelaTransicao[23][20]=39; //<exp_exp>
	TabelaTransicao[85][20]=109;
	TabelaTransicao[35][21]=74; //<atr_para>
	TabelaTransicao[5][22]=8; //<decl_variavel>
	TabelaTransicao[28][22]=8;
	TabelaTransicao[118][22]=8;
	TabelaTransicao[120][22]=8;
	TabelaTransicao[125][22]=8;
	TabelaTransicao[198][22]=8;
	TabelaTransicao[222][22]=8;
	TabelaTransicao[225][22]=8;
	TabelaTransicao[31][23]=68;//<decl_variavel_fat>
	TabelaTransicao[33][23]=71;
	TabelaTransicao[91][23]=112;
	TabelaTransicao[91][24]=111; //<decl_mesmo_tipo>
	TabelaTransicao[5][25]=11; //<enquanto_stmt>
	TabelaTransicao[28][25]=11;
	TabelaTransicao[118][25]=11;
	TabelaTransicao[120][25]=11;
	TabelaTransicao[125][25]=11;
	TabelaTransicao[198][25]=11;
	TabelaTransicao[222][25]=11;
	TabelaTransicao[225][25]=11;
}
int main(int argc, char **argv)
{
	//int tam=strlen(argv[1]);
	FILE *input =fopen(argv[1], "r");
		
	inicializaTabelas();
		
	//for(int i=0;i<tam;i++){
	AnalisadorLexico(input);
	fclose(input);
	AnalisadorSintatico();
	
	return 0;
}

