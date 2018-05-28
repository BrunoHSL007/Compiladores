//Licença
#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <iterator>
using namespace std;
string reservadas[17]={"void", "int", "char", "bool", "float", "se", "senao", "escolha", "caso", "quebra", "padrao", "para", "enquanto", "comeca", "termina", "leia", "escreva"};
int main(int argc, char **argv)
{
	//int tam=strlen(argv[1]);
	FILE *input =fopen(argv[1], "r");
	int ContLinha=1; //contador da linha onde está o erro
	//for(int i=0;i<tam;i++){
	list <string> lista;
	
	if (input == NULL)  // Se houve erro na abertura
	{
		printf("Problemas na abertura do arquivo\n");
		return 1;
	}
	while (!feof(input))
	{
		// Lê caracter por caracter do arquivo
		char lido = getc(input);
		//cout << " valor lido["<< contador <<"] = " << lido<<endl;
		if(lido=='\n'){
			ContLinha++;
		}
		else if(lido=='&')//Operadores Lógicos
		{
			lido = getc(input);
			if(lido=='&'){
				lista.push_back("AND");
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
				lista.push_back("OR");
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
				lista.push_back("IGUALDADE");
			}
			else{
				lista.push_back("ATRIBUICAO");
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='!')
		{
			lido = getc(input);
			if(lido=='='){
				lista.push_back("DIFERENTE");
			}
			else{
				lista.push_back("NOT");
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='<')
		{
			lido = getc(input);
			if(lido=='='){
				lista.push_back("MENORIGUAL");
			}
			else{
				lista.push_back("MENOR");
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='>')
		{
			lido = getc(input);
			if(lido=='='){
				lista.push_back("MAIORIGUAL");
			}
			else{
				lista.push_back("MAIOR");
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		//Controle
		else if(lido=='(')
		{
			lista.push_back("ABREPAR");
		}
		else if(lido==')')
		{
			lista.push_back("FECHAPAR");
		}
		else if(lido=='{')
		{
			lista.push_back("ABRECHAVE");
		}
		else if(lido=='}')
		{
			lista.push_back("FECHACHAVE");
		}
		else if(lido==';')
		{
			lista.push_back("FIMCOMANDO");
		}
		//Operadores Aritméticos
		else if(lido=='+')
		{
			lista.push_back("SOMA");
		}
		else if(lido=='-')
		{
			lista.push_back("SUBTRACAO");
		}
		else if(lido=='*')
		{
			lista.push_back("MULTIPLICACAO");
		}
		else if(lido=='/')
		{
			lido = getc(input);
			if(lido=='/'){ //Ignora comentários
				while(getc(input)!='\n');
			}
			else{
				lista.push_back("DIVISAO");
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
			for(int i=0; i<17;i++){
				if(!palavra.compare(reservadas[i])){
					//cout << "reservada " << palavra<<endl;
					isReservada=true;
					break;
				}
			}
			string aux1;
			if(isReservada){
				for(int i=0; i<palavra.size(); i++)
				{                            // Converte cada caracter de Str
				 palavra[i] = toupper (palavra[i]);  // para maiusculas
				}
				aux1 = palavra;
			}
			else{
				aux1 = "ID "+palavra;
				
			}
			lista.push_back(aux1);
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
				
				string aux1 = "PONTO FLUTUANTE "+digito;
				lista.push_back(aux1);
			}
			else{
				string aux1 = "INTEIRO "+digito;
				lista.push_back(aux1);
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
			string aux1 = "LITERAL \'"+literal+"\'";
			lista.push_back(aux1);
			
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
			string aux1 = "LITERAL \'"+literal+"\'";
			lista.push_back(aux1);
		}
		else if(lido!=' ' && lido!=',' && lido!=EOF && lido!='\t'){
			cout << "Erro na Linha " << ContLinha << " => Caractere '"<<lido<<"' nao esperado"<<endl<<endl;
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
	}
	list <string> :: iterator it;
	cout << "\tLISTA DE TOKENS\n";
	for(it = lista.begin(); it != lista.end(); ++it)
			cout << *it << '\n' ;
	fclose(input);
	return 0;
}

