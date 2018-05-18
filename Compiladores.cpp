//Licença
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
	//int tam=strlen(argv[1]);
	FILE *input =fopen(argv[1], "r");
	int ContLinha=1; //contador da linha onde está o erro
	//for(int i=0;i<tam;i++){
	
	if (input == NULL)  // Se houve erro na abertura
	{
		printf("Problemas na abertura do arquivo\n");
		return 1;
	}
	int contador=0;
	while (!feof(input))
	{
		// Lê caracter por caracter do arquivo
		char lido = getc(input);
		
		cout << " valor lido["<< contador <<"] = " << lido<<endl;
		//Operadores Lógicos
		if(lido=='&')
		{
			lido = getc(input);
			if(lido=='&'){
				cout << "AND" << endl;
			}
			else{
				cout << "Erro na Linha " << ContLinha << " = &" << lido;
				fseek(input, -1, 1); //Volta um caractere
				
			}
		}
		else if(lido=='|')
		{
			lido = getc(input);
			if(lido=='|'){
				cout << "OR" << endl;
			}
			else{
				cout << "Erro na Linha " << ContLinha << " = &" << lido;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='=')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "IGUALDADE" << endl;
			}
			else{
				cout << "ATRIBUICAO" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='!')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "DIFERENTE" << endl;
			}
			else{
				cout << "NOT" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='<')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "MENORIGUAL" << endl;
			}
			else{
				cout << "MENOR" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='>')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "MAIORIGUAL" << endl;
			}
			else{
				cout << "MAIOR" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		//Controle
		else if(lido=='(')
		{
			cout << "ABREPAR" << endl;
		}
		else if(lido==')')
		{
			cout << "FECHAPAR" << endl;
		}
		else if(lido=='{')
		{
			cout << "ABRECHAVE" << endl;
		}
		else if(lido=='}')
		{
			cout << "FECHACHAVE" << endl;
		}
		else if(lido==';')
		{
			cout << "FIMCOMANDO" << endl;
		}
		//Operadores Aritméticos
		else if(lido=='+')
		{
			cout << "SOMA" << endl;
		}
		else if(lido=='-')
		{
			cout << "SUBTRACAO" << endl;
		}
		else if(lido=='*')
		{
			cout << "MULTIPLICACAO" << endl;
		}
		else if(lido=='/')
		{
			lido = getc(input);
			if(lido=='/'){ //Ignora comentários
				while(getc(input)!='\n');
			}
			else{
				cout << "DIVISAO" << endl;
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
			//char palavra[tamanhoPalavra];
			//for(int i=0;i<tamanhoPalavra;i++){
			//	palavra[i] = getc(input);
			//}
			//for(int i=)
			cout << "ID " << palavra << endl;
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
				cout <<"Ponto Flutuante " << digito << endl;
			}
			else{
				cout <<"Inteiro " << digito << endl;
			}
		}
		else if(lido =='\"'){
			lido = getc(input);
			string literal;
			while((lido!='\"')){
				//tamanhoDigito++;
				literal+=lido;
				lido = getc(input);
				if(lido==EOF){
					cout << "Não encontrado \" do fechamento" << endl; //Ver se tá certo com o Professor
					return 1;
				}
			}
			cout << "Literal " << literal << endl;
		}
		else if(lido =='\''){
			lido = getc(input);
			string literal;
			while((lido!='\'')){
				//tamanhoDigito++;
				literal+=lido;
				lido = getc(input);
				if(lido==EOF){
					cout << "Não encontrado \' do fechamento" << endl; //Ver se tá certo com o Professor
					return 1;
				}
			}
			cout << "Literal " << literal << endl;
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
		
		//Perguntar sobre o número negativo se é feito nessa etapa ou mais pra frente
		//Perguntar se é pra salvar em uma lista e como fazer isso
		
		contador++;
	}
	fclose(input);
	return 0;
}

